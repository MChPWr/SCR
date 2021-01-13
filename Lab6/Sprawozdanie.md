Dla czytelniejszego dokumentu prosze zaznaczyc opcje "Display the rich diff" ----------------------------------------->

# EX_1

Zostal napisany prosty program myhello.c, ktory tworzy piec watkow w petli. Skompilowany przy uzyciu flag: -o, -ptherad

## Output programu myhello.out
---
```
Creating thread number: 0 
Creating thread number: 1 
Creating thread number: 2 
Creating thread number: 3 
Creating thread number: 4 
Hello from thread number: 4 
Hello from thread number: 3 
Hello from thread number: 2 
Hello from thread number: 1 
Hello from thread number: 0
```

Nastepnie skompilowano i uruchomiono program hello.out. Uzyto tych samych flag.

## Output programu hello.out
---
```
In main: creating thread 0
In main: creating thread 1
In main: creating thread 2
In main: creating thread 3
In main: creating thread 4
Hello World! It's me, thread #4!
Hello World! It's me, thread #3!
Hello World! It's me, thread #2!
Hello World! It's me, thread #1!
Hello World! It's me, thread #0!
```

Programy zachowuja sie dosc podobnie. Problem polega w tym, ze poprawnosc dzialania jest "pozorna". Po kilkukrotnym
uruchomieniu powyzszych programow mozemy otrzymac ponizsze wyniki:

## Przykladowy output programu hello.c
---
```
In main: creating thread 0
In main: creating thread 1
In main: creating thread 2
In main: creating thread 3
In main: creating thread 4
Hello World! It's me, thread #4!
Hello World! It's me, thread #3!
Hello World! It's me, thread #0!
Hello World! It's me, thread #2!
Hello World! It's me, thread #1!
```
## Przykladowy output programu myhello.c
---
```
Creating thread number: 0
Creating thread number: 1
Creating thread number: 2
Creating thread number: 3
Creating thread number: 4
Hello from thread number: 4
Hello from thread number: 3
Hello from thread number: 2
Hello from thread number: 0
Hello from thread number: 1
```
Wywolujac programy kilkukrotnie mozemy zauwazyc, ze watki moga pojawiac sie w innej kolejnosci. Jest to niepozadane zjawisko
i moze byc wyeliminowane przez elementy synchronizujace (muteksy).

# EX_2

Po skompilowaniu kodu (hello32.c) i uruchomieniu programu mozemy zauwazyc analogiczna sytuacje jak w zadaniu EX1. Po kilkuktortnym uruchomieniu
za niemal kazdym razem watki pojawialy sie w innej kolejnosci. Mozna zauwazyc, ze kolejnosc tworzenia watkow nie ma wyplywu na kolejnosc
pojawienia sie ich na outpucie. Wplyw na to ma system operacyjny, lecz mozemy tym manipulowac uzywajac odpowiedniej synchornizacji
za pomoca muteksow.

# EX_3

Kiedy przekazywany jest jeden argument to program rzutuje na wskaznik typu void kopie zmiennej, a dla wielu argumentow (tez nastapi rzutowanie wskaznika) 
przekazywana jest referencja do zmiennej. Ponizej przedstawiono outputy dla kolejnych skompilowanych kodow zrodlowych: hello_arg1.c, hello_arg2.c.

## Output programu hello_arg1.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./hello_arg1.out 
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Thread 6: Japan: Sekai e konnichiwa!
Thread 7: Latin: Orbis, te saluto!
Thread 5: Russian: Zdravstvuyte, mir!
Thread 4: German: Guten Tag, Welt!
Thread 3: Klingon: Nuq neH!
Thread 2: Spanish: Hola al mundo
Thread 1: French: Bonjour, le monde!
Thread 0: English: Hello World!
```

## Output programu hello_arg2.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./hello_arg2.out
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Thread 5: Russian: Zdravstvytye, mir!  Sum=15
Thread 6: Japan: Sekai e konnichiwa!  Sum=21
Thread 7: Latin: Orbis, te saluto!  Sum=28
Thread 4: German: Guten Tag, Welt!  Sum=10
Thread 3: Klingon: Nuq neH!  Sum=6
Thread 2: Spanish: Hola al mundo  Sum=3
Thread 1: French: Bonjour, le monde!  Sum=1
Thread 0: English: Hello World!  Sum=0
```

Nastepnie skompilowano i uruchomiono program bug3.out.

## Output programu bug3.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug3.out
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
```

Zostala wyswietlona ta sama wiadomosc z funkcji tworzenia watkow. Blad
moze byc spowodowany zlym rzutowaniem na wskaznik. Mozna to naprawic usuwajac wskaznik (19 linia) i referencje (32 linia). Wtedy program 
zaczyna dzialac prawidlowo. Ponizej skompilowano i uruchomiono taki program po naprawie.

## Output programu bug3_fix.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug3_fix.out
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Hello from thread 6
Hello from thread 7
Hello from thread 5
Hello from thread 4
Hello from thread 3
Hello from thread 2
Hello from thread 1
Hello from thread 0
```

# EX_4

Skompilowano i uruchomiono program bug5.out.

