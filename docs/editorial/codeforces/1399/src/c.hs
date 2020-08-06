import Control.Monad
import Data.List

teamsWithSum :: Int -> [Int] -> Int
teamsWithSum s ws = f ws (reverse ws) `div` 2
  where
    f (a : as) (b : bs)
      | a + b < s = f as (b : bs)
      | a + b == s = 1 + f as bs
      | otherwise = f (a : as) bs
    f _ _ = 0

solve :: IO ()
solve = do
  n <- read <$> getLine
  ws <- sort . map read . words <$> getLine
  print $ maximum [teamsWithSum s ws | s <- [2 .. 2 * n]]

main :: IO ()
main = do
  getLine >>= flip replicateM_ solve . read
  