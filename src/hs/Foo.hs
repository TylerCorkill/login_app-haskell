module Foo where

import Foreign.C.Types
--import Foreign.C.String

test :: Int -> Int
test x = x * x

test_hs :: CInt -> CInt
test_hs = fromIntegral . test . fromIntegral

foreign export ccall test_hs :: CInt -> CInt

dub :: Int -> Int
dub x = x + x

dub_hs :: CInt -> CInt
dub_hs = fromIntegral . dub . fromIntegral

foreign export ccall dub_hs :: CInt -> CInt

--flip_string :: String -> String
--flip_string str = reverse str

--flip_string_hs :: CString -> CString
--flip_string_hs = flip_string

--foreign export ccall flip_string_hs :: CString -> CString