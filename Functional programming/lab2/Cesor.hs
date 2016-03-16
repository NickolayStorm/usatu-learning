module Main where
import Data.Char
chipr :: [Char]->[Char]->Int->[Char]
chipr [] y _ = y
chipr (x:xs) y d = chipr xs ((addTab x d):y) d where
				addTab :: Char->Int->Char
				addTab c d | d + (ord c) > 122 = chr (d + (ord c) - 74)
						   | d + (ord c) < 48 = chr (d + (ord c) + 74)
					       | True = chr (d + (ord c))

ch :: [Char]->Bool->[Char]
ch ls b | b = chipr ls [] 9
		| True = chipr ls [] (-9) 

--chr
--48 - 122
main = print $ ch "hwd" True
