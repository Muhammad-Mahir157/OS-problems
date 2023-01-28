#include<iostream>
#include<pthread.h>
#include<cmath>
#include<semaphore.h>
#include<fstream>
using namespace std;

 int* arr;
 int* arr2;
int mean=0;
int size=0;
float std_dev=0;

sem_t sm1;
sem_t sm2;
sem_t sm3;
sem_t sm4;
//sem_t sm5;

void* printall(void* temp)		//1
{
 
  ifstream getInput;
    getInput.open("input.txt");
  
      getInput>>size;
   arr=new int[size];
     for(int x=0;x<size;x++)
     {
        getInput>>arr[x];
     }
     //printing
     cout<<" *** Printing Data ***"<<endl;
    for(int x=0;x<size;x++)
     {
        cout<<arr[x]<<" ";
     }
     cout<<endl;
     
     sem_post(&sm1);
  pthread_exit(NULL); 
}

void* cal_mean(void* temp)			//2
{
  sem_wait(&sm1);
  int sum=0;
   for(int i=0;i<size;i++)
   {
      sum=sum+arr[i];
   }
     mean=sum/size;
     
     sem_post(&sm2);
  pthread_exit(NULL); 
}

void* SquareOfNum(void* temp)		//3
{
  sem_wait(&sm2);
  arr2=new int[size];
  int num=0;
    for(int i=0;i<size;i++)
   {
      num=arr[i]-mean;
       if(num<0)
       num=num*-1; 
       
      num=num*num;		//squaring
      arr2[i]=num;		//storing in another global array
   }
     
     sem_post(&sm3);
  pthread_exit(NULL); 
}

void* cal_stddev(void* temp)		//4
{
 sem_wait(&sm3);
  for(int x=0;x<size;x++)
  {
     std_dev=std_dev+arr2[x];
  }
     
     std_dev=sqrt(std_dev/size);    
     sem_post(&sm4);
  pthread_exit(NULL); 
}

void* result_value(void* temp)	//5
{
   sem_wait(&sm4);
    cout<<" Standard deviation :- "<<std_dev<<endl;
     cout<<" Mean :- "<<mean<<endl;
     for(int x=0;x<size;x++)
     {
        cout<<arr2[x]<<" ";
     }
     cout<<endl;
  pthread_exit(NULL); 
}

int main(){
   //Initialize your semaphores here
   sem_init(&sm1, 0, 0);
   sem_init(&sm2, 0, 0);
   sem_init(&sm3, 0, 0);
   sem_init(&sm4, 0, 0);
  // sem_init(&sm5, 0, 0);
   
  pthread_t id1,id2,id3,id4,id5;
  
pthread_create(&id1,NULL, &printall, NULL);
pthread_create(&id2,NULL, &cal_mean, NULL);
pthread_create(&id3,NULL, &SquareOfNum, NULL);
pthread_create(&id4,NULL, &cal_stddev, NULL);
pthread_create(&id5,NULL, &result_value, NULL);

pthread_join(id2,NULL);
pthread_join(id1,NULL);
pthread_join(id4,NULL);
pthread_join(id3,NULL);
pthread_join(id5,NULL);
//Destroy your semaphores here

   sem_destroy(&sm1);
   sem_destroy(&sm2);
   sem_destroy(&sm3);
   sem_destroy(&sm4);
   
}
