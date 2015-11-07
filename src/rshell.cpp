#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

using namespace std;
bool MASTER = true;

bool execute (char **argv)
{
  pid_t  pid;
  int    status;
  
  if ((pid = fork()) < 0)
  {
    printf("Forking child process failed\n");
    return false;
  }
  
  else if (pid == 0)
  {
    if (execvp(*argv, argv) < 0)
    {
      printf("Invalid Prompte Entered!\n");
      return false;
    }
  }
  else
  {
    while (wait(&status) != pid);
  }
  return true;
}

void check (char *line, char **argv)
{
  while (*line != '\0') {
    while (*line == ' ')
    {
      *line++ = '\0';
    }
    *argv++ = line;
    while (*line != '\0' && *line != ' ') 
    {
      line++;
      
    }
  }
  *argv = '\0';
}

void separate(vector<char *> words) {
  for (unsigned i = 0; i < words.size(); ++i) {
    bool ororFirst = false;
    bool andandFirst = false;
    for (unsigned j = 0; words.at(i)[j] != '\0'; ++j) {
      if (words.at(i)[j] == '|' && words.at(i)[j+1] == '|') {
        if (!andandFirst) {
          ororFirst = true;
        }
      }
      if (words.at(i)[j] == '&' && words.at(i)[j+1] == '&') {
        if (!ororFirst) {
          andandFirst = true;
        }
      }
    }
    if (ororFirst) {
      cout << "|| detected first" << endl;
      unsigned size = 0;
      for (size = 0; words.at(i)[size] != '|'; ++size) {}
      char firstCommand[size];
      for (unsigned k = 0; k < size; ++k) {
        firstCommand[k] = words.at(i)[k];
      }
      firstCommand[size] = '\0';
      ++size;
      ++size;
      char* fcCopy[] = {firstCommand, 0};
      bool success = execute(fcCopy);
      if(!success) {
        unsigned size2 = 0;
        for(unsigned k = size; words.at(i)[k] != '\0'; ++k,++size2) {}
        char secondCommand[size2+1];
        unsigned z = 0;
        for(unsigned k = size; k < size + size2; ++k, ++z) {
          secondCommand[z] = words.at(i)[k];
        }
        secondCommand[size2] = '\0';
        vector<char *> v;
        v.push_back(secondCommand);
        separate(v);
      }
    } else if (andandFirst) {
      cout << "&& detected first" << endl;
      unsigned size = 0;
      for (size = 0; words.at(i)[size] != '&'; ++size) {}
      char firstCommand[size];
      for (unsigned k = 0; k < size; ++k) {
        firstCommand[k] = words.at(i)[k];
      }
      firstCommand[size] = '\0';
      ++size;
      ++size;
      char* fcCopy[] = {firstCommand, 0};
      bool success = execute(fcCopy);
      if(success) {
        unsigned size2 = 0;
        for(unsigned k = size; words.at(i)[k] != '\0'; ++k,++size2) {}
        char secondCommand[size2+1];
        unsigned z = 0;
        for(unsigned k = size; k < size + size2; ++k, ++z) {
          secondCommand[z] = words.at(i)[k];
        }
        secondCommand[size2] = '\0';
        vector<char *> v;
        v.push_back(secondCommand);
        separate(v);
      }
    } else {
      unsigned size = 0;
      for(size = 0; words.at(i)[size] != '\0'; ++size) {}
      
      int firstposition = 0;
      int lastposition = size-1;
      for(firstposition = 0; words.at(i)[firstposition] == ' '; ++firstposition) {}
      for(lastposition = size-1; words.at(i)[lastposition] == ' '; --lastposition) {}
      char command[(lastposition - firstposition) + 2];
      unsigned iterator = firstposition;
      unsigned l = 0;
      for (l = 0; iterator <= lastposition; ++l, ++iterator) {
        command[l] = words.at(i)[iterator];
      }
      command[l] = '\0';
      char* test[64];
      //execute(test);
      check(command, test);
      if (strcmp(test[0], "exit") == 0) {
        MASTER = false;
        exit(0);
      }
      execute(test);
    }
    
  }
}

int main()
{
  while (MASTER)
  {
    char str[100];
    vector<char*> words;
    cout << "$ ";
    cin.getline(str,100);
    char* point;
    point = strtok(str, ";");
    
    while (point != NULL)
    {
      words.push_back(point);
      point = strtok (NULL, ";");
    }
    
    separate(words);
    if (!MASTER) {
      return 0;
    }
    
    for (unsigned i = 0; i < 100; i++)
    {
      str[i] = '\0';
    }
    words.clear();
  }
  return 0;
}
