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
        cond do
            n == 0 ->
                1
            n == 1 ->
                x
            rem(n, 2) == 0 ->
                exp_fast(x, div(n,2)) * exp_fast(x, div(n,2))
            rem(n, 2) == 1 ->
                exp_fast(x, n-1) * x
        end
    end

    #return the n'th element of the list l
    def nth(0, [h | _]) do h end
    def nth(n, [_ | t]) do nth(n-1, t) end

    #return the number of elements in the list l
    def len(l) do len(l,0) end
    def len([_ | t],n) do len(t, n+1) end
    def len([], n) do n end

    #return the sum of all the elements in the list l
    def sum([h | t]) do sum(t, h) end
    def sum([h | t], n) do sum(t, n+h) end
    def sum([], n) do n end

    #return a list where all elements are duplicated
    def duplicate([h | t]) do [h , h | duplicate(t)] end
    def duplicate([]) do [] end

    #add the element x to the list l if it is not in the list
    def add(x, [x | t]) do [x | t] end
    def add(x, [h | t]) do [h | add(x,t)] end
    def add(x, []) do [x] end

    #remove all occurances of x in l
    def remove(x, [x | t]) do remove(x,t) end
    def remove(x, [h | t]) do [h | remove(x,t)] end
    def remove(_, []) do [] end

    #return a list of unique elements in the list l
    def unique([h | t]) do 
        t = remove(h, t)
        [h | unique(t)]
    end
    def unique([]) do [] end

    #return a list containing list of equal elements
    def pack([h | t]) do
        r = pack(h, t)
        t = remove(h, t)
        [[h | r] | pack(t)]
    end
    def pack([]) do [] end
    def pack(x, [x | t]) do [x | pack(x, t)] end
    def pack(x, [_ | t]) do pack(x, t) end
    def pack(_, []) do [] end

    #return a list where the order of elements is reversed
    def reverse([h | t]) do reverse(t) ++ [h] end
    def reverse([]) do [] end

    

end 