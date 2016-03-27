#! /usr/bin/python

from PyQt5.QtWidgets import QApplication
from presenter import Presenter
import sys

def main():
    # view = View()
    # dim_view = DimensionalView(view.drawing_area_dimensional.get_allocation().width,view.drawing_area_dimensional.get_allocation().height)
    # comp_view = ComplexView(view.drawing_area_complex.get_allocation().width,view.drawing_area_complex.get_allocation().height)
    app = QApplication(sys.argv)
    p = Presenter()
    p.show()
    app.exec_()

if __name__ == '__main__':
    main()
