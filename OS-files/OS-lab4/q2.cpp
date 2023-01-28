#include<iostream>
using namespace std;
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   int des_file[2];
   int buffer=pipe(des_file);

   buffer=fork();

   if (buffer==0)
        {
          close(des_file[0]);
        dup2(des_file[1], 1);
         close(des_file[1]);

     int check=execlp("man", "man","ls", NULL);
       }
     else if (buffer>0)
       {  
          wait(NULL);
           buffer=fork();

       if (buffer==0)
         {
     	  int open_file=open("resultfile.txt", O_WRONLY | O_CREAT, S_IRWXU);
     	 dup2(des_file[0], 0);
     	 dup2(open_file,1);
     	 close(des_file[0]);
     	 close(des_file[1]);
     	 int check2=execlp("grep","grep","ls",NULL);
         }
       else if (buffer>0)
          {
          close(des_file[0]);
           close(des_file[1]);
         }

     
     else
         {
                cout<<"Failed fork";
                return 1;
         }
   
   }
else
   {
    cout<<"Failed fork";
    return 1;
   }

}
