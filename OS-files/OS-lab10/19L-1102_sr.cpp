#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<cstring>
#include<unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
  char result[10];
   
 char filename[13]="/tmp/my_file";
 mkfifo(filename, 0666);

 int fd=open(filename,  O_WRONLY);
 
  
  write(fd,"file1.txtfile2.txt",19);			
  close(fd);
  
  char filename2[14]="/tmp/my_file2";		

 int fd2=open(filename2, O_RDONLY); 
 
  int count1=read(fd2,result,sizeof(result));		// Reading message sent by client
  result[count1]='\0';

   if(  strcmp(result,"yes") == 0)			// Result printing if same text else if not same text
      cout<<" The text in both files is same "<<endl;
    else
      cout<<" The text in both files is not same "<<endl;
}



