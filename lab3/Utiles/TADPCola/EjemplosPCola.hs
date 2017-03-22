import TADPCola

-- EJEMPLOS

primera = Vacía
segunda = Encolar primera 2
tercera = Encolar segunda 5

todos = Vacía : concatMap (\q -> map (Encolar q) [0..9]) todos

pcola_sort :: Ord a => [a] -> [a]
pcola_sort as = reverse (decolar_todo (encolar_todo as))
              where encolar_todo [] = Vacía
                    encolar_todo (a:as) = Encolar (encolar_todo as) a
                    decolar_todo Vacía = []
                    decolar_todo q = primero q : decolar_todo (decolar q)

instance Ord e => Eq (PCola e) where
  Vacía == Vacía = True
  Vacía == Encolar q e = False
  Encolar q e == Vacía = False
  q1 == q2 = primero q1 == primero q2 && decolar q1 == decolar q2

cierto = segunda == decolar tercera

cierto2 = tercera == Encolar (Encolar Vacía 5) 2


