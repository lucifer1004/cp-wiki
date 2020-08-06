import Control.Monad

rec :: Int -> [Int] -> [Int] -> [Bool] -> [Int]
rec next (z : zs) os (False : s) = z : rec next zs (z : os) s
rec next [] os (False : s) = next : rec (succ next) [] (next : os) s
rec next zs (o : os) (_ : s) = o : rec next (o : zs) os s
rec next zs [] (_ : s) = next : rec (succ next) (next : zs) [] s
rec _ _ _ _ = []

solve :: IO ()
solve = do
  getLine
  s <- map (== '1') <$> getLine
  let a = rec 1 [] [] s
  print $ maximum a
  putStrLn $ unwords $ map show a

main :: IO ()
main = do
  getLine >>= flip replicateM_ solve . read
  