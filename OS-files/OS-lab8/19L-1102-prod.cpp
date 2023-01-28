#include <iostream>
using namespace std;
#include <sys/shm.h>
#include <string>
#include <sys/wait.h>
#include<fstream>
#include<semaphore.h>
#include<unistd.h>
#include <sys/types.h>
#include<fcntl.h>

int main()
{
   char temp;
   int shmid=shmget(168, 1024, 0666|  IPC_CREAT | IPC_EXCL);  
          
    if(shmid== -1)
	   {
	   cout<<"Producer error";
	    return 1;  
	    }
    cout<<" Hello1";
    cout<<" Hello";
    sem_t *mysm1=sem_open("sname"  ,O_CREAT ,0666 ,0);
    sem_t *mysm2=sem_open("sname2" ,O_CREAT ,0666 ,0);
     
  sem_init(mysm1,1,0);
  
  sem_init(mysm2,1,0);
  
  char *word= (char*) shmat(shmid, NULL, 0); 
 
 
 ifstream fopen;
 fopen.open("file.txt");
  
   if(fopen.is_open())
   {
     int k=0;
     int count=0;
       while(!fopen.eof())
	     {
	       fopen>>temp;
	       word[k]=temp;
	       cout<<word[k];
		k=k+1;
		
		if(k==20)
		{
		  k=0;
		  sem_post(mysm1);
		  sem_wait(mysm2);
		 }
	     }
   }
   else
     cout<<"Error file";
  

//writing $ at the end of file

  word[0]='$';
  sem_post(mysm1);
  
   sem_close(mysm1);
     sem_close(mysm2);
    
 //detach
 shmdt(word);

   
}

