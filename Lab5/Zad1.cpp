#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
void error_f(const char* msg)//obsluga bledu tak zeby nie pisac za duzo razy 
{
    fprintf(stderr, "%s \n", msg);
    exit ;
}
int main()
{
    int fd_file, fd_map;
    char* plik, buffer[1];
    struct stat status;//przechowuje wlasciwiosci pliku
    int count; //numer ostatniego znaku
    char f_name[100];
    int i = 0;
    if ((fd_map = open("mainfile.txt", O_RDWR)) < 0)//sprawdzamy czy plik sie otworzyl (wy wypadku gdy nie zwraca -1)
    {
        error_f("Opening error");
    }
    while (1)
    {
        count = lseek(fd_map, 0, SEEK_END);//sprawdzamy dlugosc pliku pliku mapowania
        printf("Inster file name \n");
        printf("To end inster '.' \n");
        scanf("%s", f_name);
        if (f_name[0] == '.')
        {
            close(fd_map);
            return 0;
        }
        if ((fd_file = open(f_name, O_RDONLY)) < 0)
        {
            error_f("Can't read file\n");
        }
        else
        {
            if (fstat(fd_file, &status) == -1)//sprawdzamy status pliku -1 w wypadku gdy jest problem z plikiem
            {
                error_f("File status error");
            }
            plik = mmap(NULL, status.st_size + count, PROT_WRITE | PROT_READ, MAP_SHARED, fd_map, 0);//adres,dlugosc,comozna robic,czy ma byc widoczny,plik do ktorego mapujemy,offset
            ftruncate(fd_map, status.st_size + count);//obcina plik do dlugosci zadanej
            if (plik == MAP_FAILED)
            {
                error_f("Mapping error");
            }
            i = 0;
            while (read(fd_file, buffer, 1) > 0)//petla do przepisywania
            {
                plik[count + i] = buffer[0];
                i++;
            }
            close(fd_file);
        }
    }
}