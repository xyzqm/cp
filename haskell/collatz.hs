collatz :: Int -> [Int]
collatz 1 = [1]
collatz n = n : collatz (if even n then n `div` 2 else 3 * n + 1)

main :: IO()
main = do
  n <- readLn :: IO Int
  putStrLn . unwords . map show $ collatz n