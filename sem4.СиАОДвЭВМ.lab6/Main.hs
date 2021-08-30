import Sorting 


main :: IO ()
main = do
    list <-  quickSort
          .  map (read :: String -> Int) 
          .  lines 
         <$> readFile "I"
    return ()
    writeFile "Res" $ show list
    return ()
