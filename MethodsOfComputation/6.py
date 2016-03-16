#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

eps = 0.0001

def dfdx(x,y):
	return 16 + math.exp(1.99*x*x + 0.26*y*y)*3.98*x
	#return 3 + math.exp(0.02*x*x+0.13*y*y)*0.04*x
	#return 10  + math.exp(0.94*x*x+0.2*y)*1.88*x
	
def dfdy(x,y):
	return 0.1 + math.exp(1.99*x*x + 0.26*y*y)*0.52*y
	#return -1.2 + math.exp(0.02*x*x+0.13*y*y)*0.26*y
	#return -0.5 + math.exp(0.94*x*x+0.2*y)*0.2*y
	
def f(x,y):
	# print(x)
	# print(y)
	#a = 3*x - 1.2*y + math.exp(0.02*x*x+0.13*y*y)
	a = 16 * x + 0.1 * y + math.exp(1.99 * x * x + 0.26 * y * y)
	return a
	#return 3*x - 1.2*y + math.exp(0.02*x*x+0.13*y*y)
	#return 10*x - 0.5*y + math.exp(0.94*x*x+0.2*y*y)

def stop(x,y):
	#return  (abs(dfdx(x,y))<eps/2) and (abs(dfdy(x,y))<eps/2)
	return math.sqrt(dfdx(x,y)*dfdx(x,y)+dfdy(x,y)*dfdy(x,y)) < eps
	
def main():
	
	x,y,a = 0,0,1
	
	x_old, y_old = x,y
	
	while not(stop(x,y)):
		#print("gdcgdcg")
		x_old, y_old = x,y
		x = x_old - a*dfdx(x_old,y_old)
		y = y_old - a*dfdy(x_old,y_old)
		if f(x,y)>f(x_old,y_old):
			a = a/2
			print(a)
			x, y = x_old, y_old
		else:
			print("X = %f Y = %f a = %f"%(x,y,a))
			print("f(x,y) = %f"%f(x,y))
		
	return 0

if __name__ == '__main__':
	main()

