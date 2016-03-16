#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math
from prettytable import PrettyTable

x0, y0 = 0, 1
xn = 1
xs = []

func = lambda x,y : x*math.e**(-x**2) - 2*x*y
create_xs = lambda x0,h: [x0+i*h for i in range(0,int(1/h)+1)]

def euler():
	ys = [y0]
	previous = y0
	for x in xs:
		y = previous + h*func(x,previous)
		ys.append(y)
		previous = y
	return dict(zip(xs,ys))

def runge_kutta():
	ys = [y0]
	previous = y0
	for x in xs:
		k1 = func(x,previous)
		k2 = func(x+h/2,previous+h*k1/2)
		k3 = func(x+h/2,previous+h*k2/2)
		k4 = func(x+h,previous+h*k3)
		y = previous+h*(k1+2*k2+2*k3+k4)/6
		ys.append(y)
		previous = y
	return dict(zip(xs,ys))

def exact_solution():
	ys = []
	solution = lambda x: math.e**(-x**2)*((x**2)/2 + 1)
	for x in xs:
		y = solution(x)
		ys.append(y)
	return dict(zip(xs,ys))

def main():
	global xs
	global h
	h = 0.1
	xs = create_xs(x0,h)
	table1 = PrettyTable(["Xi","Метод Эйлера (h=0,1)","Метод Рунге-Кутта (h=0,1)","Точное решение"])
	rk = runge_kutta()
	es = exact_solution()
	e = euler()
	for x in xs:
		table1.add_row(["%.1f"%x,"%f"%e[x],"%f"%rk[x],"%f"%es[x]])	
	print(table1)
	
	h = 0.05
	xs = create_xs(x0,h)
	table2 = PrettyTable(["Xi","Метод Эйлера (h=0,05)","Метод Рунге-Кутта (h=0,05)","Точное решение"])
	rk = runge_kutta()
	es = exact_solution()
	e = euler()
	for x in xs:
		table2.add_row(["%.2f"%x,"%f"%e[x],"%f"%rk[x],"%f"%es[x]])
	print(table2)	

	
	return 0

if __name__ == '__main__':
	main()
