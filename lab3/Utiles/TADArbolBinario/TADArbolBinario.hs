-- TAD ÁrbolBinario

module TADArbolBinario where

-- CONSTRUCTORES

data ArbolBinario e = Vacío
                    | Nodo (ArbolBinario e) e (ArbolBinario e)
                    deriving Eq

-- OPERACIONES

es_vacío :: ArbolBinario e -> Bool
raíz :: ArbolBinario e -> e                     -- se aplica solo a un árbol no Vacío
izquierdo :: ArbolBinario e -> ArbolBinario e   -- se aplica solo a un árbol no Vacío
derecho :: ArbolBinario e -> ArbolBinario e     -- se aplica solo a un árbol no Vacío

-- ECUACIONES

es_vacío Vacío = True
es_vacío (Nodo i r d) = False

raíz Vacío = error "No se puede obtener la raíz del árbol vacío"
raíz (Nodo i r d) = r

izquierdo Vacío = error "No se puede obtener el subárbol izquierdo del árbol vacío"
izquierdo (Nodo i r d) = i

derecho Vacío = error "No se puede obtener el subárbol derecho del árbol vacío"
derecho (Nodo i r d) = d

instance Show e => Show (ArbolBinario e) where
  show Vacío = "<>"
  show (Nodo Vacío r Vacío) = "<" ++ show r ++ ">"
  show (Nodo i r d) = "<" ++ show i ++ "," ++ show r ++ "," ++ show d ++ ">"

