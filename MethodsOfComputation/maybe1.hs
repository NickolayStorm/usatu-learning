module Main where
--import Char(isDigit)
 eps = 0.01	
 
 isEps :: [Float]->[Float]->Bool
 isEps [] [] = error "Успех"
 isEps (x:xs) (old:olds) = (abs (x - old) < eps) && (isEps xs olds)
 
 getSolution :: [[Float]]->[Float]->Int->[Float]
 getSolution [] _ _ = []
 getSolution (a:ax) xs i = (compStr a xs i) : (getSolution ax xs (i - 1)) where
							compStr :: [Float]->[Float]->Int->Float
							compStr [] _ _ = 0--error "lolo"
							--compStr [] xs i = error (show i)
							compStr (a:as) (x:xs) i | length (a:as) == i = a + (compStr as xs i)
													| True = a*x + (compStr as xs i)

 iteration :: [[Float]]->[Float]->[Float]
 iteration a xs | isEps xs (getSolution a xs (length a)) = getSolution a xs (length a)
				| True = iteration a (getSolution a xs (length a))
	
 matrix = [[1,1,1],[1,1,1],[1,1,1]] --[[-1/5, 1/5, -1/5, -1/5], [-1/4, 0.5, -0.25, 0,75], [-2/5, 1/5, 1/5, -0.75], [-1/6, -1/3, 1/6, -1/3]]
 main = print $ iteration matrix [0,0,0] --(length matrix)
