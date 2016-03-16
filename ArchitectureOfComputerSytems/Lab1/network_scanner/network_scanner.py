#! /usr/bin/python

import sys
from controller import Controller
from view import View
from PyQt5.QtWidgets import QApplication

def main():
    app = QApplication(sys.argv)
    controller = Controller(View)
    sys.exit(app.exec_())

if __name__ == '__main__':
	main()