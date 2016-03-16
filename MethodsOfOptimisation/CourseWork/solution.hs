module Main where
    import Data.List
    --import Data.Ord (comparing)
    import Debug.Trace
    import Data.Maybe

    type W = Int --веса буквой w
    type P = Int -- стоимость p
    type I = Int --рюкзаки буквой i
    type J = Int --контейнеры и т.д

    --maxW = 1000

    -- для удаления итого элемента 
    -- ЩиТо поделать
    delByInd :: Int -> [a] -> [a]
    delByInd i list = take i list ++ drop (i + 1) list

    -- хотя буду просто пользоваться заменой
    substitude::Int -> a -> [a] -> [a]
    substitude i el xs = take i xs ++ [el] ++ drop (i + 1) xs

    --вспомогательная функция для троек
    mfst (x, _, _) = x

    msnd (_, x, _) = x

    mthd (_,_,x) = x

--Cargo
    --типичный груз, просто номера и веса, 
    --до порядку, 
    --Bool -- положен ли он уже?
    type Cargo = (J, W) 
    
    
    --example :: makeCargo [1, 3, 4, 5, 7, 6] 
    -- -> 
    --[(0, False, 1),(1, False, 3),(2, False, 4),(3, False, 5),(4, False, 7),(5, False, 6)]
    makeCargo::[W] -> [Maybe Cargo]
    makeCargo = makeCargo' 0 
        where
            makeCargo'::J -> [W] -> [Maybe Cargo]
            makeCargo' _ [] = []
            makeCargo' n (w:ws) = Just (n, w) : makeCargo' (n + 1) ws

--Knapsack
    -- номер, список грузов, вмещаемость
    type Knapsack = (I, [J], W)
    makeKnapsack = makeKnapsack' 0 
        where
            makeKnapsack'::Int -> [W] -> [Knapsack]
            makeKnapsack' _ [] = []
            makeKnapsack' n (w:ws) = (n, [], w) : makeKnapsack' (n + 1) ws
--Cost
    -- i номер рюкзака, j номер груза, стоимость
    type Cost = (I, J, P)
    
    --сгенерируем таблицу стоимостей из матрицы (путь джедая)
    --в матрице i -- сроки -- рюкзаки
    makeCost::[[P]] -> [Cost]
    makeCost = makeCostI 0
            where
        makeCostI _ [] = []
        makeCostI i (x:xs) = makeCostIJ i 0 x ++ makeCostI (i + 1) xs
                where
            makeCostIJ i j [] = []  
            makeCostIJ i j (w:ws) = (i, j, w) : makeCostIJ i (j + 1) ws


    ordCosts (_, _, p1) (_, _, p2) = compare p2 p1 --reverce sort

--Algorythm
    -- СРОЧНО продумать, а что будет, 
    -- если у нас некуда будет засунуть 
    -- максимальный элемент по тяжести? 
    -- логично помечать его типа он уже есть 
    -- #хитрый_план

    -- Нужна функция, которая будет засовывать и помечать ?? и типа Maybe

-- рекурсия по уменьшению списка Cost, такие дела

--  веса буквой w
--  стоимость p
--  рюкзаки i
--  предметы j
--  Cargo = (J, Bool, W)
--  Cost = (I, J, P)
--  Knapsack = (I, [J], W)
 --   unpack::Maybe a -> a
    unpack (Just a) = a
    unpack _ = undefined

    findSoluton :: [Maybe Cargo] -> [Knapsack] -> [Cost] -> [Knapsack]
    findSoluton _ k [] = k -- если Cost кончился = все Cost засунуты или их невозможно засунуть => выходим
    findSoluton cargo ks ((i,j,p):cs) | isNothing (cargo!!j) = findSoluton cargo ks cs --если предмет уже положен в рюкзак, идём дальше
                                      | mthd (ks!!i) >= snd (unpack (cargo!!j)) = let --типа если предмет влезает в остаток весаё
                                            (_, cargoW) = unpack(cargo!!j) --берём вес
                                            newCargo = substitude j Nothing cargo --помечаем предмет как сложенный
                                            -- в i рюкзак положим в список и уменьшим оставшийся вес
                                            (ki, clst, w) = ks!!i
                                            newKnapsack = substitude i (ki, j:clst, w - cargoW) ks
                                            in findSoluton newCargo newKnapsack cs
                                      | otherwise = findSoluton cargo ks cs

                                      --предмет не влез, продолжаем
--Input Data
    matrixOfCosts = [
        [1, 2, 3, 2, 5, 8],
        [4, 10, 6, 3, 4, 7],
        [7, 8, 9, 2, 9, 3]]
    cargos = [1, 3, 4, 5, 7, 6]
    knaps = [10,10,7]

    greedyAlg cs ks m = findSoluton (makeCargo cs) (makeKnapsack ks) (sortBy ordCosts (makeCost m))
    
    computeSum::[Knapsack] -> Int
    computeSum [] = 0
    computeSum ((ki, js,_):ks) = computeSum ks + sum (map ((matrixOfCosts!!ki)!!) js)

    main::IO()
    main = print $ trace "Сумма стоимости выбранных предметов оказалась: " (computeSum (greedyAlg cargos knaps matrixOfCosts))
    --sortBy ordCosts (makeCost matrixOfCosts)
    --print $ makeKnapsack [1, 3, 4, 5, 7, 6] 
    --undefined --do
        --print "HelloWorld"