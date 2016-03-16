module Main where
import Data.List


pminone [] = []
pminone (x:xs) = ((snd x), (fst x)) : pminone xs

composition fs gs = map (mapping gs) fs where
					mapping :: Eq a => [(a,a)]->(a,a)->(a,a)
					mapping [] g = g
					mapping (p:ps) g | (fst p) == (snd g) = ((fst g), (snd p))
								     | True = mapping ps g


proect1 [] = []
proect1 (p:ps) = nub ((fst p) : (proect1 ps))

proect2 [] = []
proect2 (p:ps) = nub ((snd p) : (proect1 ps))


decart _ [] = []
decart xs (y:ys) = (foo xs y) ++ (decart xs ys) where
				foo [] _ = []
				foo (x:xs) y = (x, y) : (foo xs y)

main = do 
	print $ "P"
	print $ [(1,2),(2,3),(3,1),(2,2),(3,2)]
	print $ "P^-1" 
	print $ pminone [(1,2),(2,3),(3,1),(2,2),(3,2)]
	print $ "P.P"
	print $ composition [(1,2),(2,3),(3,1),(2,2),(3,2)] [(1,2),(2,3),(3,1),(2,2),(3,2)]
	print $ "(P^-1).P"
	print $ composition (pminone [(1,2),(2,3),(3,1),(2,2),(3,2)]) [(1,2),(2,3),(3,1),(2,2),(3,2)]
	print $ "pr1((P^-1).P) x pr2(P^-1).P"
	print $ decart (proect1 (composition (pminone [(1,2),(2,3),(3,1),(2,2),(3,2)]) [(1,2),(2,3),(3,1),(2,2),(3,2)])) (proect1 (composition (pminone [(1,2),(2,3),(3,1),(2,2),(3,2)]) [(1,2),(2,3),(3,1),(2,2),(3,2)]))
