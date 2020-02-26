defmodule Moves do

    import My_list
    require My_list
    

    def single({:one, 1}, {m, l, r}) do {
        take(m, length(m)-1), 
        append(drop(m, length(m)-1), l),
        r
    }
    end
    def single({:one, -1}, {m, l, r}) do {
        append(m, take(l, 1)), 
        drop(l, 1),
        r
    }
    end
    def single({:two, 1}, {m, l, r}) do {
        take(m, length(m)-1), 
        l,
        append(drop(m, length(m)-1), r)
    }
    end
    def single({:two, -1}, {m, l, r}) do {
        append(m, take(r, 1)), 
        l,
        drop(r, 1)
    } 
    end

    def move([], tr) do tr end
    def move([h | t], tr) do move(t, single(h, tr)) end
    
end