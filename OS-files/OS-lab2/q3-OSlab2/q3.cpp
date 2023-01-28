#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main()
{
   int id1= fork();
   
     if (id1 == 0)
     {
        cout<<"Child 1 process\n";
        int check1=execlp("mkdir", "mkdir", "./myFolder_1","./my_Folder2 ", NULL);
	    if (check1==-1)
		  {
		    cout<<"command not found"<<endl;
		  }
    }
	     
     else if(id1 > 0)
       {
       wait(NULL);
       cout<<"Execlp Parent 1 Called\n";
       int id2= fork();
   
		   if (id2 == 0)
		     {
			    cout<<"Child 2 process\n";
			  int check2=execlp("mkdir", "mkdir", "./myFolder_1/mySubFolder", NULL);
				    if (check2==-1)
				        cout<<"command not found"<<endl;
				
		    }
	     else if(id2 > 0)
	       {
	       wait(NULL);
	       cout<<"Execlp Parent 2 called\n";
	       int id3= fork();
			   
				     if (id3 == 0)
				     {
					cout<<"Child 3 process\n";
		                          int check3=execlp("/bin/ls", "ls","-S", NULL);
				        if (check3==-1)
				           cout<<"command not found"<<endl;
				     }
				     else if(id3 > 0)
				       {
				       wait(NULL);
				       cout<<"Execlp Parent 3 called\n";
				       }
				      else
					 cout<<" Error \n";
	       }
	      else
		 cout<<" Error \n";
       }
      else
         cout<<" Error \n";
}
