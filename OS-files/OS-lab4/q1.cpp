#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

 int restore_descriptor=dup(0);
 int read=open("input.txt", O_RDONLY, 0);
 
 
 dup2(read ,0);
 close(read);
 
  int sum=0;
  int n;
 
  while(!cin.eof())
  {
   n=0;
    cin>>n;
    sum+=n;
  }
  
  dup2(restore_descriptor, 0);
  close(restore_descriptor);
  
   
  int restore=dup(1);
  int write=open("write_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
  
  dup2(write, 1);
  close(write);
  
  cout<<"The result sum of the numbers is "<<sum<<endl;
  
  dup2(restore, 1);
  close(restore);
  
  
  char f;
  cin>>f;
  cout<<"Program is going to be terminated just press any key "<<endl;
  
  
}

