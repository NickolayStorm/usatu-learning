#!/usr/bin/python

import multiprocessing as mp
from multiprocessing import Process
import ipaddress
import pinging as net_mod


class Controller():
    def __init__(self, Cls):
        print("init")
        self.view = Cls(self)
        self.view.show()
        self.q = mp.Queue()
        self.is_all_pinged = False

    def find_mask_net_addr_broadcast(self, addresses):
        l = len(addresses)
        if l == 1:
            return "255.255.255.255", addresses[0], net_mod.network_address("255.255.255.255", addresses[0])

        if l == 0:
            return "0.0.0.0", "0.0.0.0", "None"

        mask = net_mod.subnet_mask(addresses) #self.find_mask(addresses)
        subnet = net_mod.network_address(mask, addresses[0])
        broadcast = net_mod.broadcast_address(mask, subnet)

        return mask, subnet, broadcast

    def find_mask(self, addresses):
        dest = []
        tempaddrs = []

        for a in addresses:
            tempaddrs.append(a.split("."))

        addresses = tempaddrs
        tempaddrs = []

        for a in addresses:
            tempaddrs.append(list(map(int, a)))

        addresses = tempaddrs

        addr = addresses[0]

        addresses = addresses[1:]

        masks = []
        for a in addresses:
            m = list(map(str, self.find_one_mask(addr, a)))
            masks.append(ipaddress.IPv4Address(".".join(m)))

        return str(min(masks))

    def find_one_mask(self, begin, end):
        dest = []
        for i, j in zip(begin, end):
            dest.append(i ^ j)

        rez = []
        count = 0
        for i in dest:
            if i != 0:
                break
            rez.append(255)
            count += 1

        num = dest[count]

        n = None
        for n in range(1, 9):
            if num >> n == 0:
                break

        num = 0
        for i in range(1, (8 - n)):
            num += 2**(8 - i)

        rez.append(num)
        while len(rez) < 4:
            rez.append(0)

        return rez

    def get_addresses(self):
        return self.q

    def async_ping(self, addresses, timeout):
        net_mod.pg(addresses, self.q, timeout)
        self.is_all_pinged = True
        self.view.update()

    def ping(self, address_begin, address_end, timeout):

        begin = ipaddress.IPv4Address(address_begin)
        end = ipaddress.IPv4Address(address_end)
        addresses = []

        while begin <= end:
            addresses.append(str(begin))
            begin = begin + 1

        p = Process(target=self.async_ping, args=(addresses, timeout))
        p.start()
        self.is_all_pinged = False
        return len(list(addresses))

    # def get_broadcasting(self, addr, mask):
    #     if not mask is str:
    #         mask = str(mask)
    #     return str(net_mod.get_broadcasting(addr, mask))
