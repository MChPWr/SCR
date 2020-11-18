
//uruchomilem program ./zad3 potem znajac numer PID moglem wejsc do podsystemu plikow proc $cd proc/4973
//pliki znajdujace sie w folderze mozna otworzyc programem cat
								   
/*
jakub@jakub-VirtualBox:~$ cd /proc/4973
jakub@jakub-VirtualBox:/proc/4973$ ls
arch_status      environ    mountinfo      personality   statm
attr             exe        mounts         projid_map    status
autogroup        fd         mountstats     root          syscall
auxv             fdinfo     net            sched         task
cgroup           gid_map    ns             schedstat     timers
clear_refs       io         numa_maps      sessionid     timerslack_ns
cmdline          limits     oom_adj        setgroups     uid_map
comm             loginuid   oom_score      smaps         wchan
coredump_filter  map_files  oom_score_adj  smaps_rollup
cpuset           maps       pagemap        stack
cwd              mem        patch_state    stat
jakub@jakub-VirtualBox:/proc/4973$ cat mountinfo 
*/

//poleceniem cat moglem wyswietlisc zawartosc pliku

