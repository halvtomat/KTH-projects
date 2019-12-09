findlast([T],[],T).
findlast([H|T],[H|R],E):- findlast(T,R,E).