module BinaryTree where
	
	import Prelude
	
	data Tree a = Empty | Node (a) (Tree a) (Tree a) deriving (Show)			  
	
	add :: Ord a => Tree a -> a -> Tree a
	add tree n = case tree of 
					  Empty -> Node n Empty Empty
					  Node node l r | node > n -> Node node (add l n) r
									| node < n -> Node node l (add r n)
									| otherwise -> Node node r l
	create :: Ord a => [a] -> Tree a
	create l = cr Empty l where
			   cr tree [] = tree
			   cr tree (x:xs) = cr (add tree x) xs
			   
	traverce :: Show a => Tree a -> [Char]
	traverce tree = case tree of
					     Empty -> []--"nil "
					     Node n l r -> Prelude.show n ++ " " ++ (traverce l) ++ (traverce r) ++ " "
					
	getWay :: (Ord a, Show a) => Tree a -> a -> [a]
	getWay tree n = case tree of 
					  Empty -> error "elem is not exist"
					  Node node l r | node > n -> node : getWay l n
									| node < n -> node : getWay r n
									| otherwise -> [n]
	show :: Show a => Tree a -> [Char]
	show t = traverce t
	
	min :: Eq a => Tree a -> a
	min Empty = error "min: Tree is undefined."
	min (Node n Empty _) = n
	min (Node _ l r) = BinaryTree.min l
	
	max :: Eq a => Tree a -> a
	max Empty = error "max: Tree is undefined."
	max (Node n Empty _) = n
	max (Node _ l r) = BinaryTree.max r
