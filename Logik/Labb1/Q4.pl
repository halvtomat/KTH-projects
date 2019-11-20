partstring([X|_],[X]).
partstring([X,Y|_],[X,Y]).
partstring([X,Y,Z|_],[X,Y,Z]).
partstring([_|T], R) :- partstring(T, R).