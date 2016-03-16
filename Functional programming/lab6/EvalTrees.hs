module EvalTrees where-- импортируем модуль для работы с рациональными числами
	import Data.Ratio
-- дерево вычислений (или значение - или операция над двумя деревьями)
	data EvalTree = Val Integer | Oper Char EvalTree EvalTree deriving Show
-- операции
	ops = "+-*/"
-- результат вычисления дерева
	eval :: EvalTree -> Rational
	eval (Val x) = toRational x
	eval (Oper '+' x y) = eval x + eval y
	eval (Oper '-' x y) = eval x - eval y
	eval (Oper '*' x y) = eval x * eval y
	eval (Oper '/' x y)
						| eval y == 0 = 0 -- вообще-то говоря неверно
						| otherwise = eval x / eval y
-- множество разбиений множества на подмножества и дополнения
	complements :: [a] -> [([a],[a])]
	complements [] = [([],[])]
	complements (x:xs) = concat $ map (inject x) (complements xs) where
	inject x (xs,ys) = [(x:xs,ys),(xs,x:ys)]
-- всевозможные деревья для заданного списка чисел
	trees :: [Integer] -> [EvalTree]
	trees [] = []
	trees [x] = [Val x]
	trees values = concat
				[allTreesWith op lvs rvs |
								(lvs,rvs) <- complements values, 
								op <- ops, 
								not (null lvs), 
								not (null rvs)
				] where
-- всевозможные деревья для операции и зафиксированных чисел слева и справа
					allTreesWith op lvs rvs = [Oper op lt gt | lt <- trees lvs, gt <- trees rvs]
					showratio x | denominator x == 1 = show (numerator x)
					showratio x | otherwise = show (numerator x)++ "/"++ show (denominator x)
--
--
--
--
--
--
--
--

-- show (numerator x)++ "/"++ show (denominator x)
