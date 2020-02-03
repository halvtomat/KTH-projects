defmodule Test do
    
    #Compute the double of a number
    def double(n) do
        n*2
    end

    #Fahrenheit to Celsius conversion
    def f2c(n) do
        (n-32)/1.8
    end

    #Area of rectangle
    def rect(a,b) do
        a * b
    end

    #Area of square
    def sqr(a) do
        rect(a,a)
    end

    def circ(r) do
        r*r*3.1415
    end

    #Recursive multiplication v1
    def product(m, n) do
        if m == 0 do
            0
        else
            n + product(m-1, n)
        end
    end

    #v2
    def product_case(m, n) do
        case m do
            0 ->
                0
            _ ->
                n + product_case(m-1, n)
        end
    end

    #v3
    def product_cond(m, n) do
        cond do
            m == 0 ->
                0
            true ->
                n + product_cond(m-1,n)
        end
    end

    #v4
    def product_clauses(0, _) do 0 end
    def product_clauses(m, n) do
        n + product_clauses(m-1, n)
    end

    #Exponential function using only recursive addition
    def exp(x, n) do
        case n do
            0 ->
                1
            _ ->
                product(x, exp(x, n-1))
        end
    end

    #Faster version of exp
    def exp_fast(x, n) do
        case n do
            0 ->
                1
            1 ->
                x
            rem(n, 2) == 0 ->
                exp_fast(x, n/2) * exp_fast(x, n/2)
            rem(n, 2) == 1 ->
                exp_fast(x, n-1) * x
        end
    end
            
end