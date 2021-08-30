module Sorting where

import Data.Bits
import Data.List


quickSort :: (Ord a) => [a] -> [a]
quickSort []     = []
quickSort (x:xs) = intercalate [x] . map quickSort . sequence [fst, snd] $ partition (< x) xs


quickSortB :: (Num a, FiniteBits a, Ord a) => [a] -> [a]
quickSortB []        = []
quickSortB l @ (x:_) = flip qsortB' l $ finiteBitSize x
  where
    qsortB' _ []             = []
    qsortB' r l' | r == 0    = concat $ divByBit r l'
                 | otherwise = concat . map (qsortB' $ r-1) $ divByBit r l'

    divByBit r = sequence [fst, snd] . partition ((==0) . (.&. setBit 0 r))


