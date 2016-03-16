module Main where
import Data.List



main = print $ [((x^2) + (y^2)) | x<-[1..10], y<-[1..10], x/=y ]
