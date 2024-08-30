
readArray :: (Read a) => IO [a]
readArray = do
  l <- getLine
  return $ read <$> words l

main :: IO()
main = do
  n <- readLn :: IO Int
  a <- readArray :: IO [Int]
  print $ n * (n + 1) `div` 2 - sum a