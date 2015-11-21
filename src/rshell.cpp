#include <iostream>
#include <string>
#include <cstring>
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
#include <sys/stat.h>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>

using namespace std;

//Master Variable checks if the user ever enters exit
bool MASTER = true;

//Execute function will execute the passed in command
void execute (char **argv, int &t) {
  pid_t  pid;
  int status;
  
  //Checks if the fork was successful or not
  if ((pid = fork()) < 0)
  {
    printf("Forking child process failed\n");
    exit (1);
  }
  
  //Checks if we are in a child call
  else if (pid == 0)
  {
    // if (execvp(*argv, argv) < 0)
    // {
    //   //If the execute fails and returns the negative
    //   printf("Invalid Prompt Entered!\n");
    //   return false;
    // }
    
    t = execvp(*argv, argv);
    printf("Invalid Prompt Entered!\n");
    exit(errno);
    
  }
  
  //Otherwise we are in a parent call
  else
  {
    //while (wait(&status) != pid);
    pid = wait(&status);
    
    if (WIFEXITED(status)) {
      t =  WEXITSTATUS(status);
    }
  }
}

//Tests if a file exists
bool testfile(const char* t) {
	struct stat fs;
	if (stat(t, &fs) != 0) {
		return false;
	}
	return S_ISREG(fs.st_mode);
}

//Tests if a directroy exists
bool testdirectory(const char* t) {
	struct stat ds;
	if (stat(t, &ds) != 0) {
		return false;
	}	
	return S_ISDIR(ds.st_mode);
}

//Executes if test is called or brackets
bool test_command(const char* t) {
  //cout << t << endl;
  
  //bool varbiles to test for differrent things like flags
  char test[1000];
  int counter = 0;
  bool bracket = false;
  bool word = false;
  bool start = false;
  bool end = false;
  bool flag = false;
  bool eflag = true;
  bool fflag = false;
  bool dflag = false;
  bool bend = false;
  for (unsigned j = 0; t[j] != '\0'; ++j) {
    //Checks for end bracket
    if (bracket) {
      if (t[j] == ' ' && t[j + 1] == ']') {
        end = true;
        bend = true;
      }
    }
    
    //Checks for vaild end bracket
    if (bracket && !end) {
      if (t[j] == ']') {
         cout << "Need a have before space ']'\n";
         return false;
      }
    }
    
    //adds to test c_string
    if (start && !end) {
      test[counter] = t[j];
      counter++;
    }
    // checks for end of test
    if (word) {
      if (t[j + 1] == '&' || t[j + 1] == '|' || t[j + 1] == '\0') {
        end = true;
      }
    }
    
    //checks for start of test
    if (!start) {
      if (t[j] == 't' && t[j + 1] == 'e') {
        if (t[j + 2] == 's' && t[j + 3] == 't') {
          start = true;
          word = true;
          j = j + 3;
        }
      }
    }
    
    //checks for start of bracket
    if (!start) {
      if (t[j] == '[' && t[j + 1] == ' ') {
        start = true;
        bracket = true;
        j++;
      }
    }
    
    // checld for vaild start bracket
    if (!start) {
      if (t[j] == '[' && t[j + 1] != ' ') {
        cout << "Need a have after space '['\n";
        return false;
      }
    }
    
  }
  
  test[counter] = '\0';
  int j1 = 0;
  char t2[100];
  int t2c = 0;
  
  //removes spaces
  for (j1; test[j1] == ' '; j1++) {}
  
  //Checks for flags
  if (test[j1] == '-') {
    //checks for d flag
    if (test[j1 + 1] == 'd' && test[j1 + 2] == ' ') {
      dflag = true;
      eflag = false;
      flag = true;
      j1 = j1 + 2;
    }
    //checks for f flag
    else if (test[j1 + 1] == 'f' && test[j1 + 2] == ' ') {
      fflag = true;
      flag = true;
      eflag = false;
      j1 = j1 + 2;
    }
    //checks for e flag
    else if (test[j1 + 1] == 'e' && test[j1 + 2] == ' ') {
      flag = true;
      j1 = j1 + 2;
    }
    // prints the valid flags if flag was not inputted properly
    else {
      cout << "Invalid flag!\nUse the following flags:\n";
      cout << "-e checks if the file/directory exists\n";
      cout << "-f checks if the file/directory exists";
      cout << "and is a regular file\n";
      cout << "-d checks if the file/directory exists and is a directory\n";
      eflag = false;
    }
  }
  
  //makes sure the back of test was entered properly
  for (j1; test[j1] == ' '; j1++) {}
  if (test[j1] != '\0') {
    
    //checks for null character or space
    for (j1; test[j1] != '\0' && test[j1] != ' '; j1++) {
      t2[t2c] = test[j1];
      t2c++;
    }
    t2[t2c] = '\0';
    for (j1; test[j1] == ' '; j1++) {}
    
    //checks for end bracket
    if (bracket) {
      if (!bend) {
        cout << "Bracket not ended properly!\n";
        return false;
      }
    }
    
    //prints error if not ended properly
    if (test[j1] != ']' && test[j1] != '\0') {
      cout << "Error!\n";
      return false;
    }
  }
  
  //cout << "Going to test:" << t2 << endl;
  
  //Executes the paths
  //this executes e flag
  if (eflag) {
    if (testfile(t2)) {
      //cout << "The file " <<  t2 << " exists!\n";
      return true;
    }
    if (testdirectory(t2)) {
        //cout << "The directory " << t2 << " exists!\n";
        return true;
    }
    //cout << "No path to: " << t2 << endl;
    return false;
  }
  
  //this executes f flag
  if (fflag && end) {
    if (testfile(t2)) {
      //cout << "The file " <<  t2 << " exists!\n";
      return true;
    }
    else {
      //cout << "The file " << t2 << " does not exist!\n";
      return false;
    }
  }
  
  //this executes d flag
  if (dflag && end) {
    if (testdirectory(t2)) {
        //cout << "The directory " << t2 << " exists!\n";
        return true;
      }
      else {
        //cout << "The directory " << t2 << " does not exist!\n";
        return false;
    }
  }
}

