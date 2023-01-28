#include<iostream>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

int stopCount=0;
sem_t sm1;
sem_t sm2;
sem_t sm3;


int print_counter1=0;
int print_counter2=0;
int print_counter3=0;

void* thread1here(void* t1)
{
  
  while(1)
{  
   sem_wait(&sm1);   // 2,1
    if(stopCount>=27)
       break;
     cout<<"a";
     
       print_counter1=print_counter1 +1;
     
 
 if(print_counter1 == 2)
   {
      sem_post(&sm2);
      sem_post(&sm2);
      sem_post(&sm2);  
      print_counter1=0;
     
   }
     stopCount=stopCount+1;			//Used stop Count to avoid infinite loop
      cout<<"\n";
   if(stopCount>=27)
       break;
}
   pthread_exit(NULL);
}

void* thread2here(void* t2)
{
  while(1)
{
   
  sem_wait(&sm2);   // 3,2,1
cout<<"b";
  if(stopCount>=27)
       break;
  print_counter2=print_counter2 +1;
 
   
 if(print_counter2 == 3)
   {
      sem_post(&sm3);
      sem_post(&sm3);
       sem_post(&sm3);
      sem_post(&sm3);
      print_counter2=0;
     
   }
      stopCount=stopCount+1;			//Used stop Count to avoid infinite loop
       cout<<"\n";
    if(stopCount>=27)				//Since each complete patteren has 9 elements 2 A's, 3 B's,4 C's just add 9
       break;
}

    pthread_exit(NULL);
}

void* thread3here(void* t3)
{
  while(1)
  {
    
   sem_wait(&sm3);   // 4,3,2,1
     cout<<"c";
     
    print_counter3=print_counter3 +1;
   
     
  
  if(print_counter3 == 4)
   {
       sem_post(&sm1);
      sem_post(&sm1);
       print_counter3=0;
     
    }
    stopCount=stopCount+1;			//Used stop Count to avoid infinite loop
    cout<<"\n";
     if(stopCount>=27)
       break;
  }
    pthread_exit(NULL);
}

int main()
{
    sem_init(&sm1, 0, 0);
    sem_init(&sm2, 0, 0);
    sem_init(&sm3, 0, 0);
   
       sem_post(&sm1);   	//For the first iteration print
      sem_post(&sm1);

  pthread_t idofThread1,idofThread2,idofThread3;
  int checkerror1=pthread_create(& idofThread1,NULL, &thread1here, NULL);

   if(checkerror1== -1)
   {
    cout<<" Error in creating threads"<<endl;
      return 0;
    }

   int checkerror2=pthread_create(& idofThread2,NULL, &thread2here, NULL);

   if(checkerror2== -1)
   {
    cout<<" Error in creating threads"<<endl;
      return 0;
    }

   int checkerror3=pthread_create(& idofThread3 ,NULL, &thread3here, NULL);

   if(checkerror3== -1)
   {
    cout<<" Error in creating threads"<<endl;
      return 0;
    }

   pthread_join( idofThread1,NULL);
    pthread_join( idofThread2,NULL);
    pthread_join( idofThread3,NULL);
    
    sem_destroy(&sm1);
    sem_destroy(&sm2);
    sem_destroy(&sm3);
    
  
}
