permute([],[]).
permute([H|T],R):- 
    permute(T,Q),
    select(H,R,Q).

select(H,[H|R],R).
select(H,[Y|R],[Y|Q]):- 
    select(H,R,Q).