module TAD Expr where

constructores
data Expr =  Var Nat
			|Op Expr
			|Suma Expr Expr
			|Mult Expr Expr
			|Div Expr Expr

operaciones
es_var :: Expr -> Bool
es_op :: Expr -> Bool
--etc
max_var :: Expr -> Nat
resta :: Expr -> Expr -> Expr
mod :: Expr -> Expr -> Expr
eval :: [Int] -> Expr -> Int

ecuaciones
es_var (Var n) = True
es_var (Op e) = False
es_var (Suma e) = False
es_var (Mult e) = False
es_var (Div e) = False

es_op (Var n) = False
es_op (Op e) = True
--etc con las demas (es_suma, es_mult, es_div)

max_var = igual que el anterior final
resta con el op (op es opuesto)
mod e f = resta e (Mult(Div e f) f)
eval js (Var n) = js.n
eval js (Op e) = -(eval js e)
eval js (Suma e) = eval js e + eval js f
		Mult 				*
		Div 				/

implementar con 
type Expr = pointer to node
type node = tuple
				var: Nat
				left: pointer to node
				right: pointer to node
			end
