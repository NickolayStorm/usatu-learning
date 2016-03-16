
-- module Main where

--     data Rome = I | V | X | L | C | D | M deriving (Show, Read)

--     readRome :: String -> Rome
--     readRome = read

--     toInt :: Rome -> Int
--     toInt I = 1
--     toInt V = 5
--     toInt X = 10
--     toInt L = 50
--     toInt C = 100
--     toInt D = 500
--     toInt M = 1000
--     toInt _ = error "undefined char"

--     findNum :: [Int] -> Int
--     findNum = findNum' 0 0 where

--         findNum' s _ [] = s
--         findNum' s prev (r:rs) | r > prev  = findNum' (r - s) r rs
--                                | otherwise = findNum' (r + s) r rs 

--     main :: IO ()
--     main = do
--         --let strs = map (\c -> [c]) "MCMLXXXVIII"
--         print $ (findNum . map (\c -> (toInt . read) [c])) "MCMLXXXVIII"