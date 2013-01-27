module Foo where

import Foreign.C.Types

test :: Int -> Int
test x = x * x

test_hs :: CInt -> CInt
test_hs = fromIntegral . test . fromIntegral

foreign export ccall test_hs :: CInt -> CInt