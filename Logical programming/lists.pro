test([], _) :- write('\n1\n').

%% test([Head|Tail], Num) :- Num2 is Num + 1, 
%% 							write('\n2\n'), 
%% 							length(Head, Num), 
%% 							write(test(Tail, Num2)), 
%% 							test(Tail, Num2), !.

%% test([Head|Tail], Num) :- Num2 is Num + 1, 
%% 							write('\n3\n'), 
%% 							write(append(Head, test(Tail, Num2))), 
%% 							append(Head, test(Tail, Num2)).

test([], _, []) :- !.

test([Head|Tail], Num, R) :- Num2 is Num + 1,
								length(Head, Num), 
								test(Tail, Num2, R),
								!.

test([Head|Tail], Num, [Head|Tail2]) :- Num2 is Num + 1,
                                       test(Tail, Num2, Tail2).

delete_under_lists() :- test([[], [a], [b], [a, b, c], [a], [b]], 0, R).

split(_, [], [], []) :- !.
split(X, [H|T], [H|L], R) :- X > H, split(X, T, L, R), !. 
split(X, [H|T], L, [H|R]) :- split(X, T, L, R).


qsort([], []) :- !.
qsort([H|T], RET) :- split(H, T, L, R),
						qsort(L, Lft),
						qsort(R, Rght), 
						append(
								Lft,
								[H],
								X
							),
						append(
								X, 
								Rght, 
								RET).

%%сортировать те подсписки, которые без нечетных
is_have([]) :- !.
is_have([H|T]) :- Rez is H mod 2, Rez == 0, is_have(T).


foo([], []) :- !.
foo([H|T], R) :- write('2'), 
				is_have(H), 
				qsort(H, N),  
				foo(T, RNext),
				append(
						[N],
						RNext,
						R
					),
				!.

foo([H|T], [H|R]) :- foo(T, R). 


%%foo([[2,6,4],[1,3,5],[8, 10, 2, 12]], R).
