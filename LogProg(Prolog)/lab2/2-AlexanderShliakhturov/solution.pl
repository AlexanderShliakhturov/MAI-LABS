# Вариант 2
# В одном городе живут 7 любителей птиц. И фамилии у них птичьи. Каждый из них — «тезка» птицы, которой владеет 
# один из его товарищей. У троих из них живут птицы, которые темнее, чем пернатые «тезки» их хозяев. «Тезка» птицы,
# которая живет у Воронова, женат. Голубев и Канарейкин — единственные холостяки из всей компании. Хозяин грача 
# женат на сестре жены Чайкина. Невеста хозяина ворона очень не любит птицу, с которой возится ее жених. «Тезка»
# птицы, которая живет у Грачева,— хозяин канарейки. Птица, которая является «тезкой» владельца попугая, 
# принадлежит «тезке» той птицы, которой владеет Воронов. У голубя и попугая оперение светлое.
# Кому принадлежит скворец?


tezka(raven,voronov).     %ворон     
tezka(dove,golubev).      %голубь    
tezka(canary,kanareikin). %канарейка 
tezka(rook,grachev).      %грач      
tezka(gull,chaikin).      %чайка     
tezka(parrot,popugaev).   %попугай   
tezka(starling,skvorcov). %скворец   

solve(Ans,StarlingOwner):-
    Ans=[voronov/A,golubev/B,kanareikin/C,grachev/D,chaikin/E,popugaev/F,skvorcov/G],
    permutation([raven,dove,canary,rook,gull,parrot,starling],[A,B,C,D,E,F,G]),  
    A\=raven,B\=dove,C\=canary,D\=rook,E\=gull,F\=parrot,G\=starling,            

    % темные птицы
    Dark=[raven,rook,starling],    
    
    % У троих из них живут птицы, которые темнее, чем пернатые «тезки» их хозяев

    member(RavenOwner/raven,Ans),tezka(TezkaRvRv,RavenOwner),not(member(TezkaRvRv,Dark)),
    member(RookOwner/rook,Ans),tezka(TezkaRkRk,RookOwner),not(member(TezkaRkRk,Dark)),
    member(StarlingOwner/starling,Ans),tezka(TezkaSS,StarlingOwner),not(member(TezkaSS,Dark)),

    
    %Голубев и Канарейкин — холостяки из всей компании, а «Тезка» птицы, которая живет у Воронова, женат.

    not(tezka(A,golubev)),not(tezka(A,kanareikin)),  

    %Хозяин грача женат
    not(B=rook),not(C=rook),          

    %на сестре жены Чайкина => владелец грача - не Чайкин
    not(RookOwner=chaikin),      

    %Невеста хозяина ворона... => хозяин ворона - кто-то из неженатых
    (B=raven ; C=raven),         

    % «Тезка» птицы, которая живет у Грачева,— хозяин канарейки.
    tezka(D,CanaryOwner),member(CanaryOwner/canary,Ans),     
    member(ParrotOwner/parrot,Ans),tezka(TezkaRvP,ParrotOwner),

    %Птица, которая является «тезкой» владельца попугая, принадлежит «тезке» той птицы, которой владеет Воронов
    member(TezkaRvPOwner/TezkaRvP,Ans),tezka(TezkaRvTRvP,TezkaRvPOwner),
    member(voronov/TezkaRvTRvP,Ans).       
    