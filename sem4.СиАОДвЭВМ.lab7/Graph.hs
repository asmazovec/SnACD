module Graph where

import qualified Data.Map as M
import qualified Data.Set as S


-- | Graph by Junctions
type GJ = M.Map Node (S.Set Node)

type Edge = (Int, Int)
type Node = Int

-- 1
addNode :: Node -> GJ -> GJ
addNode n g = M.insertWith (flip const) n S.empty g

-- 2
addEdge :: Edge -> GJ -> GJ
addEdge (n1, n2) g = 
    M.insertWith S.union n2 (S.singleton n1) $
    M.insertWith S.union n1 (S.singleton n2) g

-- 3
remNode :: Node -> GJ -> GJ
remNode n g = M.map (S.delete n) $ M.delete n g

-- 4
isEdge :: Edge -> GJ -> Bool
isEdge (n1, n2) g = S.member n2 $ M.findWithDefault S.empty n1 g

-- 5
countNodes :: GJ -> Int
countNodes = length . M.keys

-- 6
countEdges :: GJ -> Int
countEdges = (`div` 2) . sum . map S.size . M.elems

-- 7
isEmpty :: GJ -> Bool
isEmpty = M.null












