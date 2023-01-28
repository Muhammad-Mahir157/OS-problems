#include<iostream>
#include<sys/mman.h>
#include<pthread.h>
#include<cstring>
#include<cctype>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
using namespace std;

void* initial_change(void* m_map)
  {
  
    char* myptr= (char*) m_map;
    for(int x=0; x< 50; x++)
      {
        if( isdigit(myptr[x]) == true )
          myptr[x]=' ';
      }
      
      pthread_exit(NULL);
   }


void* final_change(void* m_map)
  {
  
    char* myptr= (char*) m_map;
    for(int x=0; x< 50; x++)
      {
        
        if( isdigit(myptr[x]) == true )
          myptr[x]=' ';
      }
      
      pthread_exit(NULL);
   }


int main(int numofarg ,char** nameofFile)
{
   char* ptr_map;

	int file_des=open(nameofFile[1], O_RDWR | O_CREAT , S_IRUSR | S_IWUSR);
	  if(file_des == -1)
	  cout<<"File openng error"<<endl;
    
    ptr_map= (char*) mmap( NULL, 100 , PROT_READ | PROT_WRITE , MAP_SHARED, file_des , 0);
        
        
        close(file_des);   
	pthread_t id1,id2;
	  
	  pthread_create( &id1, NULL, &initial_change, ptr_map);  //thread1
	  
	  pthread_join(id1, NULL);

  
	  ptr_map= ptr_map+ 50;
	  
	   pthread_create( &id2, NULL, &final_change, ptr_map);  //thread2
	  
	  pthread_join(id2, NULL);
	  
	
 munmap(ptr_map, 100);

  return 0;
}
