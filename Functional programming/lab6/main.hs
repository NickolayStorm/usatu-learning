module Main where
	import Prelude
	import BinaryTree
	import EvalTrees
	
	list = [256, 16, 2, 1024, 64, 128, 8,4, 32, 2048, 512]
	
	myUniqueTree = create $ list
	
	
	main = (print $ "Create tree with "++ Prelude.show list ++ ": ")
		 >> (print $ BinaryTree.show myUniqueTree) 
		 >> (print $ "Way to 4: " ++ Prelude.show (getWay myUniqueTree 4)) 
		 >> (print $ "min: " ++ Prelude.show (BinaryTree.min myUniqueTree)) 
		 >> (print $ "max: " ++ Prelude.show (BinaryTree.max myUniqueTree))
	--main = print $ [t | t <-(trees [3,4,5,6]), eval t == 1/3]
