#include <stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include<semaphore.h>
using namespace std;

int x=0;
int total_threads=0;
sem_t sem_special;

//sem_t* sem_ordinary;

void* special_thread(void* temp)
{
    sem_wait(&sem_special);             			
   printf("\n Successfully executed all the Threads \n");
   
  // for(int j=0;j<total_threads; j++)
   //   sem_destroy(&sem_ordinary[j]);
  

   sem_destroy(&sem_special);
   pthread_exit(NULL);

}

void* just_printing(void* temp)
{ 
   //sem_wait(&sem_ordinary[x]);		//[0], [1]+
   
       x=x+1;
      printf("%d", x);
      printf("\n");
      
   //  if(x != total_threads)			//[1]+
   // sem_post(&sem_ordinary[x]);		
    
      if(x == total_threads)
         sem_post(&sem_special);
}

int main(int noOfinput,char** arr)
 { 

   int num=atoi(arr[1]);
    printf(" No of threads to be created: %d", num); 
    printf("\n");
    total_threads=num;
    
   sem_init(&sem_special ,0,0);
   
   /*sem_ordinary= new sem_t[total_threads];
   sem_init(&sem_ordinary[0] ,0, 1);
   
   for(int k=1; k<total_threads; k++)
     sem_init(&sem_ordinary[k] ,0, 0);*/
   
     pthread_t special_id;
 pthread_create( &special_id, NULL, &special_thread, NULL);
 
     pthread_t key[num];
     
	 for (int i=0; i<num; i++)
	 {
	   pthread_create(&key[i], NULL, &just_printing, NULL);
	 }   
    
	 for (int i=0; i<num; i++)
	 {
	   pthread_join(key[i], NULL);
	 }

      pthread_join(special_id,NULL);
 
 return 0;
 
  }

