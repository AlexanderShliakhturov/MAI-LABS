% Task 2: Relational Data

% The line below imports the data
:- ['three.pl'].
:- ['task1.pl'].

% Вспомогательные предикаты

% Сумма элементов списка
sum_list([], 0).  
sum_list([Head|Tail], Sum) :-
    sum_list(Tail, RestSum), 
    Sum is Head + RestSum. 

% Проверка, что все элементы списка больше двух

greater_than_two([], true).
greater_than_two([Head|Tail], Result) :-
    Head > 2,                 
    greater_than_two(Tail, Result). 
greater_than_two([Head|_], false) :- Head =< 2.

% Количество вхождения элемента в список

count(_, [], 0).
count(X, [X|Rest], Res) :-
    count(X, Rest, SubCount), 
    Res is SubCount + 1.    
count(X, [Y|Rest], Res) :-
    X \= Y,      
    count(X, Rest, Res).

% Максимальный элемент списка

max([X], X).
max([Head|Tail], Head):- max(Tail, Res), Head > Res.
max([_|Tail], Res):- max(Tail, Res).


% ПРЕДИКАТ ДЛЯ НАХОЖДЕНИЯ СРЕДНЕГО БАЛЛА И ПРОВЕРКИ СДАЧИ ЭКЗАМЕНОВ

average_grade_and_passed(LastName, AverageGrade, Passed) :-
    grades_avg(LastName, AverageGrade),
    check_passed(LastName, Passed).

grades_avg(LastName, AverageGrade) :-
    student(_, LastName, List),
    findall(X, member(grade(_, X), List), All),
    sum_list(All, Sum),
    length(All, Len), 
    AverageGrade is Sum / Len. 

check_passed(LastName, Result) :- 
    student(_, LastName, List),
    findall(X, member(grade(_, X), List), All),
    greater_than_two(All, Result).
    


% ПРЕДИКАТ ДЛЯ НАХОЖДЕНИЯ КОЛИЧЕСТВА НЕ СДАВШИХ СТУДЕНТОВ ДЛЯ КАЖДОГО ПРЕДМЕТА

amount_who_dont_passed_subj(FullSubj, Ans) :-
    subject(Subj, FullSubj),
    findall(Grade, (student(_, _, Grades), member(grade(Subj, Grade), Grades)), All_marks), 
    count(2, All_marks, Ans).

% ПРЕДИКАТ ДЛЯ НАХОЖДЕНИЯ СТУДЕНТА С МАКСИМАЛЬНЫМ СРЕДНИМ БАЛЛОМ ПО ГРУППЕ

student_with_max_avg_grade_in_group(Group, NameList) :-
    findall(Avg, (student(Group, _, Grades), calculate_average(Grades, Avg)), List),
    max(List, MaxAvgGrade),
    findall(Name, (average_grade_and_passed(Name, MaxAvgGrade, _), student(Group, Name, _)), NameList).


calculate_average(Grades, Avg) :-
    sum_grades(Grades, Sum),
    length(Grades, Len),
    Avg is Sum / Len.

sum_grades([], 0).
sum_grades([grade(_, Grade) | Tail], Sum) :-
    sum_grades(Tail, TailSum),
    Sum is TailSum + Grade.





