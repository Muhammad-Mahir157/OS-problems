#include <iostream>
using namespace std;
#include <string.h>
#include<pthread.h>
#include<stdlib.h>

struct fibonumb
{
   int actual_number;
   int size;
};


int fibonacci_Count(int num)		// Helper function to determine size from a max fibonacci number passed to it
{
    bool flag=false;
     int count=0;
	int x1=0,x2=1;
	if(num==x1 )
          return 0;
         else if(num==x2)
           return 1;
	else
	{
	   count=2;
		int final=x1+x2;
	
	while(final<=num)
	{
	   count++;
		if(final==num)
		{
		   flag=true;
		     return count;
	        }
		x1=x2;
		x2=final;
		final=x1+x2;
	}
	if(flag==false)
	   return ++count;
      }
    return -1;
}

void* Fibonachi(void* parameter)		//Fibonacci Function for series
{

 fibonumb* temp=(fibonumb*) parameter;

  int* result=new int[temp->size];	//Creating resultan based on the number provided
	int num1=0,num2=1,final=0;

	
	result[0]=final;
		final=num1+num2;
	
	  result[1]=final;
	
	for(int i=2;final<temp->actual_number;i++)
	{		
		final=num1+num2;
		//cout<<" "<<final;
		result[i]=final;
		num1=num2;
		num2=final;
	}
	

  return result;

}


int main(int count, char** num_array)   // Main Function
{

  pthread_t thread_id[count-2];
  
  fibonumb fibo_arr[count-2];
  
  int fn=2;
  for(int k=0;k<count-2;k++)
  {    
     fibo_arr[k].actual_number=atoi(num_array[fn]);
    
     fn=fn+1;  
     fibo_arr[k].size=fibonacci_Count(fibo_arr[k].actual_number);
     
  }
  cout<<endl;
 for(int i=0; i<count-2;i++)
{
  if (pthread_create(&thread_id[i], NULL, &Fibonachi, &fibo_arr[i])==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }   
 }
 
 for(int i=0; i<count-2;i++)
  {
  cout<<"Thread No "<<i<<": ";
     int *ptr;
     pthread_join(thread_id[i], (void**) &ptr);
      
     for(int a=0; a< fibo_arr[i].size ;a++)
     {    
       cout<<*(ptr+a)<<" ";
      }
delete ptr;
  cout<<endl;
   }

  return 0;
}
