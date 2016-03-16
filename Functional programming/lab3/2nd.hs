module Main where
foo a | (fst a) + (snd a) < 10 = True
	  | True = False
boo = all foo [(2,2), (6,3), (7,4)]

main = print $ boo
