EX_1

Napisano skrypt, ktory w nieskonczonej petli wypisuje na ekran tekst
"Hello World". Od razu napisano funkcje void milisecSleep(), ktorej zadaniem jest zmiana czestotliwosci wypisywania tekstu w zaleznosci od zadanej wartosci zmiennej timeDelay. Funkcja ta korzysta z funkcji nanosleep(). Po skomplilowaniu programu zostal on uruchomiony. 
Zadana wartosc zmiennej timeDelay odpowiadajacej za czestotliwosc wypisywania tekstu na ekran zostala ustawiona na wartosc 1.
Nastepnie wydano komende: top -u maciej.

Output komendy:

PID   USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
1378  maciej    20   0 3784244 304648  82184 S  45,2  15,0   7:20.44 gnome-s+
1243  maciej    20   0  361728 122768  61476 S  14,3   6,0   2:46.82 Xorg
3394  maciej    20   0  827588  38712  22568 S   8,6   1,9   0:23.76 gnome-t+
26501 maciej    20   0    2488    584    516 S   2,3   0,0   0:00.61 a.out

Program o wykonywanym kodem o domyslnej nazwie a.out znalazl sie w czolowlce najbardziej obciazajacych procesow.

Nastepenie zmieniono wartosc timeDelay na 100. Wydano komende: top -u maciej

W efekcie program znalazl sie na koncu listy

PID   USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND  
26733 maciej    20   0    2488    584    516 S   0,0   0,0   0:00.00 a.out

EX_2

W celu demontracji reakcji programu na sygnal zmodyfikowani program ex1.c dodajac
do niego funkcje pelniaca funkcjonalnosc handlera - signalHandler(). Funkcja w zaleznosci od danego sygnalu wykona rozne instrukcje. 

Uruchomiono program.

Output po 5 sekundach:

PID: 27689
0
1
2
3
4
5


Wydanko komende: kill -14 27689

Output

68
69
Catching SIGALRM
70
71

Efekt: Sygnal zostal zlapany.

Wydano komende: kill -10 27148

Output:

88
Catching SGUSR1. I'll not catch signals for ten iterations!
89
90
91
92
93
94
95
96
97
98
99
Catching signals now!
100

Efekt:

Zaczeto ignorowac sygnaly na 10 iteracji. Po 10 wyswietlonych liczbach odbieranie sygnalu jest mozliwe.

Nastepnie wywolano sygnal SIGUSR2(12). Wpisano komende: kill -12 27689

Efekt

Program nie reaguje.

Nastepnie wywolaono sygnal SIGTERM(15). Wpisano komende: kill -15 27689

Output:

57
358
359
360
361
Catching SIGTERM
maciej@maciej-VirtualBox:~/Documents/SCR/SCR-1/Lab3/ex2$

Efekt:

Po przechywceniu sygnalu program zakonczyl sie.

EX_3

Uruchomiono program z zadania ex2. Zostala sprawdzowna tablica akcji sygnalow poleceniem: cat /proc/27868/status | grep Sig

Output:

SigQ:	0/7730
SigPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000800
SigCgt:	0000000000006200

Po zdekodowaniu na kod binarny otrzymano:

SigIgn: 0000100000000000 - 12 (SIGUSR2). Jest on ignorowany.
SigCgt: 0110001000000000 - Są to sygnały 10,14,15 czyli (SIGUSR1,SIGALRM,SIGTERM), ktore sa przechwytywane przez proces (caught).

EX_4

Napisano prosty program, ktory w nieskonczonej petli wyswietla tekst. Napisano rowniez prosty skrypt, ktory bedzie drugim ogniwem lancucha potoku.

Komenda: ./a.out | ./ex4.sh | cat

Nastepnie uzyto polecenia ps -f. Sprawodzono PIDy poszczegolnych procesow.
Nastepnie zlistingowano zaleznosci kazdego procesu w folderze fd.

Output komndy ps -f:

PID TTY      STAT   TIME COMMAND
2274 pts/2    R+     0:00  \_ ps f
2241 pts/1    S+     0:00  \_ ./a.out
2242 pts/1    S+     0:00  \_ /bin/bash ./ex4.sh
2243 pts/1    S+     0:00  \_ cat

Outputy komendy ls -l /proc/224x/fd, gdzie x to ostatnia cyfra w numerze 
procesu

ls -l /proc/2241/fd
total 0
lrwx------ 1 maciej maciej 64 lis 18 19:38 0 -> /dev/pts/1
l-wx------ 1 maciej maciej 64 lis 18 19:38 1 -> 'pipe:[43836]'
lrwx------ 1 maciej maciej 64 lis 18 19:38 2 -> /dev/pts/1

ls -l /proc/2242/fd
total 0
lr-x------ 1 maciej maciej 64 lis 18 19:39 0 -> 'pipe:[43836]'
l-wx------ 1 maciej maciej 64 lis 18 19:39 1 -> 'pipe:[43838]'
lrwx------ 1 maciej maciej 64 lis 18 19:39 2 -> /dev/pts/1
lr-x------ 1 maciej maciej 64 lis 18 19:39 255 -> /home/maciej/Documents/SCR/SCR-1/Lab3/ex4/ex4.sh

ls -l /proc/2243/fd
total 0
lr-x------ 1 maciej maciej 64 lis 18 19:39 0 -> 'pipe:[43838]'
lrwx------ 1 maciej maciej 64 lis 18 19:39 1 -> /dev/pts/1
lrwx------ 1 maciej maciej 64 lis 18 19:39 2 -> /dev/pts/1

Po analize powyzszych outputow mozna stwierdzic, ze proces o numerze PID 2241 (a.out) byl pierwszym ogniwem potoku i przekazal dane do potoku
(1 -> pipe:[43836]). Proces 2242 czytal z potoku (0 -> pipe:[43836]) i zapisywal do potoku (1 -> pipe:[43838]). Ostatnie ogniwo potoku czyli proces cat o numerze PID 2243 czytal z potoku (0 -> pipe:[43838]) i kierowal dane na standardowe wyjscie. 

EX_5

Zadaniem polecnia Strace jest przechwytywanie i "nagrywanie" wywolan systemowych dokonywanych przez procesy, sygnaly. Nazwa wywolan oraz jego argumenty, sa wypisywane na wyjscie standardowe bledu. Opcjonalnym wyjsciem jest wyjscie do pliku, gdy podamy flage -o.
    Strace uzywany jest jako narzedzie diagnostycznego, narzedzie do debuggowania.

Przydatne opcje:

DWIE NAJWAZNIEJSZE

strace --help
man strace

RESZTA OPCJONALNYCH

-c Odpowiada za zliczanie czasu, wywolania i bledy dla kazdego wywolania   systemowego. Zglasza na koncu raport.

-d Przekazuje na stderr wyjscie debuggowe strace.

-V Drukuje numer wersji strace.

-f Sledzi procesy potomne, tworzone przez obecnie sledzone procesy.

-t Poprzedza kazda linie trace czasem dnia.

-T Czas spedzony na wywolaniach systemowych. "Nagrywa" roznice czasowe
miedzy poczatkiem i koncem kazdego wywolania systemowego.

-xx Drukuje wszystkie napisy w formacie szesnastkowym.

-a kolumna Justowanie zwarcanych wartosci w konkretnej kolumnie.

-e wyraznie Okresla ktore zdarzenie i jak sledziec. Mnogosc opcji, ktore mozemy podejrzec w manualu.
