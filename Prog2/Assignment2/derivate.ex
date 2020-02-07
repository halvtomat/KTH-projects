defmodule Derivate do 

    @type literal() ::  {:const, number()}
                    |   {:const, atom()}
                    |   {:var, atom()}

    @type expr()    ::  {:add, expr(), expr()}
                    |   {:mul, expr(), expr()}
                    |   {:exp, expr(), expr()}
                    |   literal()
    
    def deriv({:const, _}, _), do: {:const, 0}
    def deriv({:var, v}, v), do: {:const, 1}
    def deriv({:var, _}, _), do: {:const, 0}
    def deriv({:mul, e1, e2}, v), do: {:add, {:mul, deriv(e1, v), e2}, {:mul, e1, deriv(e2, v)}}
    def deriv({:add, e1, e2}, v), do: {:add, deriv(e1, v), deriv(e2, v)}
    def deriv({:exp, e1, e2}, _), do: {:mul, e2, {:exp, e1, {:add, e2, {:const, -1}}}}

    #def simplify({:mul, e1, e2}) do
    #    cond 

end