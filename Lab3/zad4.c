

/*
korzystam z programu ./zad2
poniewaz jest to przyklad programy przechwytujacego/ ignorujacego wybrane sygnaly


ponizej stworzylem potok trzech polecen 
pierwszy program zad2 wypisuje w nieskonczonosc tekst
jakub@jakub-VirtualBox:~/Desktop/SCR/lab3$ ./zad2 | cat | cat > /dev/null 



sprawdzam numery PID programow
zad2 -> 5036
cat -> 5037
cat -> 5038

jakub@jakub-VirtualBox:/proc/4973$ ps l
F   UID     PID    PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
4  1000    1751    1695  20   0 166536  6616 poll_s Ssl+ tty2       0:00 /usr/lib/gdm3/gdm-x-ses
4  1000    1755    1751  20   0 682272 71584 ep_pol Sl+  tty2       0:50 /usr/lib/xorg/Xorg vt2 
0  1000    1831    1751  20   0 193376 15656 poll_s Sl+  tty2       0:00 /usr/libexec/gnome-sess
0  1000    3485    3477  20   0  13644  5636 do_wai Ss   pts/0      0:00 bash
0  1000    3857    3477  20   0  13540  5396 do_wai Ss   pts/1      0:00 bash
0  1000    5036    3485  20   0   2488   584 hrtime S+   pts/0      0:00 ./zad2
0  1000    5037    3485  20   0  10752   588 pipe_w S+   pts/0      0:00 cat
0  1000    5038    3485  20   0  10752   588 pipe_w S+   pts/0      0:00 cat
0  1000    5041    3857  20   0  13936  3360 -      R+   pts/1      0:00 ps l



ponizej podane sa informacje o plikach w folderze fd 
folder fd znajduje sie w podsystemie plikow katalogu proc
0 oznacza wejscie
1 i 2 oznaczaja wyjscie


jakub@jakub-VirtualBox:/proc/4973$ ls -l /proc/5036/fd
total 0
lrwx------ 1 jakub jakub 64 lis 18 20:02 0 -> /dev/pts/0
l-wx------ 1 jakub jakub 64 lis 18 20:02 1 -> 'pipe:[66738]'
lrwx------ 1 jakub jakub 64 lis 18 20:02 2 -> /dev/pts/0

jakub@jakub-VirtualBox:/proc/4973$ ls -l /proc/5037/fd
total 0
lr-x------ 1 jakub jakub 64 lis 18 20:02 0 -> 'pipe:[66738]'
l-wx------ 1 jakub jakub 64 lis 18 20:02 1 -> 'pipe:[66740]'
lrwx------ 1 jakub jakub 64 lis 18 20:02 2 -> /dev/pts/0

jakub@jakub-VirtualBox:/proc/4973$ ls -l /proc/5038/fd
total 0
lr-x------ 1 jakub jakub 64 lis 18 20:03 0 -> 'pipe:[66740]'
l-wx------ 1 jakub jakub 64 lis 18 20:03 1 -> /dev/null
lrwx------ 1 jakub jakub 64 lis 18 20:03 2 -> /dev/pts/0


Mozemy odtworzyc kolejnosc wystepowania polecen w pliku
poprzez sledzenie wyjscia i wejscia 

jednen program na wyjscie daje dane
1 -> 'pipe:[66738]' 

drugi program dane odbiera
0 -> 'pipe:[66738]'
ten sam program wysyla je dalej
1 -> 'pipe:[66740]' 
itd.

ponizej zaprezentowana zawartosc pliku status

jakub@jakub-VirtualBox:/proc/4973$ cat /proc/5036/status
Name:	zad2
Umask:	0002
State:	S (sleeping)
Tgid:	5036
Ngid:	0
Pid:	5036
PPid:	3485
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 46 120 131 132 1000 
NStgid:	5036
NSpid:	5036
NSpgid:	5036
NSsid:	3485
VmPeak:	    2488 kB
VmSize:	    2488 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	     584 kB
VmRSS:	     584 kB
RssAnon:	      64 kB
RssFile:	     520 kB
RssShmem:	       0 kB
VmData:	     180 kB
VmStk:	     132 kB
VmExe:	       8 kB
VmLib:	    1644 kB
VmPTE:	      44 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
CoreDumping:	0
THP_enabled:	1
Threads:	1
SigQ:	0/15523
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000006a00
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	0000003fffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Speculation_Store_Bypass:	vulnerable
Cpus_allowed:	7
Cpus_allowed_list:	0-2
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	1301
nonvoluntary_ctxt_switches:	4
jakub@jakub-VirtualBox:/proc/4973$ 



*/
