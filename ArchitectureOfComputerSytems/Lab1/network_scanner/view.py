#!/usr/bin/python
# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QWidget, QTableWidgetItem, QPushButton
from PyQt5.QtWidgets import QAbstractItemView, QApplication
from PyQt5.QtGui import QCursor
from PyQt5.QtCore import QTimer, Qt
from ui import Ui_Form
from ipaddress import IPv4Address

class IpAddrItem(QTableWidgetItem):
    def __init__(self, ip):
        super(IpAddrItem, self).__init__(ip)
    def __lt__(self, other):
        return IPv4Address(self.data(0)) < IPv4Address(other.data(0))

class View(QWidget, Ui_Form):

    def __init__(self, controller):
        super(View, self).__init__()
        self.setupUi(self)
        self.get_information.clicked.connect(self.getNetInfo)
        self.analys.clicked.connect(self.netAnalys)
        self.clear_info.clicked.connect(self.clearInfo)

        self.controller = controller

        #table
        self.netMap.setColumnCount(3)
        self.netMap.setColumnWidth(0, 200)
        self.netMap.setColumnWidth(1, 110)
        self.netMap.setColumnWidth(2, 200)
        self.netMap.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.netMap.verticalHeader().setVisible(False)
        headers = ["Адрес", "Активность", "ДНС имя"]
        self.netMap.setHorizontalHeaderLabels(headers)
        self.netMap.setSortingEnabled(True)

        self.timer = QTimer()
        self.timer.timeout.connect(self.getAddressesQueue)

        self.address_begin.setInputMask("000.000.000.000;")
        self.address_end.setInputMask("000.000.000.000;")
        self.timeout.setInputMask("0000;")
        self.hide_timeouted.stateChanged.connect(self.setRowsHiden)

        self.setWindowTitle("Сетевой анализатор. Пахтусов, ПРО-306")

    def addAddress(self, ip, status, dns):
        countRow = self.netMap.rowCount()
        self.netMap.insertRow(countRow)
        item = IpAddrItem(ip)
        self.netMap.setItem(countRow, 0, item)
        item = QTableWidgetItem(str(status))
        self.netMap.setItem(countRow, 1, item)
        item = QTableWidgetItem(dns)
        self.netMap.setItem(countRow, 2, item)
        if not status and self.hide_timeouted.isChecked():
            self.netMap.hideRow(countRow)

    def getAddressesQueue(self):
        queue = self.controller.get_addresses()
        while not queue.empty():
            addr, status, name = queue.get()
            self.addAddress(addr, status, name)
            newVal = self.progress.value() + 1
            if newVal == self.count:
                self.timer.stop()
                QApplication.restoreOverrideCursor()

            self.progress.setValue(self.progress.value() + 1)

    def getNetInfo(self):
        self.netMap.clear()
        self.netMap.setRowCount(0)
        self.progress.setValue(0)
        self.timer.start(1000)
        QApplication.setOverrideCursor(QCursor(Qt.WaitCursor))
        self.count = self.controller.ping(
                        self.address_begin.text(),
                        self.address_end.text(),
                        int(self.timeout.text())
                )
        headers = ["Адрес", "Активность", "ДНС имя"]
        self.netMap.setHorizontalHeaderLabels(headers)
        self.progress.setMinimum(0)
        self.progress.setMaximum(self.count)

    def netAnalys(self):
        rows = [index for index in self.netMap.selectedIndexes()]
        i = 0
        acc = []
        while True:
            try:
                acc.append(rows[i].data())
                i += 3
            except:
                break
        print(acc)

        mask, subnet, broadcast = self.controller.find_mask_net_addr_broadcast(acc)

        self.net_address.setText(subnet)
        self.net_address.setEnabled(True)

        self.mask.setText(mask)
        self.mask.setEnabled(True)
        self.broadcasting.setEnabled(True)
        self.broadcasting.setText(broadcast)

    def setRowsHiden(self, state):
        print("set rows hidden")
        if state == 2:
            state = True
        else:
            state = False
        count = self.netMap.rowCount()
        print(count)
        for i in range(0, count):
            if self.netMap.item(i, 1).data(0) == str(False):
                self.netMap.setRowHidden(i, state)

    def setMask(self, mask):
        print("set Mask to: ", mask)
        self.mask.setText(mask)

    def clearInfo(self):
        self.broadcasting.setText("")
        self.broadcasting.setEnabled(False)

        self.mask.setText("")
        self.mask.setEnabled(False)

        self.net_address.setText("")
        self.net_address.setEnabled(False)
