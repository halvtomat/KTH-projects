defmodule Finder do

    import My_list
    import Moves
    require My_list
    require Moves

    def split([], _) do {[], []} end
    def split(l, e) do {take(l, position(l, e)-1), drop(l, position(l, e))} end

    def find({[], _, _}, {[], _, _}) do [] end
    
end