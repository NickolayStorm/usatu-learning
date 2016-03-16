module Main where

    foo x = (cos x) - x + 1.0

    eps = 0.001
    x0 = 0.0
    x1 = 0.5

    method f = met x1 x0 0 f where
            met :: Float -> Float -> Int -> (Float -> Float) -> (Float, Int)
            met x prev count f | (abs (x - prev)) < eps = (x, count)
                               | True = met (x - (x - prev) * (f x)/((f x) - f(prev))) x (count + 1) f

    main::IO()
    main = do
        print$ method foo