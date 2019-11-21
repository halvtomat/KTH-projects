verify(InputFile):-
    see(InputFile),                                 %Set InputFile as standard input.
    read(Prems),                                    %Read the next prolog term of the standard input.
    read(Goal),                                     %---||---
    read(Proof),                                    %---||---
    seen,                                           %close the InputFile and set standard input to keyboard again.
    check_proof(Prems, Goal, Proof).

check_proof(Prems, Goal, Proof):-
    asserta(prems_db(Prems)),                        %Add all premisses to the premise database
    asserta(proof_db(Proof)),                        %Add the proof to the proof database
    last(Proof,[_,Goal,_]),

    (check_rule(Proof) -> (retract(proof_db(X)),retract(prems_db(Y)));(retract(proof_db(X)),retract(prems_db(Y)),fail)).


check_rule([]):- !.
check_rule([[_,X,premise]|T]):-                     %Premiss
    prems_db(Prem),
    member(X,Prem),
    check_rule(T).
check_rule([[N,and(X,Y),andint(R1,R2)]|T]):-        %And introduction
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R1,X,_],Proo),
    member([R2,Y,_],Proo),
    check_rule(T).
check_rule([[N,X,andel1(R)]|T]):-                   %And elimination 1
    N>R,
    proof_db(Proo),
    member([R,and(X,_),_],Proo),
    check_rule(T).
check_rule([[N,Y,andel2(R)]|T]):-                   %And elimination 2
    N>R,
    proof_db(Proo),
    member([R,and(_,Y),_],Proo),
    check_rule(T).
check_rule([[N,or(X,_),orint1(R1,R2)]|T]):-         %Or introduciton 1
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R1,X,_],Proo),
    check_rule(T).
check_rule([[N,or(_,Y),orint2(R1,R2)]|T]):-         %Or introduction 2
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R2,Y,_],Proo),
    check_rule(T).
check_rule([[N,neg(neg(X)),negnegint(R)]|T]):-      %Double-Negation introduction
    N>R,
    proof_db(Proo),
    member([R,X,_],Proo),
    check_rule(T).
check_rule([[N,X,copy(R)]|T]):-                     %Copy
    N>R,
    proof_db(Proo),
    member([R,X,_],Proo),
    check_rule(T).
check_rule([[N,cont,negel(R1,R2)]|T]):-             %Negation elimination
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R1,X,_],Proo),
    member([R2,neg(X),_],Proo),
    check_rule(T).
check_rule([[N,_,contel(R)]|T]):-                   %Contradiction elimination
    N>R,
    proof_db(Proo),
    member([R,cont,_],Proo),
    check_rule(T).
check_rule([[N,X,negnegel(R)]|T]):-                 %Double-Negation elimination
    N>R,
    proof_db(Proo),
    member([R,neg(neg(X)),_],Proo),
    check_rule(T).
check_rule([[N,X,impel(R1,R2)]|T]):-                %Implication eliminiation
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R2,imp(Y,X),_],Proo),
    member([R1,Y,_],Proo),
    check_rule(T).
check_rule([[N,neg(X),mt(R1,R2)]|T]):-              %Modus Tollens
    N>R1,
    N>R2,
    proof_db(Proo),
    member([R1,imp(X,Y),_],Proo),
    member([R2,neg(Y),_],Proo),
    check_rule(T).
check_rule([[_,or(X,neg(X)),lem]|T]):-              %Law of Excluded Middle
    check_rule(T).
%––––––––––––––––––––––––––––––––––––––––––––––––––––Box time–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––:
check_rule([[[N,X,assumption]|T1]|T2]):-                                                                                 %|
    proof_db(Proo),                                                                                                      %|
    append(Proo,[[N,X,assumption]|T1],Prootemp),                                                                         %|
    assert(proof_db(Prootemp)),                                                                                          %|
    check_rule(T1),                                                                                                      %|
                                                                                                                         %|
    last([[N,X,assumption]|T1], Res),                                                                                    %|
    append(Proo,[[N,X,assumption],Res],Proo2),                                                                           %|
    retractall(proof_db(_)),                                                                                             %|
    assert(proof_db(Proo2)),                                                                                             %|
    check_rule(T2).                                                                                                      %|
%–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––:

check_rule([[N,imp(X,Y),impint(R1,R2)]|T]):-        %Implication introduction
    N>R1,
    N>R2,
    proof_db(Proo),
    member([[R1,X,assumption]|[R2,Y,_]],Proo),
    check_rule(T).
check_rule([[N,neg(X),negint(R1,R2)]|T]):-          %Negation introdcution
    N>R1,
    N>R2,
    proof_db(Proo),
    member([[R1,X,assumption]|[R2,cont,_]],Proo),
    check_rule(T).
check_rule([[N,X,pbc(R1,R2)]|T]):-                  %Proof By Contradiction       
    N>R1,
    N>R2,
    proof_db(Proo),
    member([[R1,neg(X),assumption]|[R2,cont,_]],Proo),
    check_rule(T).
check_rule([[N,X,orel(R1,R2,R3,R4,R5)]|T]):-        %Or elimination              
    N>R1,
    N>R2,
    N>R3,
    N>R4,
    N>R5,
    proof_db(Proo),
    member([R1,or(A,B),_],Proo),
    member([[R2,A,assumption],[R3,X,_]],Proo),
    member([[R4,B,assumption],[R5,X,_]],Proo),
    check_rule(T).