//Check will check the first and remove spaces and add it to second
void check (char *first, char **second) {
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
bool separate(vector<char *> words) {
  
  //Overall loop for each of the commands passed in
  for (unsigned i = 0; i < words.size(); ++i) {
    //cout << "separate:" << words.at(i) << endl;
    
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
      
      //Checks for a test call
      bool ttt;
      bool callme = false;
      for (unsigned j = 0; words.at(i)[j] != '\0' && words.at(i)[j] != '&' 
        && words.at(i)[j] != '|'; ++j) {

        if (words.at(i)[j] == 't' && words.at(i)[j + 1] == 'e') {
          if (words.at(i)[j + 2] == 's' && words.at(i)[j + 3] == 't') {
            callme = true;
            j = j + 3;
          }
        }
      
        if (words.at(i)[j] == '[') {
          callme = true;
        }
      }
      
      //Calls test funtion if test in found in input
      if (callme) {
        ttt = test_command(words.at(i));
      }
      int pass = 0;
      if (!callme) {
        //int pass = 0;
        execute(test, pass);
        if (pass == 0) { return true;}
      }
      
      
      //If the firstcommand fails, then execute the following
      if(pass != 0 || !ttt) {
        //Obtain the size of the following command
        unsigned size2 = 0;
        for(unsigned k = size; words.at(i)[k] != '\0'; ++k,++size2) {}
        
        //Create a c string for the second command
        char s[1000];
        
        //Create a starting point for the new second command
        unsigned z = 0;
        //load the second command into the second command variable from vector
        for(unsigned k = size; k < size + size2; ++k, ++z) {
          s[z] = words.at(i)[k];
        }
        
        //Terminate with the null character
        s[size2] = '\0';
        
        //Create a new storage vector for the second command
        vector<char *> v;
        
        //Push it on
        v.push_back(s);
        
        //Recursively call separate on the new storage vector for the second
        //and possibly more chained
        //return (separate(v));
        return separate(v);
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
      
      //Checks for a test call
      bool ttt;
      bool callme = false;
      for (unsigned j = 0; words.at(i)[j] != '\0' && words.at(i)[j] != '&' 
        && words.at(i)[j] != '|'; ++j) {

        if (words.at(i)[j] == 't' && words.at(i)[j + 1] == 'e') {
          if (words.at(i)[j + 2] == 's' && words.at(i)[j + 3] == 't') {
            callme = true;
            j = j + 3;
          }
        }
      
        if (words.at(i)[j] == '[') {
          callme = true;
        }
      }
      
      //Calls test funtion if test in found in input
      if (callme) {
        ttt = test_command(words.at(i));
        //temp = true;
      }
      
      int pass = 0;
      bool idk = false;
      if (!callme) {
        //cout << "Test: " << *test << endl;
        execute(test, pass);
        if (pass != 0) {return false;}
        if (pass == 0) {idk = true;}
      }
      
      //If the firstcommand succeeds, then execute the following
      if(idk || ttt) {
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
        //return (success | separate(v));
        return separate(v);
        
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
      
      // Checks if test in inputed
      bool callme = false;
      for (unsigned j = 0; words.at(i)[j] != '\0'; ++j) {

        if (words.at(i)[j] == 't' && words.at(i)[j + 1] == 'e') {
          if (words.at(i)[j + 2] == 's' && words.at(i)[j + 3] == 't') {
            callme = true;
            j = j + 3;
          }
        }
      
        if (words.at(i)[j] == '[') {
          callme = true;
        }
      }
      
      //Calls test funtion if test in found in input
      if (callme) {
        return test_command(words.at(i));
      }
      
      //Execute the command
      int pass = 0;
      execute(test, pass);
      if (pass == 0) {return true;}
      if (pass != 0){return false;}
    }
  }
}

bool par_function(char *t) {
  //Contain will be the c string to hold part of the commands contained 
  //within a set of parentheses
  char contain[1000];

  // indicate whether there are parentheses or not
  bool temp = false;
  
  // First open parentheses position
  bool foP = false;
  
  //Temporary variables for if the string passed contains any parentheses
  //start will be the start of the commands contained inside a parentheses
  //end for the end
  //counter will keep track of the number of parentheses encountered
  int start = 0;
  int end = 0;
  int counter = 0;
  
  int i = 0;
  
  //Loop for checking if the string has a parentheses
  for (i = 0; t[i] != '\0'; ++i) {
    //When the first parentheses are found, set start, and set foP and temp
    //to be true
    if (!foP) {
      if (t[i] == '(') {
          start = i + 1;
          foP = true;
          temp = true;
      }
    }
    //If a open parentheses are found, increment our counter
    if (t[i] == '(') {
        counter++;
    }
    //If a close parentheses are found, decrement our counter if the counter
    //is not 1, which would be a sign of the final parentheses
    if (t[i] == ')') {
        if (counter == 1) {
            end = i - 1;
        }
        else {
            counter--;
        }
    }
  }
  
  int fill = 0;
  //If a parentheses is found
  if (temp)
  {
    //Variables we will be using for the beginning of the string of commands
    //b will be our c string to hold commands before
    //i and bi are iterators
    //a and o will be if we find an a or an o first
    //doit is a variable that will decide whether or not we should be pushing
    //commands into our separate
    char b[100];
    int i = 0;
    int bi = 0;
    bool a = false;
    bool o = false;
    bool doit = true;
    
    //checks for space in front
    for (i; t[i] == ' '; i++) {}
    if (t[i] != '(') {
      int ic = 0;
      for (i; t[i] != '('; i++, bi++) {
        b[bi] = t[i];
        if ((t[i] == '&' && t[i + 1] == '&') 
          || (t[i] == '|' && t[i + 1] == '|' )) {
          ic = i;
        }
      }
      
      //checks if & was entered
      if (b[ic] == '&') {
        if (!a && !o) {
          a = true;
          doit = false;
          //cout << "and detected\n";
        }
      }
      
      //checks if | was entered
      if (b[ic] == '|') {
        if (!a && !o) {
          o = true;
          doit = false;
          //cout << "or detected\n";
        }
      }
      b[ic] = '\0';
    }
    bool bw;
    b[bi] = '\0';
    //cout << "B: " << b << endl;
    
    //executes b if its not empty
    if (b[0] != '\0') {
      bw = par_function(b);
    }
    for (int k = start; k <= end; ++k)
    {
        contain[fill] = t[k];
        fill++;
    }
    contain[fill] = '\0';
    
    //executes firsthalf if need be
    bool firstHalf;
    if ((a && bw) || (o && !bw) || doit) {
      firstHalf = par_function(contain);
    }
    
    //If there is more commands after the final end parentheses
    if (t[end + 1] != '\0') {
      //Create another string to hold all commands after
      //secondHalf will be our storage
      //p is our iterator
      //orr and aand determine if we find a || or && first
      //newStart is the point where we start for our secondHalf
      char secondHalf[100];
      unsigned p = 0;
      bool orr = false;
      bool aand = false;
      int newStart = 0;
      
      for(unsigned k = end + 2 ; t[k] != '\0'; ++k) {
        
        //checks if && was entered
        if (t[k] == '&' && t[k + 1] == '&') {
          if (!aand && !orr) {
            aand = true;
            newStart = k + 2;
          }
        }
        
        //checks if || was entered
        if (t[k] == '|' && t[k + 1] == '|') {
          if (!orr && !aand) {
            orr = true;
            newStart = k + 2;
          }
        }
      }
      if (newStart != 0) {
        for(unsigned k = newStart; t[k] != '\0'; ++k, ++p) {
          secondHalf[p] = t[k];
        }
        secondHalf[p] = '\0';
        
        //Executes secondHalf if it needs to be
        if ((orr && !firstHalf) || aand) {
          par_function(secondHalf);
        }
      }
    }
      
  }
  //Otherwise if a parentheses is not found
  else {
    //Create a vector to store the command in, push it, and call separate on it
    vector<char *> v;
    v.push_back(t);
    bool temp = separate(v);
    return temp;
    
  }
   return true; 
}

//This funtion tests for comments
void dummy(vector<char *> words) {
  //Our dummy function has ending which determines if we are ending commands
  //there due to comments
  //comment determines if there is a comment or not
  //quotes determines if we are in a set of quotes or not
  bool ending = false;
  bool comment = false;
  bool quotes = false;
  //Overall loop for checking through the strings of commands
  for (unsigned i = 0; i < words.size(); ++i) {
    //Overall loop for checking through a single string of commands
    for (unsigned j = 0; words.at(i)[j] != '\0'; ++j) {
      //If we find quotes, and quotes is false, it means we are in a new
      //set of quotes
      if (words.at(i)[j] == '"' && !quotes) {
        quotes = true;
        //Otherwise if we find quotes and quotes is true, it means we are
        //ending the set of quotes we were in
      } else if (words.at(i)[j] == '"' && quotes) {
        quotes = false;
      }
      //If we find a # sign and the previous character is a space, and we are
      //not in a set of quotes, this means the user has entered in a comment
      if (words.at(i)[j] == '#' && words.at(i)[j-1] == ' ' && !quotes){
          words.at(i)[j] = '\0';
          comment = true;
      }
    }
    //If comments are found, we can end all future commands
    if (comment) {
      ending = true;
    }
    //Send the string to par function
    par_function(words.at(i));
    //if we need to end, simply return, otherwise the loop continues
    if (ending) {
      return;
    }
  }
}

int main() {
    
  //Main loop which conditionally and continually runs until MASTER variable 
  //is false, aka user enters exit
  while (MASTER) {
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
    dummy(words);
    
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
  //_CrtDumpMemoryLeaks();
  return 0;
}
