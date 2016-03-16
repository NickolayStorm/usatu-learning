module Main where

romeToInt c | c == 'I' = 1
			| c == 'V'= 5
			| c == 'X' = 10
			| c == 'L' = 50
			| c == 'C' = 100
			| c == 'D' = 500
			| c == 'M' = 1000
			|True = error "undefined char"

romeAnalys :: [Char]->Integer
romeAnalys (x:xs) = parseC xs x (romeToInt x) 0 where --list prev_char num_tail_of_sum sum 
					parseC :: [Char]->Char->Integer->Integer->Integer
					parseC [] _ cs s = cs + s
					parseC (x:xs) prev csum sum = comp (romeToInt x) x xs (romeToInt prev) csum sum where
						comp :: Integer->Char->[Char]->Integer->Integer->Integer->Integer
						comp curr c list prev csum sum | curr > prev = parseC list c (curr - csum) sum
													   | curr < prev = parseC list c curr (sum + csum)--error (show (sum + csum))--
													   | True = parseC list c (csum + curr) sum
													 
binaryParse :: [Char]->Integer
binaryParse l = comput (reverse l) 0 0 where
			comput [] _ sum = sum
			comput (x:xs) num sum | x == '0' = comput xs (num+1) sum
								  | x == '1' = comput xs (num + 1) (sum + 2^num)
								  | True = error "binary parse error"

--foo5 :: [Char]->[Char]->IO						  
foo5 s sl = print $(romeAnalys s) + (binaryParse sl)

main = (foo5 "MCMLXXXVIII" "000000")
