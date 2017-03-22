import TADArbolBinario
import TADPosicion

es_nodo :: ArbolBinario e -> Bool
es_nodo a = not (es_vacío a)

hoja :: e -> ArbolBinario e
hoja e = Nodo Vacío e Vacío

primero = hoja 5
segundo = hoja 2
tercero = Nodo primero 4 segundo
cuarto = Nodo tercero 7 tercero

es_hoja :: ArbolBinario e -> Bool
es_hoja Vacío = False
es_hoja (Nodo i r d) = es_vacío i && es_vacío d

es_izquierdo_de :: Eq e => ArbolBinario e -> ArbolBinario e -> Bool
a `es_izquierdo_de` b = es_nodo b && a == izquierdo b

es_derecho_de :: Eq e => ArbolBinario e -> ArbolBinario e -> Bool
a `es_derecho_de` b = es_nodo b && a == derecho b

es_hijo_de :: Eq e => ArbolBinario e -> ArbolBinario e -> Bool
a `es_hijo_de` b = a `es_izquierdo_de` b || a `es_derecho_de` b

es_ancestro_de :: Eq e => ArbolBinario e -> ArbolBinario e -> Bool
a `es_ancestro_de` b = a == b || (es_nodo a && (izquierdo a `es_ancestro_de` b
                                                || derecho a `es_ancestro_de` b))

es_descendiente_de :: Eq e => ArbolBinario e -> ArbolBinario e -> Bool
a `es_descendiente_de` b = b `es_ancestro_de` a

altura :: ArbolBinario e -> Int
altura Vacío = 0
altura (Nodo i r d) = 1 + altura i `max` altura d

subarbol :: ArbolBinario e -> Posicion -> ArbolBinario e
subarbol a R = a
subarbol a (I p) = subarbol (izquierdo a) p
subarbol a (D p) = subarbol (derecho a) p

posiciones :: ArbolBinario e -> [Posicion]
posiciones Vacío = []
posiciones (Nodo i r d) = R : map I (posiciones i) ++ map D (posiciones d)

-- la siguiente operación se aplica a un arbol a y una posicion p tal que p pertenece a posiciones de a
elemento :: ArbolBinario e -> Posicion -> e
elemento a p = raíz (subarbol a p)

