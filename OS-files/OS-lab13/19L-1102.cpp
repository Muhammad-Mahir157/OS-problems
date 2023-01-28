#include<iostream>
#include<sys/mman.h>
#include<pthread.h>
#include<cstring>
#include<cctype>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<semaphore.h>
using namespace std;

sem_t sm1;
sem_t sm2;
int main_counter=0;

struct mysubstr
{
    char* ptr_map;
    char* req_substring;
    int map_length;
};


void* initial_change(void* sub_obj)
  {
    sem_post(&sm1);
    sem_wait(&sm1);
     cout<<" \n Thread 1"<<endl;
    mysubstr* myclassobj= (mysubstr*) sub_obj;
    int count1=0,count2=strlen(myclassobj->req_substring) ;
    
    for(int x=0; x< myclassobj->map_length/2; x++)
      {
        if( myclassobj->req_substring[0] == myclassobj->ptr_map[x] )
         {
          for(int k=0; k<count2; k++)
            {
               if(myclassobj->req_substring[k] == myclassobj->ptr_map[x])
                               count1=count1+1;           
                    x++;
            }
            
         }
            if(count1 == count2)
              main_counter++;
           //  cout<<" T1 count: "<<count1<<endl;
             
               count1=0;
      }
    
     
      sem_post(&sm2);
       pthread_exit(NULL);
   }


void* final_change(void* sub_obj)
  {
      sem_wait(&sm2);
     cout<<" Thread 2"<<endl;
        mysubstr* myclassobj= (mysubstr*) sub_obj;
    int count1=0,count2=strlen(myclassobj->req_substring) ;

     
    for(int x=myclassobj->map_length/2 ; x< myclassobj->map_length; x++)
      {
        if( myclassobj->req_substring[0] == myclassobj->ptr_map[x] )
          {
          for(int k=0; k<count2; k++)
            {
               if(myclassobj->req_substring[k] == myclassobj->ptr_map[x])
                    count1++;
                    
                    x++;
                
            }
          } 
        
            if(count1 == count2)
              main_counter++;
          
        //  cout<<" T2 Count1 "<<count1<<endl; 
              count1=0;
      }
        
       pthread_exit(NULL);
   }


int main(int numofarg ,char** nameofFile)
{

	int file_des=open(nameofFile[1], O_RDWR | O_CREAT , S_IRUSR | S_IWUSR);
	  if(file_des == -1)
	  cout<<"File openng error"<<endl;
	
	sem_init(&sm1,0,0);
	sem_init(&sm2,0,0);
    mysubstr obj;
    obj.ptr_map= (char*) mmap( NULL, 1000 , PROT_READ | PROT_WRITE , MAP_SHARED, file_des , 0);
    obj.map_length=strlen( obj.ptr_map);
    cout<<" Len: "<<obj.map_length;
    
    int size=0;
    for(int k=2; k< numofarg; k++)
      size=size+strlen(nameofFile[k])+1;
     
     //size--;
      cout<<"\n Size:"<<size<<endl;
      
      obj.req_substring=new char[size];
     int s=0;
      for(int i=2; i<numofarg ;i++)
        {
          
           for(int j=0; nameofFile[i][j]!='\0'; j++)
             {
			obj.req_substring[s]=nameofFile[i][j];
			s=s+1;
	     }
		obj.req_substring[s]=' ';
		s=s+1;
        }
        obj.req_substring[s]='\0';
        
         cout<<obj.req_substring;
        
     /*  obj.req_substring=new char[size];
      strcpy(obj.req_substring,nameofFile[2]);
      
      
   for(int i=3;i< numofarg; i++)
     strcat(obj.req_substring,nameofFile[i] );
     
       cout<<obj.req_substring<<" ";
     
        // obj.req_substring=new char[strlen(nameofFile[2])];
          //strcpy(obj.req_substring,nameofFile[2]);
        
        cout<<obj.req_substring<<endl;*/
        close(file_des);   
	pthread_t id1,id2;
	  
	  pthread_create( &id1, NULL, &initial_change, &obj);  //thread1
	  
	   int num=0;
	  pthread_join(id1, NULL);
	cout<<" Thread 1 returned "<<endl;
	  
	   pthread_create( &id2, NULL, &final_change, &obj);  //thread2
	  
	 
	  pthread_join(id2, NULL );
	 cout<<" Thread 2 returned"<<endl;
	  cout<<" The no of sub strings are: "<< main_counter<<endl;
	  
 sem_destroy(&sm1);
  sem_destroy(&sm2);	
 munmap(obj.ptr_map, 1000);

  return 0;
}
