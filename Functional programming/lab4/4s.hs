module Main where

foo [] = []
foo (x:xs) | x == 'a' = x : (foo xs)
		   | x == 'e' = x : (foo xs)
		   | x == 'i' = x : (foo xs)
		   | x == '0' = x : (foo xs)
		   | x == 'u' = x : (foo xs)
		   | x == 'y' = x : (foo xs) 
		   | True = foo xs

--boo :: Eq a => [a]->[(a,Int)]
boo :: [Char]->[(Char, Int)]
boo [] = []
--boo [x] = error (x:[])
boo (x:xs) = (x, (length (x:xs)) - length (filter (x /= ) xs)) : (boo (filter (x /=) xs))

mysort [] = []
mysort (x:xs) = mysort small ++ (x : mysort large) where 
			small = [y | y <- xs, (snd y) <= (snd x)]
			large = [y | y <- xs, (snd y) > (snd x)]

toChar :: [(Char, Int)] -> [Char]
toChar [] = ")"
toChar (x:xs) = '(' : (fst x) : ", " ++ ((show (snd x)) ++ ") " ++ (toChar xs))

main = do
	src <- readFile "file.in"
	writeFile "file.out" (toChar (mysort (boo (foo src))))
