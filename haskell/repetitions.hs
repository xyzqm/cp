runs :: String -> [Int]
runs [] = [0]
runs [_] = [1]
runs (x:y:xs) = if x == y
  then let s = runs (y:xs) in (head s + 1):tail s
  else 1:runs (y:xs)

main :: IO()
main = do
  s <- getLine
  print $ maximum (runs s)