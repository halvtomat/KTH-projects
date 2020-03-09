defmodule Exam do
    
    def drop(l, n), do: drop(l, n-1, n-1)
    def drop([], _, _), do: []
    def drop([_ | t], 0, n), do: drop(t, n, n)
    def drop([h | t], a, n), do: [h | drop(t, a-1, n)]

    def rotate(l, n), do: rotate(l, [], n)
    def rotate(l, r , 0), do: l ++ Enum.reverse(r)
    def rotate([h | t], r, n), do: rotate(t, [h | r], n-1)

    def nth(n, {:node, left, right}) do
        case nth(n, left) do
            {:found, val} ->
                {:found, val}
            {:cont, k} ->
                case nth(k, right) do
                    {:found, val} ->
                        {:found, val}
                    {:cont, k} ->
                        {:cont, k}
                end
        end
    end
    def nth(1, {:leaf, val}), do: {:found, val}
    def nth(n, {:leaf, _}), do: {:cont, n-1}

    def hp35(seq), do: hp35(seq, [])
    def hp35([], [h | _]), do: h
    def hp35([:add | t], [a, b | st]), do: hp35(t, [b + a | st])
    def hp35([:sub | t], [a, b | st]), do: hp35(t, [b - a | st])
    def hp35([x | t], s), do: hp35(t, [x | s])

    def pascal(1), do: [1]
    def pascal(n), do: [1 | next(pascal(n-1))]

    def next([1]), do: [1]
    def next([a, b | t]), do: [a+b | next([b | t])]
end