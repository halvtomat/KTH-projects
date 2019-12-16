% For SICStus, uncomment line below: (needed for member/2)
%:- use_module(library(lists)).
% Load model, initial state and formula from file.
verify(Input) :-
    see(Input),
    read(T), 
    read(L), 
    read(S), 
    read(F), 
    seen,
    check(T, L, S, [], F).

% check(T, L, S, U, F)
% T - The transitions in form of adjacency lists
% L - The labeling
% S - Current state
% U - Currently recorded states
% F - CTL Formula to check.
%
% Should evaluate to true iff the sequent below is valid.
%
% (T,L), S |- F
% U
% To execute: consult(’your_file.pl’). verify(’input.txt’).

% Literals
check(_,L,S,[],X) :-        % Checks if a label exists within a state.
    member([S,L1],L),       % L1 is a list of all the labels in this state.
    member(X,L1).           % Is X a member of L1
% Literal neg
check(_,L,S,[],neg(X)) :-   % Same as above but negated.
    member([S,L1],L),       % L1 is a list of all the labels in this state.
    \+member(X,L1).         % Is X not a member of L1?
% And
check(T,L,S,[],and(X,Y)) :- % Checks if both the labels X and Y exists within a state.
    check(T,L,S,[],X),      % Checks if X exists in the state.
    check(T,L,S,[],Y),!.    % Checks if Y exists in the state.
% Or
check(T,L,S,[],or(X,_)) :-  % Checks if X or _ exists within a state.
    check(T,L,S,[],X),!.    % Checks if X exists in the state.
% Or twin
check(T,L,S,[],or(_,Y)) :-  % Checks if _ or Y exists within a state.
    check(T,L,S,[],Y),!.    % Checks if Y exists in the state. 
% AX
check(T,L,S,U,ax(X)):-      % Checks if all the neighboring states contain X.
  member([S,T1], T),        % From this line we will get a list with all adjacent states of S.
  ax_util(T,L,T1,U,X).      % Call ax_util to iterate through the list of adjacent states.

ax_util(_,_,[],_,_).        % Base case, when the adjacency-list is empty, we are done.
ax_util(T,L,[S|Tail],U,X) :-% Iterates the adjacency-list to check if X exist.
  check(T,L,S,U,X),!,       % Checks if X exists in the state S.
  ax_util(T,L,Tail,U,X).    % Call ax_util again with the Tail of the adjacnecy-list.
% EX
check(T,L,S,U,ex(X)) :-     % Checks if there is any next state where X exists.
    member([S,T1],T),       % From this line we will get a list of all the adjacent states T1 of S.
    member(S1,T1),          % From this line we use the list T1 to get one of the adjacent states of S.
    check(T,L,S1,U,X).      % Now we check if X exists in the adjacent state S1. If this fails S1 will become the next adjecent state in T1.
% AG
check(_,_,S,U,ag(_)) :-         % Base case. 
    member(S,U).                % Checks if our current state exists in the list U of already evaluated states.
check(T,L,S,U,ag(X)) :-         % Checks if next state is always X.
  check(T,L,S,[],X),            % Checks if X is a label in the current state.
  check(T,L,S,[S|U],ax(ag(X))). % Adds our current state in the list U of already evaluated states and then continue to evaluate on the next state.
% EG
check(_,_,S,U,eg(_)) :-             % Base case.
    member(S,U),!.                  % Checks if our current state exists in the list U of already evaluated states.
check(T,L,S,U,eg(X)) :-             % Checks if there is a path where it's always X.
    check(T,L,S,[],X),              % Checks if X is a label in the current state.
    check(T,L,S,[S|U],ex(eg(X))).   % Adds our current satte in the list U of already evaluated states and then continue to evalutate on the next state.
% AF
check(T,L,S,U,af(X)) :-             % Checks if we eventually end up at X.
  \+ member(S, U),                  % Checks if we have NOT been in S before. This is to stop an endless cycle to occure.
  check(T,L,S,[],X).                % Checks if X exists in S.
check(T,L,S,U,af(X)) :-             % Checks if we eventually end up at X.
  \+ member(S,U),                   % Checks if we have NOT been in S before. This is to stop an endless cycle to occure.
  check(T,L,S,[S|U],ax(af(X))).     % Checks if X eventually shows up in ALL the adjacent states of S. 
% EF
check(T,L,S,U,ef(X)) :-             % Checks if there is a path such as we eventually get to X.
  \+ member(S,U),                   % Checks if we have NOT been in S before. This is to stop an endless cycle to occure.
  check(T,L,S,[],X).                % Checks if X exists in S.
check(T,L,S,U,ef(X)):-              % Checks if there is a path such as we eventually get to X.
  \+ member(S,U),                   % Checks if we have NOT been in S before. This is to stop an endless cycle to occure.
  check(T,L,S,[S|U],ex(ef(X))).     % Checks if X eventually shows up in ANY of the adjacent states of S.