## Output programu bug5.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug5.out 
Main: creating thread 0
Main: creating thread 1
Main: creating thread 2
Main: creating thread 3
Main: creating thread 4
Main: Done.
```

Program iniciuje tworzenie watkow, ale nie konczy tej czynnosci. 
Spowodowane jest to brakiem instrukcji "pthread_exit(NULL);" na koncu
maina. Wykonuja one swoj kod, ale watek glowny ( main) wczesniej konczy dzialanie, niz inicjonwane watki wykonaja sie do konca, zatem zostaja one zakonczone. Nalezy to naprawic wstawijac powyzsza instrukcje na koniec maina. 

Skompilowano i uruchomiono program uwzgledniajacy ta instrukcje.

## Output programu bug5_fix.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug5_fix.out
Main: creating thread 0
Main: creating thread 1
Main: creating thread 2
Main: creating thread 3
Main: creating thread 4
Main: Done.
thread=4: starting...
thread=3: starting...
thread=2: starting...
thread=1: starting...
thread=0: starting...
thread=0 result=-3.153838e+06. Done.
thread=3 result=-3.153838e+06. Done.
thread=2 result=-3.153838e+06. Done.
thread=4 result=-3.153838e+06. Done.
thread=1 result=-3.153838e+06. Done.
```

# EX_5

Skompilowano i uruchomiono program join.out

## Output programu join.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./join.out 
Main: creating thread 0
Main: creating thread 1
Main: creating thread 2
Main: creating thread 3
Thread 3 starting...
Thread 2 starting...
Thread 1 starting...
Thread 0 starting...
Thread 2 done. Result = -3.153838e+06
Thread 1 done. Result = -3.153838e+06
Thread 3 done. Result = -3.153838e+06
Thread 0 done. Result = -3.153838e+06
Main: completed join with thread 0 having a status of 0
Main: completed join with thread 1 having a status of 1
Main: completed join with thread 2 having a status of 2
Main: completed join with thread 3 having a status of 3
Main: program completed. Exiting.
```

W celu zwracania przez watki roznych wartosci, dodano zmienna value typu
double, do ktorej przypisano wartosc id watku

## Output programu join_fix.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./join_fix.out 
Main: creating thread 0
Main: creating thread 1
Main: creating thread 2
Main: creating thread 3
Thread 3 starting...
Thread 2 starting...
Thread 1 starting...
Thread 0 starting...
Thread 0 done. Result = -3.153838e+06
Main: completed join with thread 0 having a status of 0
Thread 1 done. Result = -2.153838e+06
Main: completed join with thread 1 having a status of 1
Thread 2 done. Result = -1.153838e+06
Main: completed join with thread 2 having a status of 2
Thread 3 done. Result = -1.538376e+05
Main: completed join with thread 3 having a status of 3
Main: program completed. Exiting.
```

Nastepnie skompilowano i uruchomiono program detached.c

## Output programu detached.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./detached.out 
Main: creating thread 0
Main: creating thread 1
Main: creating thread 2
Main: creating thread 3
Main: program completed. Exiting.
Thread 3 starting...
Thread 2 starting...
Thread 1 starting...
Thread 0 starting...
Thread 2 done. Result = -3.153838e+06
Thread 3 done. Result = -3.153838e+06
Thread 1 done. Result = -3.153838e+06
Thread 0 done. Result = -3.153838e+06
```

Instrukcja pthread_join jest odpowiedzialna za synchronizowanie dzialania programu, aby mozna bylo wykonac kod wszystkich watkow w czasie trwania programu. W pliku detached.c nie ma tej funkcji, wiec nie ma rowniez synchronizacji. Program nie czeka na zakonczenie wszystkich watkow i konczy sie szybciej. (Wskazuje na to informacja o zakonczeniu programu przed wykonaniem sie wszystkich watkow)

# EX_6

Skompilowano i uruchomiono program bug2.out

## Output programu bug2.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug2.out
Thread stack size = 8388608 bytes (hint, hint)
Created 8 threads.
Segmentation fault (core dumped)
```

Natepnie skompilowano i uruchomiono program bu2fix.out

## Output programu bug2fix.out
---
```
maciej@maciej-VirtualBox:~/Documents/SCRY/SCR-1/Lab6$ ./bug2fix.out
Thread stack size = 17000000 bytes (hint, hint)
Created 8 threads.
3: Hello World!   1999999.000000
3: Thread stack size = 17000000 bytes
6: Hello World!   1999999.000000
6: Thread stack size = 17000000 bytes
4: Hello World!   1999999.000000
4: Thread stack size = 17000000 bytes
2: Hello World!   1999999.000000
2: Thread stack size = 17000000 bytes
1: Hello World!   1999999.000000
1: Thread stack size = 17000000 bytes
7: Hello World!   1999999.000000
5: Hello World!   1999999.000000
5: Thread stack size = 17000000 bytes
0: Hello World!   1999999.000000
0: Thread stack size = 17000000 bytes
7: Thread stack size = 17000000 bytes
```

Pojawienie sie sygnalu 11 (segmentation fault) spowodowane jest naruszeniem ochrony pamieci. Nalezy zwiekszyc pamiec dla watku przez uzycie pthread_attr_setstacksize() oraz zmienic argument funkcji tworzacej watki pthread_create NULL -> &attr. (analogicznie jak w pliku bug2.fix.c)
