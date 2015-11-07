Script started on Sat 07 Nov 2015 07:15:01 AM UTC
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls && echo a
Makefile  README.md  a.out*  almost.cpp  edit.cpp  rshell.cpp  single_command.sh  temp	test.cpp  typescript
a
tmodi001@cs_private:~/workspace/cs100/assn1 $ echo 1 && a || ls
1
bash: a: command not found
Makefile  README.md  a.out*  almost.cpp  edit.cpp  rshell.cpp  single_command.sh  temp	test.cpp  typescript
tmodi001@cs_private:~/workspace/cs100/assn1 $ echo 1 && echo 2 || echo 3
1
2
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls -a; echo hello; mkdir test
./   Makefile	a.out*	    edit.cpp	single_command.sh  test.cpp
../  README.md	almost.cpp  rshell.cpp	temp		   typescript
hello
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls
Makefile   a.out*      edit.cpp    single_command.sh  test/	typescript
README.md  almost.cpp  rshell.cpp  temp 	      test.cpp
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls -a; echo hello && mkdir test || echo world;
./   Makefile	a.out*	    edit.cpp	single_command.sh  test/     typescript
../  README.md	almost.cpp  rshell.cpp	temp		   test.cpp
hello
mkdir: cannot create directory ‘test’: File exists
world
tmodi001@cs_private:~/workspace/cs100/assn1 $ rmdir test && echo done
done
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls
Makefile  README.md  a.out*  almost.cpp  edit.cpp  rshell.cpp  single_command.sh  temp	test.cpp  typescript
tmodi001@cs_private:~/workspace/cs100/assn1 $ ls -a || ls
./   Makefile	a.out*	    edit.cpp	single_command.sh  test.cpp
../  README.md	almost.cpp  rshell.cpp	temp		   typescript
tmodi001@cs_private:~/workspace/cs100/assn1 $ exit
exit

Script done on Sat 07 Nov 2015 07:17:21 AM UTC
