-- TAD Posicion

module TADPosicion where

-- CONSTRUCTORES

data Posicion = R
              | I Posicion
              | D Posicion
              deriving (Eq, Show)

-- OPERACIONES

-- ECUACIONES


