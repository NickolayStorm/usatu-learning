from structures import TransformationMatrix, HomogeneousPoint
import math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from cairodrawing import CairoDrawing, PointType


class DimensionalView(QWidget):
    def __init__(self, parent=None, axis_length=40, indent=20):

        super(DimensionalView, self).__init__(parent)
        # Длина оси
        self.axis_length = axis_length - 2*indent
        self.indent = indent
        # Новый центр координат экрана
        self.x0 = self.width()/2
        self.y0 = self.height()/2
        # Матрица преобразования
        self.transformation_matrix = None
        # Матрица поворотов
        self.rotation_matrix = None
        # Режим центрального или ортогонального проецирования
        self.mode = "central"
        # Наличие ошибки
        self.error_status = None

    def resizeEvent(self, event):
        size = event.size()
        self.resize(size)
        self.x0 = self.width()/2
        self.y0 = self.height()/2
        self.axis_length = (min(self.width(), self.height()) - self.indent*2)/2
        self.calculate()

    def set_size(self, width, height):
        self.x0 = width/2
        self.y0 = height/2
        self.calculate()

    def set_points(self, source_point, observer_point):
        self.source_point = source_point
        self.observer_point = observer_point
        self.calculate()

    def set_mode(self,mode):
        self.mode = mode
        self.calculate()

    # Создание матрицы поворотов.
    def create_rotation_matrix(self, C):
        oz_angle = math.atan2(C.x, C.y)
        length = math.sqrt(C.x*C.x + C.y*C.y)
        ox_angle = math.atan2(length, C.z)
        self.rotation_matrix = TransformationMatrix.rotation_oz(oz_angle)*TransformationMatrix.rotation_ox(ox_angle)

    def central_projection_matrix(self, C):
        # Матрица поворота вокруг осей OZ и OX
        self.create_rotation_matrix(C)
        # Создаем копию, т.к. это изменяемый объект.
        mtx = self.rotation_matrix.copy()

        # Отражение относительно плоскости YOZ
        mtx = mtx * TransformationMatrix.reflection_yoz()

        # При центральном проецировании
        if self.mode == "central":
            # Координата наблюдателя: длина радиус-вектора точки наблюдателя
            observer_z = math.sqrt(C.x*C.x + C.y*C.y + C.z*C.z)
            # Центральное преобразование для плоскости XOY
            mtx = mtx * TransformationMatrix.central_xoy(observer_z)

        # Ортогональное проецирование на плоскость XOY (плоскость экрана)
        mtx = mtx * TransformationMatrix.ortogonal_projection_xoy()
        # Перенос в начало координата экрана.
        mtx = mtx * TransformationMatrix.transfer(self.x0, self.y0, 0)

        self.transformation_matrix = mtx

    # Преобразование точки трёхмерного пространства
    # в точку двумерного пространства.
    # check - параметр, который отвечает за проверку на выход за пределы экрана,
    # т.к. нет смысла проверять выход за пределы координатные оси.
    def to_2d_point(self, x, y, z, check=None):
        if self.error_status is None:
            source = HomogeneousPoint(x, y, z)
            point = (source * self.transformation_matrix).convert_to_2d()

            # Проверка на выход точки за область видимости наблюдателя.
            rotated = source * self.rotation_matrix
            observer_z = math.sqrt(self.observer_point.x**2 +
                                   self.observer_point.y**2 +
                                   self.observer_point.z**2)

            if check and (point.x < 0 or point.x > 2*self.x0 or point.y < 0 or point.y > 2*self.y0):
                self.error_status = "Точки вышли за пределы экрана"

                # Если расстояние до точки после поворотов больше или равно расстоянию до наблюдателя:
            elif self.mode == "central" and rotated.z >= observer_z:
                self.error_status = "Точки вышли из области видимости наблюдателя"

            elif self.observer_point == source:
                self.error_status = "Наблюдатель находится в исходной точке"

            return point

        else:
            return None

    def calculate_points(self, source_point):
        # Точки для отрисовки осей координат
        self.OX_begin = self.to_2d_point(self.axis_length, 0, 0)
        self.OX_end = self.to_2d_point(-self.axis_length, 0, 0)
        self.OY_begin = self.to_2d_point(0, self.axis_length, 0)
        self.OY_end = self.to_2d_point(0, -self.axis_length, 0)
        self.OZ_begin = self.to_2d_point(0, 0, self.axis_length)
        self.OZ_end = self.to_2d_point(0, 0, -self.axis_length)

        # Центр системы координат
        self.O = self.to_2d_point(0, 0, 0)

        # Точка и её проекции на оси и плоскости. Одновременно производится
        # проверка на выход за пределы экрана.
        self.T = self.to_2d_point(source_point.x, source_point.y, source_point.z, "check")
        self.T1 = self.to_2d_point(source_point.x, source_point.y, 0, "check")
        self.T2 = self.to_2d_point(source_point.x, 0, source_point.z, "check")
        self.T3 = self.to_2d_point(0, source_point.y, source_point.z, "check")
        self.TX = self.to_2d_point(source_point.x, 0, 0, "check")
        self.TY = self.to_2d_point(0, source_point.y, 0, "check")
        self.TZ = self.to_2d_point(0, 0, source_point.z, "check")

    def calculate(self):
        self.error_status = None
        if self.observer_point.x == 0 and self.observer_point.y == 0 and self.observer_point.z == 0:
            self.error_status = "Наблюдатель находится в начале координат"
            return

        if self.source_point == self.observer_point:
            self.error_status = "Наблюдатель находится в исходной точке"
            return

        self.central_projection_matrix(self.observer_point)
        self.calculate_points(self.source_point)

    def paintEvent(self, event):

        painter = QPainter(self)

        pen = QPen()
        brush = QBrush(QColor(255, 245, 173, 255))
        painter.setBrush(brush)
        pen.setColor(QColor(20, 10, 70, 255))
        painter.drawRect(0, 0, self.width(), self.height())

        cr = painter

        # При отсутствии ошибок выполняем отрисовку элементов, иначе
        # выводим только сообщение об ошибке.
        if self.error_status is None:

            # Рисуем оси координат.
            CairoDrawing.draw_axis(cr, self.OX_begin, self.OX_end, 'X')
            CairoDrawing.draw_axis(cr, self.OY_begin, self.OY_end, 'Y')
            CairoDrawing.draw_axis(cr, self.OZ_begin, self.OZ_end, 'Z')

            # Рисуем линии проекций.

            pen = QPen()
            pen.setStyle(Qt.DashLine)
            pen.setColor(QColor(115, 117, 115, 255))
            cr.setPen(pen)

            CairoDrawing.draw_line(cr, self.T1, self.TX)
            CairoDrawing.draw_line(cr, self.T1, self.TY)

            CairoDrawing.draw_line(cr, self.T, self.T1)
            CairoDrawing.draw_line(cr, self.T, self.T2)
            CairoDrawing.draw_line(cr, self.T, self.T3)

            CairoDrawing.draw_line(cr, self.T2, self.TX)
            CairoDrawing.draw_line(cr, self.T2, self.TZ)

            CairoDrawing.draw_line(cr, self.T3, self.TY)
            CairoDrawing.draw_line(cr, self.T3, self.TZ)

            CairoDrawing.draw_line(cr, self.TX, self.O)
            CairoDrawing.draw_line(cr, self.TY, self.O)
            CairoDrawing.draw_line(cr, self.TZ, self.O)

            pen.setStyle(Qt.SolidLine)
            pen.setColor(QColor(0, 0, 0, 255))
            cr.setPen(pen)

            # Рисуем точки.
            CairoDrawing.draw_point(cr, self.T, "T", PointType.main)
            CairoDrawing.draw_point(cr, self.O, "O", PointType.main)

            CairoDrawing.draw_point(cr, self.T1, "T1", PointType.subsidiary)
            CairoDrawing.draw_point(cr, self.T2, "T2", PointType.subsidiary)
            CairoDrawing.draw_point(cr, self.T3, "T3", PointType.subsidiary)

            CairoDrawing.draw_point(cr, self.TX, "TX", PointType.subsidiary)
            CairoDrawing.draw_point(cr, self.TY, "TY", PointType.subsidiary)
            CairoDrawing.draw_point(cr, self.TZ, "TZ", PointType.subsidiary)

        else:
            cr.drawText(self.width()/5, self.height()/2, self.error_status)
