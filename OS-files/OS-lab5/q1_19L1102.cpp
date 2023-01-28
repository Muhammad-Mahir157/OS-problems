#include<iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include<string>
#include<cstring>
using namespace std;

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
   
   int descrip=fork();

  if(descrip==0)
   {
  /* int key_shm= shmget(12321,getpagesize(), 0 );

   datahandle* ptr=(datahandle*) shmat(key_shm, NULL, 0);
   cout<<"Shared memory with id In Child: "<<key_shm<<endl;*/
  
     //child writes in shared memory
        cout<<"Child here"<<endl;
         char* temp=new char[2000];     
     int read_file=open("input.txt",O_RDONLY,0);  
       if(read_file==-1)
       cout<<"Read failed"<<endl;
     int r_count=read(read_file,temp,2000);
      temp[r_count]='\0';
   
     // writing    
          ptr->filehandle= copystr(temp);
     
      
       cout<<"Child gone"<<endl;
     //updating check to go back to parent 
          ptr->check=10; 
  
    ptr->check=-3;
    cout<<"waiting for the parent to modify"<<endl;
    while(ptr->check==-3);  
    
    cout<<"Child here 2nd time"<<endl;
         //reading modified data 
       char* temp2=new char[2000];    
         temp2= copystr(ptr->filehandle);
  
       //writing modified data
       int f_write=open("input.txt",O_WRONLY | O_CREAT, S_IRWXU);   
        if(f_write==-1)
       cout<<"Write failed"<<endl;     
           int w2_count= write(f_write,temp2, strlen(temp2)); 
        
    
    
     cout<<"Child gone 2nd time"<<endl;  
       //deleting shared memory
       shmctl(key_shm,IPC_RMID,NULL);
       
       // de-attaching
       shmdt(ptr);
       
       //updating check to go back to parent  
          ptr->check=20;   
    
  }
    else if(descrip>0)
    {
     /* int key_shm= shmget(12321,getpagesize(), IPC_CREAT | IPC_EXCL | 0666 );

   datahandle* ptr=(datahandle*) shmat(key_shm, NULL, 0);
   cout<<"Shared memory with id In parent: "<<key_shm<<endl;*/
   
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
         
      
      //writing modified data
          ptr->filehandle= copystr(buffer);
          
         
     
       
       //updating check to go back to parent 
          ptr->check=30; 
      
    
    //De-attaching
      shmdt(ptr); 
      cout<<"De-attached"<<endl;
    }
  else
     cout<<"Fork has failed"<<endl;
     
     return 0;

}

