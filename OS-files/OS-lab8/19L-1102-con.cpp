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
  int shmid=shmget(168, 1024 , 0 ); //We have not passed IPC_CREAT, this means that it will always use existing shared region.
    if(shmid== -1)
      {
   cout<<"Consumer error";
      return 1; 
    }

  sem_t *mysm1=sem_open("sname",0);
  sem_t *mysm2=sem_open("sname2",0);
  char *word= (char*) shmat(shmid, NULL, 0); 
 

 int i=0;
while(1)
 {
   sem_wait(mysm1);

      if(word[0]!='$')
	   {
	        while(i<20)
	        {
	          cout<<word[i];
	          i=i+1;
	        }
	              i=0;
		char key_input;
		cout<<" Press key then enter to continue ";
		cin>>key_input;
		
		sem_post(mysm2);
	   }
	   else if(word[0]=='$')
	   {
	      break;
	   }
 }
  
    shmctl(shmid, IPC_RMID, NULL); 		//mark the shared region for deletion
  
   sem_close(mysm1);
     sem_close(mysm2);
      
 //detach
 shmdt(word);
 

}

