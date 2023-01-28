#include <iostream>
using namespace std;
#include <string>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include<cstring>

static char* copystr(const char* arr) 
{
	char* temp=new char[strlen(arr)+1]; //Initializing an array
	int i=0;

	while(arr[i]!='\0')
	temp[i]=arr[i++];

	temp[i]='\0';

	return temp;

}
struct datahandle
{
   int check;
   char* filehandle;
};

int main()
{

  int key_shm= shmget(12321,getpagesize(), IPC_CREAT | IPC_EXCL | 0666 );

   datahandle* ptr=(datahandle*) shmat(key_shm, NULL, 0);
   cout<<"Shared memory with id: "<<key_shm<<endl;
   
 ptr->check=-1;
    cout<<"waiting for the child"<<endl;
    while(ptr->check==-1);   
      
  //parent reads from file 
      char* temp=new char[2000];
      temp= copystr(ptr->filehandle);
               
          char* buffer=new char[strlen(temp)+1]; 
          int  buf_count=0;     
       for(int i=0;temp[i]!='\0';i++)
       {
          if(!(temp[i]>=47 && temp[i]<58) )
            {
               if(temp[i]>64 && temp[i]<91)
               {
                 buffer[buf_count]=temp[i]+32;
                   buf_count++;
                }
                else if(temp[i]>96 && temp[i]<123)
                 {
                 buffer[buf_count]=temp[i]-32;
                   buf_count++;
                 }
                 else
                  {
                 buffer[buf_count]=temp[i];
                   buf_count++;
                  }                  
             }       
       }
           delete[] temp;
      
      //writing modified data
          ptr->filehandle= copystr(buffer);
          
         
       delete[] buffer;
       
       //updating check to go back to parent 
          ptr->check=30; 
      
    
    //De-attaching
      shmdt(ptr); 
      cout<<"De-attached"<<endl;


}
