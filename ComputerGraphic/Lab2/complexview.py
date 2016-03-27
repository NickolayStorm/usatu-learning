from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from cairodrawing import CairoDrawing, PointType
from structures import Point, HomogeneousPoint


class ComplexView(QWidget):
    def __init__(self, parent=None, indent=20):

        super(ComplexView, self).__init__(parent)

        width = self.width()
        height = self.height()

        # Новый центр координат экрана
        self.x0 = width / 2
        self.y0 = height / 2
        # Отступ от крайних точек оси до границы области рисования.
        self.indent = indent
        # Длина оси координат.
        self.axis_length = min(width, height) - 2*self.indent
        # Точки комплексного чертежа.
        self.point_t = HomogeneousPoint(50, 50, 50)
        self.point_c = HomogeneousPoint(90, 90, 90)

    def set_points(self, point_t, point_c):
        self.point_t = point_t
        self.point_c = point_c
        self.calculate()

    def resizeEvent(self, event):
        size = event.size()
        self.resize(size)
        self.x0 = self.width()/2
        self.y0 = self.height()/2
        self.axis_length = min(self.width(), self.height()) - 2*self.indent
        self.calculate()

    def calculate(self):
        # Крайние точки осей координат
        self.XY_begin = Point(self.x0 - self.axis_length/2, self.y0)
        self.XY_end = Point(self.x0 + self.axis_length/2, self.y0)

        self.YZ_begin = Point(self.x0, self.y0 - self.axis_length/2)
        self.YZ_end = Point(self.x0, self.y0 + self.axis_length/2)

        # Точки комплексного чертежа. Точка T.
        self.TX = Point(self.x0 - self.point_t.x, self.y0)
        self.TY1 = Point(self.x0 + self.point_t.y, self.y0)
        self.TY2 = Point(self.x0, self.y0 + self.point_t.y)
        self.TZ = Point(self.x0, self.y0 - self.point_t.z)
        self.T1 = Point(self.TX.x, self.TY2.y)
        self.T2 = Point(self.TX.x, self.TZ.y)
        self.T3 = Point(self.TY1.x, self.TZ.y)

        # Точки комплексного чертежа. Точка C.
        self.CX = Point(self.x0 - self.point_c.x, self.y0)
        self.CY1 = Point(self.x0 + self.point_c.y, self.y0)
        self.CY2 = Point(self.x0, self.y0 + self.point_c.y)
        self.CZ = Point(self.x0, self.y0 - self.point_c.z)
        self.C1 = Point(self.CX.x, self.CY2.y)
        self.C2 = Point(self.CX.x, self.CZ.y)
        self.C3 = Point(self.CY1.x, self.CZ.y)

    def paintEvent(self, event):
        painter = QPainter(self)

        pen = QPen()
        brush = QBrush(QColor(135, 206, 235, 255))
        painter.setBrush(brush)
        pen.setColor(QColor(20, 10, 70, 255))
        painter.drawRect(0, 0, self.width(), self.height())

        # painter.translate(self.width()/2, self.height()/2)
        # painter.set_font_size(16)

        CairoDrawing.draw_line(painter, self.XY_begin, self.XY_end)
        CairoDrawing.draw_line(painter, self.YZ_begin, self.YZ_end)

        CairoDrawing.draw_text(painter, Point(self.YZ_begin.x+5, self.YZ_begin.y+10), "-Y")
        CairoDrawing.draw_text(painter, Point(self.YZ_begin.x-15, self.YZ_begin.y+10), "Z")
        CairoDrawing.draw_text(painter, Point(self.YZ_end.x+5, self.YZ_end.y-10), "Y")
        CairoDrawing.draw_text(painter, Point(self.YZ_end.x-20, self.YZ_end.y-10), "-Z")
        CairoDrawing.draw_text(painter, Point(self.XY_begin.x, self.XY_begin.y+15), "-Y")
        CairoDrawing.draw_text(painter, Point(self.XY_begin.x, self.XY_begin.y-5), "X")
        CairoDrawing.draw_text(painter, Point(self.XY_end.x-10, self.XY_end.y-5), "-X")
        CairoDrawing.draw_text(painter, Point(self.XY_end.x-10, self.XY_end.y+15), "Y")

        CairoDrawing.draw_line(painter, self.T1, self.TX)
        CairoDrawing.draw_line(painter, self.TX, self.T2)
        CairoDrawing.draw_line(painter, self.T2, self.TZ)
        CairoDrawing.draw_line(painter, self.TZ, self.T3)
        CairoDrawing.change_pen_dash(painter)
        CairoDrawing.draw_line(painter, self.T3, self.TY1)
        CairoDrawing.draw_line(painter, self.TY2, self.T1)
        CairoDrawing.change_pen_default(painter)

        CairoDrawing.draw_arc(painter, self.TY1, self.TY2, Point(self.width()/2, self.height()/2))

        CairoDrawing.draw_point(painter, self.T1, "T1", PointType.main)
        CairoDrawing.draw_point(painter, self.TX, "TX", PointType.subsidiary)
        CairoDrawing.draw_point(painter, self.T2, "T2", PointType.main)
        CairoDrawing.draw_point(painter, self.TZ, "TZ", PointType.subsidiary)
        CairoDrawing.draw_point(painter, self.T3, "T3", PointType.main)
        CairoDrawing.draw_point(painter, self.TY1, "TY1", PointType.subsidiary)
        CairoDrawing.draw_point(painter, self.TY2, "TY2", PointType.subsidiary)

        CairoDrawing.draw_line(painter, self.C1, self.CX, p2_name="CX")
        CairoDrawing.draw_line(painter, self.CX, self.C2, p2_name="C2")
        CairoDrawing.draw_line(painter, self.C2, self.CZ, p2_name="CZ")
        CairoDrawing.draw_line(painter, self.CZ, self.C3, p2_name="C3")
        CairoDrawing.change_pen_dash(painter)
        CairoDrawing.draw_line(painter, self.C3, self.CY1, p2_name="CY1")
        CairoDrawing.draw_line(painter, self.CY2, self.C1, "CY2", "C1")
        CairoDrawing.change_pen_default(painter)

        CairoDrawing.draw_arc(painter, self.CY1, self.CY2, Point(self.width()/2, self.height()/2))

        CairoDrawing.draw_point(painter, self.C1, "C1", PointType.observer_main)
        CairoDrawing.draw_point(painter, self.CX, "CX", PointType.observer_subsidiary)
        CairoDrawing.draw_point(painter, self.C2, "C2", PointType.observer_main)
        CairoDrawing.draw_point(painter, self.CZ, "CZ", PointType.observer_subsidiary)
        CairoDrawing.draw_point(painter, self.C3, "C3", PointType.observer_main)
        CairoDrawing.draw_point(painter, self.CY1, "CY1", PointType.observer_subsidiary)
        CairoDrawing.draw_point(painter, self.CY2, "CY2", PointType.observer_subsidiary)
