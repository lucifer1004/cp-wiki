import Control.Monad
import Data.Bool
import Data.List

solve :: IO ()
solve = do
  getLine
  as <- map read . words <$> getLine
  putStrLn $ bool "NO" "YES" $ all (<= 1) $ zipWith subtract <*> tail $ sort as

main :: IO ()
main = do
  getLine >>= flip replicateM_ solve . read
  