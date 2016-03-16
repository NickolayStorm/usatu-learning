module Main where
--import Char(isDigit)
 eps = 0.01	
 
 computStr :: [Float]->[Float]-> Float
 computStr [] _ = 0
 --computStr [x] _ = x
 computStr (s:ss) (x:xs) = s*x + (computStr ss xs)
	
 isSufficientAccuracy :: [[Float]] -> [Float] -> Bool
 isSufficientAccuracy (m:ms) xes | eps + 1 + computStr [5,1,-1,1] xes < 0 = True
   								 | True = False
	
 getSolution :: [[Float]]->[Float]->[Float]
 getSolution matrix xes | isSufficientAccuracy matrix xes = xes
						| True = getSolution matrix (computCurrSolution matrix xes (length (head matrix))) where
							    computCurrSolution :: [[Float]]->[Float]->Int->[Float]
							    computCurrSolution [] _ _ = []
							    computCurrSolution (m:mx) xes curr = (computOneX m xes curr)
																: computCurrSolution mx xes (curr - 1) where
																computOneX :: [Float]->[Float]->Int->Float
																computOneX [] _ _ = 0
																computOneX [b] [] _ = b
																computOneX _ [] n = error (show n)
																computOneX (s:ss) (x:xs) curr | curr == length (x:xs) = computOneX (s:ss) xs curr
																							  | True = s*x + computOneX ss xs curr
	
 main = print $ getSolution [[-1/5, 1/5, -1/5, -1/5], [-1/4, 0.5, -0.25, 0,75], [-2/5, 1/5, 1/5, -0.75], [-1/6, -1/3, 1/6, -1/3]] [0,0,0,0]	
