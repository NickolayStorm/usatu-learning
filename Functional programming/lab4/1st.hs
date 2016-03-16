module Main where
boo = [x^2 + ((x-1)^2)|x<-[1..]]

foo (x:xs) | x `div` 100 /= 0 = x
		   | True = foo xs

main = print $ foo boo
