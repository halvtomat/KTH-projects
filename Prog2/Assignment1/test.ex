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

    #reverse_fast (tail recursion)
    def reverse_fast(l) do reverse_fast(l, []) end
    def reverse_fast([], r) do r end
    def reverse_fast([h | t], r) do reverse_fast(t, [h | r]) end

    #insertion sort
    def insert(e, []) do [e] end
    def insert(e, [h | t]) do
        if h > e do
            [e , h | t]
        else 
            [h | insert(e, t)]
        end
    end

    #insertion sort cont.
    def isort(l) do isort(l, []) end
    def isort([h | t], s) do isort(t, insert(h,s)) end
    def isort([], s) do s end

    #merge sort
    def msort(l) do
        case l do
            [a | []] ->
                [a]
            [] ->
                []
            [_ | _] ->
                {l1, l2} = msplit(l, [], [])
                merge(msort(l1), msort(l2))
        end
    end

    #merges ort cont.
    def merge([], l) do l end
    def merge(l, []) do l end
    def merge([h1 | t1], [h2 | t2]) do
        if h1 < h2 do
            [h1 | merge(t1, [h2 | t2])]
        else
            [h2 | merge([h1 | t1], t2)]
        end
    end

    #merge sort cont.
    def msplit([], l1, l2) do {l1, l2} end
    def msplit([h | t], l1, l2) do msplit(t, [h | l2], l1) end

    #quicksort
    def qsort([]) do [] end
    def qsort([a | []]) do [a] end
    def qsort([p | l]) do 
        {l1, l2} = qsplit(p, l, [], [])
        l1 = qsort(l1)
        l2 = qsort(l2)
        l1 ++ [p | l2]
    end

    #quicksort cont.
    def qsplit(_, [], l1, l2) do {l1, l2} end
    def qsplit(p, [h | t], l1, l2) do
        if p < h do
            qsplit(p, t, l1, [h | l2])
        else
            qsplit(p, t, [h | l1], l2)
        end
    end

    #converts decimal to binary
    def to_binary(0) do [] end
    def to_binary(n) do to_binary(div(n,2)) ++ [rem(n,2)] end

    #better conversion
    def to_better(n) do to_better(n, []) end
    def to_better(0, b) do b end
    def to_better(n, b) do to_better(div(n,2), [rem(n,2) | b]) end

    #converts back from binary to deciamal
    def to_integer(x) do to_integer(x, 0) end
    def to_integer([], n) do n end
    def to_integer([x | r], n) do to_integer(r, n + product( rem(x,2), exp(2, length(r)))) end
   
    #Benchmark for reverse function
    def bench() do
    ls = [16, 32, 64, 128, 256, 512]
    n = 100
    # bench is a closure: a function with an environment.
    bench = fn(l) ->
    seq = Enum.to_list(1..l)
    tn = time(n, fn -> reverse_fast(seq) end)
    tr = time(n, fn -> reverse(seq) end)
    :io.format("length: ~10w nrev: ~8w us rev: ~8w us~n", [l, tn, tr])
    end
    # We use the library function Enum.each that will call
    # bench(l) for each element l in ls
    Enum.each(ls, bench)
    end

    # Time the execution time of the a function.
    def time(n, fun) do
        start = System.monotonic_time(:milliseconds)
        loop(n, fun)
        stop = System.monotonic_time(:milliseconds)
        stop - start
    end

    # Apply the function n times.
    def loop(n, fun) do
        if n == 0 do
            :ok
        else
            fun.()
            loop(n - 1, fun)
        end
    end

    #Fibonacci number generator (aware of super slow speed, but it looks nice and is simple)
    def fib(0) do 0 end
    def fib(1) do 1 end
    def fib(n) do fib(n-1) + fib(n-2) end 

    #Benchmark for the super slow Fibonacci generator
    def bench_fib() do
        ls = [8,10,12,14,16,18,20,22,24,26,28,30,32]
        n = 10
        bench = fn(l) ->
            t = time(n, fn() -> fib(l) end)
            :io.format("n: ~4w fib(n) calculated in: ~8w us~n", [l, t])
        end
        Enum.each(ls, bench)
    end
end 