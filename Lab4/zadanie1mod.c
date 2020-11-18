#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>


int main(){
  int i=0;
  
  while(1){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
    printf("%d \n", i);
  }
}
