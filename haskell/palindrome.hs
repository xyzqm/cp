import Data.Map (Map, adjust, toList, fromList)
import Data.List
freq :: String -> Map Char Int
freq = foldr (adjust (1 +)) $ fromList [(c, 0) | c <- ['A'..'Z']]

cmp :: (Char, Int) -> (Char, Int) -> Ordering
cmp (_, b) (_, d) = if even b then LT else GT
build :: [(Char, Int)] -> String
build [] = ""
build ((a, b):xs) = if even b
  then
    let s = replicate (b `div` 2) a
    in s ++ build xs ++ s
  else 
    replicate b a
solve :: String -> String
solve s =
  let f = sortBy cmp (toList $ freq s) in build f

main :: IO()
main = do
  s <- getLine
  let f = freq s
  let r = if length [x | x@(a, b) <- toList f, odd b] > 1
      then "NO SOLUTION"
      else solve s
  putStrLn r