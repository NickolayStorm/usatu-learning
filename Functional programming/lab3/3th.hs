module Main where
import Data.List

p1 x y = even (x + y)

p2 x y = x > y  

p3 x y = x `mod` 4 == y `mod` 4

p4 x y = (x + 2*y) < 8

p5 x y = not (even (max x y))

is [] _ _= False
is (p:ps) x y | p x y = True
			  | True = is ps x y

foo :: [(Int->Int->Bool)]->[(Int, Int)]->[(Int, Int)]
foo ps args = boo ps (unzip args) where
			boo ps args = zoo ps (fst args) (snd args) where
				zoo :: [(Int->Int->Bool)]->[Int]->[Int]->[(Int, Int)]
				zoo _ [] [] = []
				zoo ps (x:xs) (y:ys) | is ps x y = (x,y) : (zoo ps xs ys)
				                     | True = zoo ps xs ys 

main = print $ foo [p1, p2, p3, p4, p5] [(1,1), (1,2), (5,8)]
