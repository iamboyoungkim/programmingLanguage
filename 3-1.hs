factors :: Int -> [Int]
factors n = [x | x <- [1..n], n `mod` x == 0]

prime :: Int -> Bool
prime n = factors n == [1, n]
prime 1 = False

findingPrimes :: Int -> Int -> [Int]
findingPrimes a b = take b ([x | x <- [a..], prime x])
