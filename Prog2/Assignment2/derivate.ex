defmodule Derivate do 

    #{:add, {:mul, {:const, 2}, {:var, :x}}, {:const, 3}}
    # 2x + 3
    #{:add, {:add, {:mul, {:const, 4}, {:exp, {:var, :x}, {:const, 2}}}, {:mul, {:const, 2}, {:var, :x}}}, {:const, 5}}
    # 4x^2 + 2x + 5

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



    def simplify({:const, a}), do: {:const, a}
    def simplify({:var, a}), do: {:var, a}

    def simplify({:mul, {:const, 0}, _}), do: {:const, 0}
    def simplify({:mul, _, {:const, 0}}), do: {:const, 0}
    def simplify({:mul, {:const, a}, {:const, b}}), do: {:const, a*b}

    def simplify({:mul, {:mul, {:const, a}, e1}, {:const, b}}), do: simplify({:mul, {:const, a*b}, simplify(e1)})
    def simplify({:mul, {:const, b}, {:mul, {:const, a}, e1}}), do: simplify({:mul, {:const, a*b}, simplify(e1)})
    def simplify({:mul, {:mul, e1, {:const, a}}, {:const, b}}), do: simplify({:mul, {:const, a*b}, simplify(e1)})
    def simplify({:mul, {:const, b}, {:mul, e1, {:const, a}}}), do: simplify({:mul, {:const, a*b}, simplify(e1)})

    def simplify({:mul, e1, {:const, a}}), do: {:mul, simplify(e1), {:const, a}}
    def simplify({:mul, {:const, a}, e2}), do: {:mul, {:const, a}, simplify(e2)}
    def simplify({:mul, e1, e2}), do: simplify({:mul, simplify(e1), simplify(e2)})

    def simplify({:add, {:const, 0}, e2}), do: simplify(e2)
    def simplify({:add, e1, {:const, 0}}), do: simplify(e1)
    def simplify({:add, {:const, a}, {:const, b}}), do: {:const, a+b}
    
    def simplify({:add, {:add, {:const, a}, e1}, {:const, b}}), do: simplify({:add, {:const, a+b}, simplify(e1)})
    def simplify({:add, {:const, b}, {:add, {:const, a}, e1}}), do: simplify({:add, {:const, a+b}, simplify(e1)})
    def simplify({:add, {:add, e1, {:const, a}}, {:const, b}}), do: simplify({:add, {:const, a+b}, simplify(e1)})
    def simplify({:add, {:const, b}, {:add, e1, {:const, a}}}), do: simplify({:add, {:const, a+b}, simplify(e1)})

    def simplify({:add, {:const, a}, e2}), do: {:add, {:const, a}, simplify(e2)}
    def simplify({:add, e1, {:const, a}}), do: {:add, simplify(e1), {:const, a}}
    def simplify({:add, e1, e2}), do: simplify({:add, simplify(e1), simplify(e2)})

    def simplify({:exp, e1, {:const, 1}}), do: simplify(e1)
    def simplify({:exp, _, {:const, 0}}), do: {:const, 1}
    def simplify({:exp, e1, e2}), do: {:exp, simplify(e1), simplify(e2)}



    def readify({:const, a}), do: IO.write(a)
    def readify({:var, a}), do: IO.write(a)
    def readify({:add, e1, e2}) do 
        readify(e1)
        IO.write(" + ")
        readify(e2)
    end
    def readify({:mul, e1, e2}) do
        readify(e1)
        readify(e2)
    end
    def readify({:exp, e1, e2}) do
        IO.write("(")
        readify(e1)
        IO.write(" ^ ")
        readify(e2)
        IO.write(")")
    end

    def derivate(e, v) do
        e = deriv(e, v)
        e = simplify(e)
        readify(e)
    end
end