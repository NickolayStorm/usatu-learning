from PyQt5.QtGui import *
from PyQt5.QtCore import *
from structures import Point
from enum import Enum


class PointType(Enum):
    main = 1
    subsidiary = 2
    observer_main = 3
    observer_subsidiary = 3

pen_color = {PointType.main: Qt.darkBlue,
             PointType.subsidiary: Qt.blue,
             PointType.observer_main: Qt.red,
             PointType.observer_subsidiary: Qt.red}

pen_size = {PointType.main: 3,
            PointType.subsidiary: 2,
            PointType.observer_main: 3,
            PointType.observer_subsidiary: 2}


class CairoDrawing:
    @staticmethod
    def draw_line(cr, p1, p2, p1_name=None, p2_name=None):
        cr.drawLine(p1, p2)
        if p1_name is not None:
            cr.drawText(p1, p1_name)
        if p2_name is not None:
            cr.drawText(p1, p1_name)

    @staticmethod
    def draw_axis(cr, p1, p2, name):
        cr.drawLine(p1, p2)
        cr.drawText(p1, name)

    @staticmethod
    def draw_complex_axis(cr, p1, p2):
        pass

    @staticmethod
    def draw_point(cr, p, name, point_type):

        pen = QPen()
        color = pen_color[point_type]
        pen.setColor(color)
        cr.setPen(pen)
        brush = QBrush()
        brush.setStyle(Qt.SolidPattern)
        brush.setColor(color)
        cr.setBrush(brush)
        size = pen_size[point_type]

        cr.drawEllipse(p, size, size)

        brush.setColor(QColor(0, 0, 0, 255))
        cr.setBrush(brush)
        pen.setColor(QColor(0, 0, 0, 255))

        cr.drawText(p, name)

    @staticmethod
    def draw_text(cr, p, text):
        cr.drawText(p, text)

    @staticmethod
    def draw_arc(cr, p1, p2, zero):
        x = (p1.x - zero.x) * 2
        y = (p2.y - zero.y) * 2
        area = QSize(x, y)
        delta = p1.x - zero.x
        area_point = Point(zero.x - delta, zero.y - delta)
        if zero.x > p1.x:
            start_angle = 90 * 16
            spain_angle = 90 * 16
        else:
            start_angle = 0
            spain_angle = -90 * 16

        cr.drawArc(QRect(area_point, area), start_angle, spain_angle)

    @staticmethod
    def change_pen_dash(cr):
        pen = QPen()
        pen.setStyle(Qt.DashLine)
        pen.setColor(QColor(115, 117, 115, 255))
        cr.setPen(pen)

    @staticmethod
    def change_pen_default(cr):
        pen = QPen()
        pen.setStyle(Qt.SolidLine)
        pen.setColor(QColor(0, 0, 0, 255))
        cr.setPen(pen)
