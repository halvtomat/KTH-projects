valuate(InputFile):-
    see(InputFile),     %Set InputFile as standard input.
    read(prems),        %Read the next prolog term of the standard input.
    read(goal),         %---||---
    read(proof),        %---||---
    seen,               %close the InputFile and set standard input to keyboard again.
    check_proof(prems, goal, proof).

check_proof(prems, goal, proof):-
    assert(prems_db(prems)),
    assert(proof_db(proof)).

check_rule([]):- !.
check_rule([[_,X,premise]|T]):-
    prems_db(Prem),
    member(X,Prem),
    check_rule(T).
check_rule([[N,and(X,Y),andint(R1,R2)]|T]):-
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R1,X,_],Proo),
    member([R2,Y,_],Proo),
    check_rule(T).
check_rule([[N,X,andel1(R)]|T]):-
    N>R,
    proof_db(Proo),
    member([R,and(X,_),_],Proo),
    check_rule(T).
check_rule([[N,Y,andel2(R)]|T]):-
    N>R,
    proof_db(Proo),
    member([R,and(_,Y),_],Proo),
    check_rule(T).
check_rule([[N,or(X,_),orint1(R1,R2)]|T]):-
    N>R1,
    N>R2,
    Proof_db(Proo),
    member([R1,X,_],Proo),
    check_rule(T).
check_rule([[N,or(_,Y),orint2(R1,R2)]|T]):-
    N>R1,
    N>R2,
    Proof_db(Proo),
    member([R2,Y,_],Proo),
    check_rule(T).




