defmodule My_list do

    #Returns the list containing the first n elements of l
    def take(_, 0), do: []
    def take([], _), do: []
    def take([h | t], n), do: [h | take(t, n-1)]

    #Returns the list l without its first n elements
    def drop([], _), do: []
    def drop(l, 0), do: l
    def drop([_ | t], n), do: drop(t, n-1)

    #Returns the list l1 with the elements of l2 appended
    def append(l, []), do: l
    def append(l, [h | t]), do: append(l ++ [h], t)    

    #Tests whether x is an element of l
    def member([], _), do: false
    def member([x | _], x), do: true
    def member([_ | t], x), do: member(t, x)

    #Returns the first position of x in the list l
    def position(l, x), do: position(l, x, 1)
    def position([], _, _), do: false
    def position([x | _], x, n), do: n
    def position([_ | t], x, n), do: position(t, x, n+1)

end