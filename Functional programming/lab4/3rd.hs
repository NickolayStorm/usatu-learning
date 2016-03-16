module Main where
boo :: Integral a => [a] -> a
boo (x:xs) | --((x `div` 100 + x `mod` 10) `mod` 2 == 0) && (((x `div` 100 + x `mod` 10) `div` 2) == ((x `div` 10) `mod` 10)) = x
		    (x `mod` 11 == x `mod` 6) && ((x `div` 6) /= 0) && ((x `div` 100 + x `mod` 10) `mod` 2 == 0) && (((x `div` 100 + x `mod` 10) `div` 2) == ((x `div` 10) `mod` 10)) = x
		   | True = boo xs

main = print $ boo [100..]
