defmodule Exam do

    def decode([]), do: []
    def decode([h|t]), do: decode_util(h)++ decode(t)
    def decode_util({_, 0}), do: []
    def decode_util({c, n}), do: [c | decode_util({c, n-1})]

    def zip([], _), do: []
    def zip(_, []), do: []
    def zip([h1|t1], [h2|t2]), do: [{h1, h2}| zip(t1,t2)]

    def balance(:nil), do: {0, 0}
    def balance({:node, _, a, b}) do
        {d1, i1} = balance(a)
        {d2, i2} = balance(b)
        {max(d1, d2)+1, max(max(i1, i2), abs(d1-d2))}
    end

    def eval({:add, a, b}), do: eval(a) + eval(b)
    def eval({:mul, a, b}), do: eval(a) * eval(b)
    def eval({:neg, a}), do: -a
    def eval(x), do: x

    def gray(0), do: [[]]
    def gray(1), do: [[0], [1]]
    def gray(n), do: update(0, gray(n-1)) ++ update(1, Enum.reverse(gray(n-1)))
    
    def update(_, []), do: []
    def update(a, [h|t]), do: [[a | h] | update(a, t)]
    
end