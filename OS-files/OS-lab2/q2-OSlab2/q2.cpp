#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(int arg,char** arr)
{
   int id1= fork();
   
     if (id1 == 0)
     {
        cout<<"Child 1 process\n";
        int sum=0;
        for(int i=1;i<arg;i++)
            sum+=atoi(arr[i]);
            cout<<" Sum is: "<<sum<<endl;
          int id2= fork();
   
		   if (id2 == 0)
		     {
			    cout<<"Child 2 process\n";
			      int sum=0;
     				  for(int i=1;i<arg;i++)
          			     sum+=atoi(arr[i]);
           			 cout<<"\n Average is: "<<sum/(arg-1)<<endl;
				int id3= fork();
			   
				     if (id3 == 0)
				     {
					cout<<"Child 3 process\n";
					  int max=0;
  					      for(int i=1;i<arg;i++)
  					      {
  					         if(max<atoi(arr[i]))
      						      max=atoi(arr[i]);
      					      }
           					 cout<<" Max num is: "<<max<<endl;
				     }
				     else if(id3 > 0)
				       {
				       wait(NULL);
				       cout<<"Parent 3 process\n";
				       }
				      else
					 cout<<" Error \n";
		    }
	     else if(id2 > 0)
	       {
	       wait(NULL);
	       cout<<"Parent 2 process\n";
	       }
	      else
		 cout<<" Error \n";
    }
	     
     else if(id1 > 0)
       {
       wait(NULL);
       cout<<"Parent 1 process\n";
       }
      else
         cout<<" Error \n";
}
