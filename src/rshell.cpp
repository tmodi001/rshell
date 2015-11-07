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

//Master Variable checks if the user ever enters exit
bool MASTER = true;

//Execute function will execute the passed in command
bool execute (char **argv)
{
  pid_t  pid;
  int    status;
  
  //Checks if the fork was successful or not
  if ((pid = fork()) < 0)
  {
    printf("Forking child process failed\n");
    return false;
  }
  
  //Checks if we are in a child call
  else if (pid == 0)
  {
    if (execvp(*argv, argv) < 0)
    {
      //If the execute fails and returns the negative
      printf("Invalid Prompt Entered!\n");
      return false;
    }
  }
  
  //Otherwise we are in a parent call
  else
  {
    while (wait(&status) != pid);
  }
  return true;
}

//Check will check the first and remove spaces and add it to second
void check (char *first, char **second)
{
  while (*first != '\0') {
    while (*first == ' ')
    {
      *first++ = '\0';
    }
    *second++ = first;
    while (*first != '\0' && *first != ' ') 
    {
      first++;
      
    }
  }
  *second = '\0';
}

//separate will execute single commands or prepare commands with || and && to
//run conditionally
void separate(vector<char *> words) {
  
  //Overall loop for each of the commands passed in
  for (unsigned i = 0; i < words.size(); ++i) {
    
    //ororFirst refers to if we find || first
    bool ororFirst = false;
    //andandFirst refers to if we find && first
    bool andandFirst = false;
    
    //Loop to check which is the first we find if any
    for (unsigned j = 0; words.at(i)[j] != '\0'; ++j) {
      
      //Checking for ||
      if (words.at(i)[j] == '|' && words.at(i)[j+1] == '|') {
        if (!andandFirst) {
          ororFirst = true;
        }
      }
      
      //Checking for &&
      if (words.at(i)[j] == '&' && words.at(i)[j+1] == '&') {
        if (!ororFirst) {
          andandFirst = true;
        }
      }
      
    }
    
    //If || is found first
    if (ororFirst) {
      //Find the size of the command
      unsigned size = 0;
      for (size = 0; words.at(i)[size] != '|'; ++size) {}
      
      //Create new c string for the first command
      char firstCommand[1000];
      
      //Finds the first and the last position of the overall command to remove
      //spaces from the first and the back ends
      unsigned firstposition = 0;
      unsigned lastposition = size-1;
      
      //Loop for leading spaces
      for(firstposition = 0; words.at(i)[firstposition] == ' ';
      ++firstposition) {}
      
      //Loop for trailing spaces
      for(lastposition = size-1; words.at(i)[lastposition] == ' ';
      --lastposition) {}
      
      //Create an iterator to iterate from firstposition to lastposition
      unsigned iterator = firstposition;
      unsigned l = 0;
      
      //Copy the command from the vector to the firstcommand c string
      for (l = 0; iterator <= lastposition; ++l, ++iterator) {
        firstCommand[l] = words.at(i)[iterator];
      }
      
      //Add the null character to the end
      firstCommand[l] = '\0';
      
      //Create a holder test variable
      char* test[64];
      
      //Call check on the firstcommand and test to push command onto test
      check(firstCommand, test);
      
      //Ensure that the command was not exit
      if (strcmp(test[0], "exit") == 0) {
        MASTER = false;
        exit(0);
      }
      
      //Increase the size by 2 to pass the || entry
      ++size;
      ++size;
      
      //Test for the success of the command
      bool success = execute(test);
      
      //If the firstcommand fails, then execute the following
      if(!success) {
        //Obtain the size of the following command
        unsigned size2 = 0;
        for(unsigned k = size; words.at(i)[k] != '\0'; ++k,++size2) {}
        
        //Create a c string for the second command
        char secondCommand[1000];
        
        //Create a starting point for the new second command
        unsigned z = 0;
        //load the second command into the second command variable from vector
        for(unsigned k = size; k < size + size2; ++k, ++z) {
          secondCommand[z] = words.at(i)[k];
        }
        
        //Terminate with the null character
        secondCommand[size2] = '\0';
        
        //Create a new storage vector for the second command
        vector<char *> v;
        
        //Push it on
        v.push_back(secondCommand);
        
        //Recursively call separate on the new storage vector for the second
        //and possibly more chained
        separate(v);
      }
      
      //IF && is found first
    } else if (andandFirst) {
      //Obtain the size of the command
      unsigned size = 0;
      for (size = 0; words.at(i)[size] != '&'; ++size) {}
      
      //Create new c string for the first command
      char firstCommand[1000];
      
      //Finds the first and the last position of the overal command to remove
      //spaces from the first and the back ends
      unsigned firstposition = 0;
      unsigned lastposition = size-1;
      
      //Loop for the leading spaces
      for(firstposition = 0; words.at(i)[firstposition] == ' ';
      ++firstposition) {}
      
      //Loop for trailing spaces
      for(lastposition = size-1; words.at(i)[lastposition] == ' ';
      --lastposition) {}
      
      //Create an iterator to iterator from firstposition to lastposition
      unsigned iterator = firstposition;
      unsigned l = 0;
      
      //Copy the command from the vector to the firstcommand c string
      for (l = 0; iterator <= lastposition; ++l, ++iterator) {
        firstCommand[l] = words.at(i)[iterator];
      }
      
      //Terminate with null character
      firstCommand[l] = '\0';
      
      //Create test to copy into
      char* test[64];
      
      //Check to check from the firstcommand and push into test
      check(firstCommand, test);
      
      //Ensure that the command passed in was not exit
      if (strcmp(test[0], "exit") == 0) {
        MASTER = false;
        exit(0);
      }
      
      //Increase the size by 2 to pass the && entry
      ++size;
      ++size;
      
      //Test for the success of the command
      bool success = execute(test);
      
      //If the firstcommand succeeds, then execute the following
      if(success) {
        //Find the size of the remaining command(s)
        unsigned size2 = 0;
        for(unsigned k = size; words.at(i)[k] != '\0'; ++k,++size2) {}
        
        //Create a c string for the following commnads
        char secondCommand[1000];
        
        //Create a starting point for the new second command
        unsigned z = 0;
        //Load the second command into the second command variable from vector
        for(unsigned k = size; k < size + size2; ++k, ++z) {
          secondCommand[z] = words.at(i)[k];
        }
        
        //Terminate with the null character
        secondCommand[size2] = '\0';
        
        //Create a new storage vector for the second command
        vector<char *> v;
        v.push_back(secondCommand);
        
        //Recursively call separate on the new storage vector for the 
        //commands that will follow
        separate(v);
      }
      
      //If neither || or && is found
    } else {
      
      //Find the size of the command
      unsigned size = 0;
      for(size = 0; words.at(i)[size] != '\0'; ++size) {}
      
      //Find the first and the last position of the overall command to remove 
      //spaces from the front and the back ends
      unsigned firstposition = 0;
      unsigned lastposition = size-1;
      
      //Loop for leading spaces
      for(firstposition = 0; words.at(i)[firstposition] == ' ';
      ++firstposition) {}
      
      //Loop for trailing spaces
      for(lastposition = size-1; words.at(i)[lastposition] == ' ';
      --lastposition) {}
      
      //command will be a new c string to hold the entire command without the 
      //spaces the normal command has
      char command[1000];
      
      //create an iterator to iterate from firstposition to lastposition
      unsigned iterator = firstposition;
      unsigned l = 0;
      
      //Copy the command from the vector to the new command c string
      for (l = 0; iterator <= lastposition; ++l, ++iterator) {
        command[l] = words.at(i)[iterator];
      }
      
      //End with null character
      command[l] = '\0';
      
      //Create test variable
      char* test[64];
      
      //Call Check on command and test to push command onto test
      check(command, test);
      
      //Ensure that the command was not exit
      if (strcmp(test[0], "exit") == 0) {
        MASTER = false;
        exit(0);
      }
      
      //Execute the command
      execute(test);
    }
    
  }
}

//Main master loop to continuously obtain user input
int main()
{
  //Main loop which conditionally and continually runs until MASTER variable 
  //is false, aka user enters exit
  while (MASTER)
  {
    //Create a storage c string
    char str[100];
    
    //Create a vector to store into
    vector<char*> words;
    
    //Standard output the dollar sign 
    cout << "$ ";
    
    //Get user input and store into c string str
    cin.getline(str,100);
    
    //Create a new storage c string
    char* point;
    
    //Call string token on the original user inputted string and store in point
    point = strtok(str, ";");
    
    //As long as point is not null, aka empty, continually push back 
    //commands that are separated by semicolons into the vector
    while (point != NULL)
    {
      words.push_back(point);
      point = strtok (NULL, ";");
    }
    
    //Call the separate function on the vector
    separate(words);
    
    //If the master is ever returned as false, end the program
    if (!MASTER) {
      return 0;
    }
    
    //Clean the storage c string with null characters
    for (unsigned i = 0; i < 100; i++)
    {
      str[i] = '\0';
    }
    
    //Clear the vector
    words.clear();
  }
  return 0;
}
