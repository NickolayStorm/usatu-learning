module Main where
import Data.List

comutative f x y = f x y == f y x

foo [] _ = []
foo (f:fs) val = (comutative f (fst val) (snd val)) : foo fs val

zoo x y = x + y

add x y = x + y

main = print $ foo [div, mod, add] (2,5)
