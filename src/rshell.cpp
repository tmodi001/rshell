#include <iostream>

using namespace std;

void  execute(char *argv[temp]) {
 pid_t pid;
 int status;
 
 if ((pid = fork()) < 0) {
    printf("Fork Failed!\n");
    exit(1);
 }
 else if (pid == 0) {
    printf("Child: executing\n");
    execvp(args[temp], args);
    perror("execvp failed");
 }
 else if (c_pid > 0){
    if( (pid = wait(&status)) < 0){
      perror("wait");
      exit(1);
    }
    printf("Parent: finished\n");
  }
}

int main(){
string temp;
while (temp != "exit"){
 cout << "$ ";
 getline(cin, command);
 unsigned place = 0;
 
 do_work(command, place);
 
 }
}
