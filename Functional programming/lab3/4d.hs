module Main where
import Data.List
foo l = reverse (boo l [] 1) where
	boo [] l _ = l
	boo (x:xs) l num | even x = boo xs (num:l) (num + 1)
					 | True = boo xs l (num + 1)

zoo a | a > 6 = False
	  | True = True

main = print $ snd (span zoo (foo [1,2,3,4,5,7,8,9,10]))
