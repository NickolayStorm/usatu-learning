--Метод дихотомии
module Main where
    import Text.Printf

    eps :: Float
    eps = 0.001
    
    func :: Float -> Float
    func x = x*x - 5*x + 3
    
    --dihotomy :: ()
    dihotomy a b foo | (foo a) * (foo b) > 0 = error "Нет корней на промежутке или на промежутке множество корней"
                     | True = dih a b foo where 
                           dih a b foo | b - a < eps = a
                                       | (foo a) * (foo ((a + b) / 2)) < 0 = dih a ((a + b) / 2) foo
                                       | True = dihotomy ((a + b) / 2) b foo
    main :: IO()
    main = do
        printf "%.2f\n" (dihotomy (0.0) 3.0 func)
