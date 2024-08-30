code :: Int -> [String]
code 0 = [""]
code n =
  let a = code (n - 1)
  in (('0':) <$> a) ++ (('1':) <$> reverse a)

main :: IO()
main = do
  n <- readLn :: IO Int
  putStrLn . unlines $ code n
