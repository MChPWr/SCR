#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>  // open()
#define BUFOR 100

const char mapped_filename[15]="mapped_img";

int main(){
    char file_path[BUFOR];                  // zmienna do zapisu podanej przez uzytkownika nazwy 
    struct stat sb;                         // struktura statystyk pliku
    int fd_map=open(mapped_filename, O_RDWR);  // file descriptor dla pliku do którego mapujemy pamięć
    int fd_file;                            // file descriptor dla pliku czytanego
    size_t length;                          // rozmiar pamięci do zmapowania
    char *addr;                             // adres zmapowanej pamięci
    int pid=0;                              // do kontroli wartości zwracanej przez fork


    pid=fork();
    if(pid<0){                 // sprawdzamy czy fork się powiódł
        fprintf(stderr, "ERR:  Nie udało się utworzyć procesu dziecka" ); 
        return -1; 

    ///////////  DZIECKO  /////////////////
    }else if(pid==0){   
        char * arguments[3];
        arguments[0]="eog";
        arguments[1]=mapped_filename;
        arguments[2]=NULL;
        fprintf(stdout,"C:  Uruchamiam exec \n");
        execvp(arguments[0], arguments);
    ///////////  RODZIC  /////////////////
    }else{   
        while(1){
            printf("[EX to exit]   Podaj nazwe pliku do zmapowania: ");
            fscanf (stdin, "%s", file_path);
            if(file_path[0]=='E' && file_path[1]=='X' && file_path[2]=='\0'){break;};
            stat(file_path, &sb);
            length=sb.st_size;
            addr=mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED,fd_map, 0);
            msync(addr,length,MS_SYNC);
            ftruncate(fd_map, length);
            fd_file=open(file_path,O_RDONLY|O_CREAT,  S_IRWXU);
            if (fd_file == -1){ 
                fprintf(stderr,"ERR: Nie można otworzyć pliku do odczytu \n");
            }else{
                read(fd_file, addr, length);
            };
            munmap(addr, length);
        };
    };
    close(fd_map);
}