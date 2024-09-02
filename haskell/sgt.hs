-- unfortunately TLE's on CSES :(
import Control.Monad
import Data.Monoid

data SGT a where
  Node :: Monoid a => a -> Int -> Int -> SGT a -> SGT a -> SGT a
  Leaf :: SGT a

node :: SGT a -> SGT a -> SGT a
node lt@(Node sl l _ _ _) rt@(Node sr _ r _ _) = Node (sl <> sr) l r lt rt

build :: (Monoid a) => Int -> Int -> [a] -> SGT a
build l r [x] = Node x l r Leaf Leaf
build l r xs = let m = (l + r) `div` 2
                   lt = build l m (take (m - l) xs)
                   rt = build m r (drop (m - l) xs)
               in node lt rt

query :: SGT a -> Int -> Int -> a
query (Node s l r lt rt) ql qr -- query range [ql, qr)
  | ql <= l && r <= qr = s
  | qr <= l || r <= ql = mempty
  | otherwise = query lt ql qr <> query rt ql qr

main :: IO()
main = do
  [n, q] <- map read . words <$> getLine
  a <- map (Sum . read) . words <$> getLine :: IO [Sum Int]
  let sgt = build 0 n a
  replicateM_ q $ do
    [l, r] <- map read . words <$> getLine
    print $ getSum $ query sgt (l - 1) r
