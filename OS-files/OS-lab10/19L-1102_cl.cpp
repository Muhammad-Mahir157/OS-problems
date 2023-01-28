#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include<fstream>
#include<cstring>
#include<unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
  char filename2[14]="/tmp/my_file2";		// Named pipe 2
 mkfifo(filename2, 0666);
 
 char filename[13]="/tmp/my_file";		// Opening Named pipe 1

 int fd=open(filename, O_RDONLY); 
 
 char buffer1[20];
 char buffer2[20];
 char result[10];
 char* str1=new char[500];
 char* str2=new char[500];
 
 int count1=read(fd,buffer1,9);		// Reading first file name
  buffer1[count1]='\0';
  
 int count2=read(fd,buffer2,sizeof(buffer2));		// Reading second file name
 buffer2[count2]='\0';
 
 close(fd);
 
 cout<<"The file1 Name sent by the server is: "<<buffer1<<endl;
 cout<<"The file2 Name sent by the server is: "<<buffer2<<endl;
 
 ifstream fin;
 fin.open(buffer1);			// Reading data from file 1
 
 if(fin.is_open())
 {
    fin.getline(str1,500,'-1');
 }
 else
  cout<<" can't open File 1"<<endl;
 fin.close();
 
 fin.open(buffer2);			// Reading data from file 2
 
 if(fin.is_open())
 {
    fin.getline(str2,500,'-1');
 }
 else
  cout<<" can't open File 2"<<endl;
 fin.close();
 
 
 cout<<" Str1: "<<str1;
 cout<<" Str2: "<<str2;
 
 
  int fd2=open(filename2,  O_WRONLY);
  
 // int i=str1.compare(str2);
 if( strcmp(str1,str2)== 0 )
  write(fd2,"yes",4);			// Sending message to server on the basis of comaprison of the text!
 else
   write(fd2,"no",3);
   
  close(fd2);
 
}



