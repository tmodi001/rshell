Script started on Sat 07 Nov 2015 07:25:23 AM UTC
tmodi001@cs_private:~/workspace/cs100/assn1 $ ./a.out
$ ls && exit
Makefile   a.out       commented_command.sh  multi_command.sh  single_command.sh  test.cpp
README.md  almost.cpp  edit.cpp 	     rshell.cpp        temp		  typescript
tmodi001@cs_private:~/workspace/cs100/assn1 $ ./a.out
$ exit
tmodi001@cs_private:~/workspace/cs100/assn1 $ ./a.out
$ echo 1 #exit
1
$ echo 1 || exit
1
$ exit #exi
tmodi001@cs_private:~/workspace/cs100/assn1 $ ./a.out
$ ls || exit && a
Makefile   a.out       commented_command.sh  multi_command.sh  single_command.sh  test.cpp
README.md  almost.cpp  edit.cpp 	     rshell.cpp        temp		  typescript
$ a || ls && exit
Invalid Prompt Entered!
Makefile   a.out       commented_command.sh  multi_command.sh  single_command.sh  test.cpp
README.md  almost.cpp  edit.cpp 	     rshell.cpp        temp		  typescript
$ exit
tmodi001@cs_private:~/workspace/cs100/assn1 $ exit
exit

Script done on Sat 07 Nov 2015 07:27:03 AM UTC
