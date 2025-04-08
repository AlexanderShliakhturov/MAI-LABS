% Первая часть задания - предикаты работы со списками

length([], 0) . 
length([_|Y], N) :- length(Y, N1), N is N1 + 1.

member(A, [A|_]).
member(A, [_|Z]) :- member(A, Z).

append([], X, X).
append([A|X], Y, [A|Z]) :- append(X,Y,Z).


remove([], _, []).
remove([X|T], X, T).
remove([Y|T], X, [Y|T1]) :-  remove(T, X, T1).

permute([],[]).
permute(L,[X|T]):-remove(X,L,R),permute(R,T).

sublist(S, L) :- 
    append(_, L1, L),
    append(S, _, L1),
    \+ (append(_, L2, L), append(S, _, L2), L1 \== L2).



% УДАЛЕНИЕ ВСЕХ ЭЛЕМЕНТОВ СПИСКА ПО ЗНАЧЕНИЮ


%не используя стандартные предикаты
remove_X([], _, []).
remove_X([X|Rest], X, Result) :- remove_X(Rest, X, Result).
remove_X([Y|Rest], X, [Y|Result]) :- remove_X(Rest, X, Result).

%на основе стандарных предикатов

remove_all(Lst, X, Result) :- 
    \+ member(X, Lst), 
    Result = Lst.
remove_all(Lst, X, Result) :-
    remove(Lst, X, NewLst),
    remove_all(NewLst, X, Result).


    

%ВЫЧИСЛЕНИЕ СУММЫ ДВУХ ВЕКТОРОВ СПИСКОВ С УЧЕТОМ ВОЗМОЖНОГО НЕСОВПАДЕНИЯ РАЗМЕРНОСТЕЙ

%не используя стандартные предикаты
vect_sum([], V2, V2).
vect_sum(V1, [], V1).

vect_sum([X1|Rest1], [X2|Rest2], [Sum|Result]) :-
    Sum is X1 + X2,
    vect_sum(Rest1, Rest2, Result).



