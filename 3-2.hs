flipCoin :: String -> [Int]
flipCoin coins
    | (length coins) >= 2 = flipCoinRec coins 0
    | otherwise = [0]

flipCoinRec :: String -> Int -> [Int]
flipCoinRec [] cnt = [0]

flipCoinRec [x] cnt
    | x == 'H' = [0]
    | otherwise = [cnt + 1, 0]

flipCoinRec (x:coins) cnt
    | x == head coins = flipCoinRec coins (cnt + 1)
    | otherwise = [cnt + 1] ++ flipCoinRec coins (cnt + 1)
