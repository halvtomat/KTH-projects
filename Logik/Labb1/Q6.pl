%       Edges
edge(a,b).
edge(b,c).
edge(c,a).
edge(b,e).
edge(e,f).
edge(f,d).
edge(f,g).
%       Edges go both way -> Undirected Graph
connected(X,Y) :- edge(X,Y) ; edge(Y,X).
%       Find the path between two nodes
findpath(X,Y,P) :-
       traverse(X,Y,[X],Q), %Traverse the path
       reverse(Q,P).        %Reverse the list of steps to get it in the rigth order
traverse(X,Y,P,[Y|P]) :-    %If the current node is connected to the final node, we are finished
       connected(X,Y).
traverse(X,Y,V,P) :-        %Find a node that we havn't been to previously and is connected to the current node and go there
       connected(X,C),      %is it connected to the current node?
       C \== Y,             %Is it the destination node?
       \+member(C,V),       %Have we been there before?
       traverse(C,Y,[C|V],P).  