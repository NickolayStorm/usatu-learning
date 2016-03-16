module Main where
boo = take 10 (iterate(\x -> if (not (even x)) then x*2 else x - 3) 1)

main = print $ boo
