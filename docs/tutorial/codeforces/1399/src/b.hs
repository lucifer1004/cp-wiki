import Control.Monad

solve :: IO ()
solve = do
  getLine
  as <- map read . words <$> getLine
  bs <- map read . words <$> getLine
  let moves = zip (subtract (minimum as) <$> as) (subtract (minimum bs) <$> bs)
  print $ sum $ (\(a, b) -> a + b - min a b) <$> moves

main :: IO ()
main = do
  getLine >>= flip replicateM_ solve . read
  