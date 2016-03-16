module Main where
foo a | even (fst a) = False
	  | True = True
boo = any foo [(2,2), (6,3), (7,4)]

main = print $ boo
