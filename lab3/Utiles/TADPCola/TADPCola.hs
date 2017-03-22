-- TAD PCola

module TADPCola where

-- CONSTRUCTORES

data Ord e => PCola e = Vacía
                      | Encolar (PCola e) e
                      deriving Show

-- OPERACIONES

es_vacía :: Ord e => PCola e -> Bool
primero :: Ord e => PCola e -> e        -- se aplica solo a una cola no Vacía
decolar :: Ord e => PCola e -> PCola e   -- se aplica solo a una cola no Vacía

-- ECUACIONES

es_vacía Vacía = True
es_vacía (Encolar q e) = False

primero Vacía = error "No se puede obtener el primero de la cola Vacía"
primero (Encolar q e) | es_vacía q = e
                      | e >= primero q = e
                      | otherwise = primero q

decolar Vacía = error "No se puede decolar la cola Vacía"
decolar (Encolar q e) | es_vacía q = Vacía
                      | e >= primero q = q
                      | otherwise = Encolar (decolar q) e


