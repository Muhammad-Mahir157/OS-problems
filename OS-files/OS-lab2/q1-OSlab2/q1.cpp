#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

int main(int arg, char** a)
{
  int h=atoi(a[1]);
	cout<<"Your height is:"<<h<<endl;
  int id= fork();
    if(id==0)
     {
	for(int a=0; a<=h; a++)
	{
		for(int b=a; b<h; b++)
		{
			cout<<" ";
		}

		for(int c=0; c<=a; c++)
		  {
			  cout<<"* ";
		  }
		  cout<<endl;
	}
   }
   else if(id >0)
   {
     wait(NULL);

	for(int a=h-1; a>=0; a--)
	{
		for(int b=a; b<h; b++)
		{
			cout<<" ";
		}

		for(int c=0; c<=a; c++)
		  {
			  cout<<"* ";
		  }
		  cout<<endl;
	}
  }
   else
    cout<<"\n Error "<<endl;
   return 0;
}
