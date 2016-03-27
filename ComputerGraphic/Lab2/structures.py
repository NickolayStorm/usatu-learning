import numpy as np
import math

from PyQt5.QtCore import *


# Матрицы базовых преобразований.
class TransformationMatrix:
    # Пустая матрица, забитая нулями.
    @staticmethod
    def null():
        return np.matrix(np.zeros((4, 4)))

    # Базовая матрица с единицами на главной диагонали.
    @staticmethod
    def base():
        mtx = TransformationMatrix.null()
        mtx.itemset((0, 0), 1)
        mtx.itemset((1, 1), 1)
        mtx.itemset((2, 2), 1)
        mtx.itemset((3, 3), 1)
        return mtx

    # Поворот вокруг оси OX
    @staticmethod
    def rotation_ox(angle):
        mtx = TransformationMatrix.base()
        mtx.itemset((1, 1), math.cos(angle))
        mtx.itemset((1, 2), math.sin(angle))
        mtx.itemset((2, 1), -math.sin(angle))
        mtx.itemset((2, 2), math.cos(angle))
        return mtx

    # Поворот вокруг оси OY
    @staticmethod
    def rotation_oy(angle):
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 0), math.cos(angle))
        mtx.itemset((0, 2), -math.sin(angle))
        mtx.itemset((2, 0), math.sin(angle))
        mtx.itemset((2, 2), math.cos(angle))
        return mtx

    # Поворот вокруг оси OZ
    @staticmethod
    def rotation_oz(angle):
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 0), math.cos(angle))
        mtx.itemset((0, 1), math.sin(angle))
        mtx.itemset((1, 0), -math.sin(angle))
        mtx.itemset((1, 1), math.cos(angle))
        return mtx

    # Сжатие/растяжение
    @staticmethod
    def deformation(alpha, beta, gamma):
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 0), alpha)
        mtx.itemset((1, 1), beta)
        mtx.itemset((2, 2), gamma)
        return mtx

    # Отражение относительно плоскости XOY
    @staticmethod
    def reflection_xoy():
        mtx = TransformationMatrix.base()
        mtx.itemset((2, 2), -1)
        return mtx

    # Отражение относительно плоскости YOZ
    @staticmethod
    def reflection_yoz():
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 0), -1)
        return mtx

    # Отражение относительно плоскости XOZ
    @staticmethod
    def reflection_xoz():
        mtx = TransformationMatrix.base()
        mtx.itemset((1, 1), -1)
        return mtx

    # Перенос на вектор (l, m, n)
    @staticmethod
    def transfer(l, m, n):
        mtx = TransformationMatrix.base()
        mtx.itemset((3, 0), l)
        mtx.itemset((3, 1), m)
        mtx.itemset((3, 2), n)
        return mtx

    # Матрица перспективного преобразования на плоскость XOY
    @staticmethod
    def central_xoy(c):
        mtx = TransformationMatrix.base()
        mtx.itemset((2, 3), -1/c)
        return mtx

    # Матрица перспективного преобразования на плоскость XOZ
    @staticmethod
    def central_xoz(c):
        mtx = TransformationMatrix.base()
        mtx.itemset((1, 3), -1/c)
        return mtx

    # Матрица перспективного преобразования на плоскость YOZ
    @staticmethod
    def central_yoz(c):
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 3), -1/c)
        return mtx

    # Матрица ортогонального проецирования на плоскость XOY
    @staticmethod
    def ortogonal_projection_xoy():
        mtx = TransformationMatrix.base()
        mtx.itemset((2, 2), 0)
        return mtx

    # Матрица ортогонального проецирования на плоскость XOZ
    @staticmethod
    def ortogonal_projection_xoz():
        mtx = TransformationMatrix.base()
        mtx.itemset((1, 1), 0)
        return mtx

    # Матрица ортогонального проецирования на плоскость YOZ
    @staticmethod
    def ortogonal_projection_yoz():
        mtx = TransformationMatrix.base()
        mtx.itemset((0, 0), 0)
        return mtx


# Точка с однородными координатами.
class HomogeneousPoint:
    def __init__(self):
        self.point_struct = np.matrix([0, 0, 0, 1])

    def __init__(self, x, y, z, c=1):
        self.point_struct = np.matrix([x, y, z, c])

    # Умножение вектора и матрицы преобразований.
    def __mul__(self, other):
        tmp = self.point_struct * other
        return HomogeneousPoint(tmp.item(0),tmp.item(1),tmp.item(2),tmp.item(3))

    # Сравнение точек.
    def __eq__(self, other):
        return ( self.point_struct.item(0) == other.point_struct.item(0) and
                self.point_struct.item(1) == other.point_struct.item(1) and
                self.point_struct.item(2) == other.point_struct.item(2) and
                self.point_struct.item(3) == other.point_struct.item(3) )

    @property
    def x(self):
        return self.point_struct.item(0)

    @property
    def y(self):
        return self.point_struct.item(1)

    @property
    def z(self):
        return self.point_struct.item(2)

    def convert_to_2d(self):
        y_2d = self.point_struct.item(1)/self.point_struct.item(3)
        x_2d = self.point_struct.item(0)/self.point_struct.item(3)
        return Point(x_2d, y_2d)

    def __str__(self):
        s = "("+str(self.x)+", "+str(self.y)+", "+str(self.z)+", "+str(self.point_struct.item(3))+")"
        return s


# Точка двумерного пространства
class Point(QPoint):
    def __init__(self, x, y):
        super(Point, self).__init__(x, y)
        self.x = x
        self.y = y

    def __str__(self):
        return "("+str(self.x)+", "+str(self.y)+")"
