from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtGui import *
from structures import HomogeneousPoint
from dimensional import DimensionalView
from complexview import ComplexView


class Presenter(QMainWindow):
    def __init__(self):

        super(Presenter, self).__init__()
        loadUi("gui2.ui", self)

        dimensional = DimensionalView(self)
        old = self.w1.size()
        self.widgets_layout.replaceWidget(self.w1, dimensional)
        dimensional.resize(old)
        dimensional.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        complex = ComplexView(self)
        old = self.w2.size()
        self.widgets_layout.replaceWidget(self.w2, complex)
        complex.resize(old)
        complex.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        self.dimensional_view = dimensional
        self.complex_view = complex

        self.connect_signals()
        self.set_values()
        print(self.mode.currentIndex())
        if self.mode.currentIndex() == 0:
            self.dimensional_view.set_mode("central")
        else:
            self.dimensional_view.set_mode("ortogonal")

    def connect_signals(self):
        self.sliderX.valueChanged.connect(self.on_scale_changed)
        self.sliderY.valueChanged.connect(self.on_scale_changed)
        self.sliderZ.valueChanged.connect(self.on_scale_changed)
        self.sliderVX.valueChanged.connect(self.on_scale_changed)
        self.sliderVY.valueChanged.connect(self.on_scale_changed)
        self.sliderVZ.valueChanged.connect(self.on_scale_changed)
        self.mode.currentIndexChanged.connect(self.on_rb_toggled)

    def on_scale_changed(self):
        # self.labelX.setText(str(self.sliderX.value()))
        # self.labelY.setText(str(self.sliderY.value()))
        # self.labelZ.setText(str(self.sliderZ.value()))
        # self.labelVX.setText(str(self.sliderVX.value()))
        # self.labelVY.setText(str(self.sliderVY.value()))
        # self.labelVZ.setText(str(self.sliderVZ.value()))
        text_c = "C({},{},{})".format(self.sliderVX.value(),
                                      self.sliderVY.value(),
                                      self.sliderVZ.value())
        self.labelC.setText(text_c)
        text_t = "C({},{},{})".format(self.sliderX.value(),
                                      self.sliderY.value(),
                                      self.sliderZ.value())
        self.labelT.setText(text_t)
        self.set_values()

    def set_values(self):
        C = HomogeneousPoint(self.sliderVX.value(),
                                self.sliderVY.value(),
                                self.sliderVZ.value())
        T = HomogeneousPoint(self.sliderX.value(),
                                self.sliderY.value(),
                                self.sliderZ.value())
        self.dimensional_view.set_points(T, C)
        self.complex_view.set_points(T, C)
        self.update()

    def on_rb_toggled(self, index):
        if index == 0:
            self.dimensional_view.set_mode("central")
        else:
            self.dimensional_view.set_mode("ortogonal")
        self.dimensional_view.update()
