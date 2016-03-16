module Main where

myexpr a b c = (tan a - b**c) / (c - sqrt(a))

prod :: [Int] -> Int
prod x = pr x (maximum x) where 
	pr [] _ = 1
	pr (x:xs) m | x == m = pr xs m
				| True = x * (pr xs m)

fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib(n-2)

fact 0 = 1
fact n = n * fact(n-1)

foo n = min (fib(fact n)) (fact(fib(n) - n))


main = do
     nStr <- getLine
     print $ foo (read nStr :: Integer)
     main
