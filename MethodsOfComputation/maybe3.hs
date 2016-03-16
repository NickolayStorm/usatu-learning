module Main where
--import Char(isDigit)
 eps = 0.001	
 e = exp 1
 isEps x old | abs (x - old) > eps = False
			 | True = True
			 
 f x = 2*(e**x) + x - 1
 f' x = 2*(e**x) + 1
 func :: Float -> Float
 func x = x - (f (x))/(f' (x))
 
 iteration :: Float -> Float -> Int -> (Float, Int)
 iteration x old count | not (isEps x old) = iteration (func x) x (count + 1)
				       | True = (x, count)
					 
 main = print $ show (iteration (-0.1) 1 0)
	

