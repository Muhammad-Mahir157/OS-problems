#include<iostream>
#include"convertText.h"
#include<fstream>
using namespace std;

void processtext(char* inp,char* out)
{
	ifstream mydata(inp);
	  	 char* buffer=new char[200];
     if(mydata.is_open())
     {
		     mydata.getline(buffer, 200, '-1');	    // here -1 indicates eof
     }
      string converted_data="";
      for(int i=0;buffer[i]!='\0';i++)
      {
         if(buffer[i]>='a' && buffer[i]<='z' ||buffer[i]>='A' && buffer[i]<='Z')
         {
            if(buffer[i]>='a' && buffer[i]<='z')
              {
                 buffer[i]=buffer[i]-32;
               }
            converted_data=converted_data+buffer[i];
         }
      }
      
      ofstream write_data(out);
        if(write_data.is_open())
        {
           write_data<<converted_data<<endl;
        }
		delete[]buffer;
}
