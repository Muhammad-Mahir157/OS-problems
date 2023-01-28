  #include <unistd.h>
  #include <string.h>
  #include <sys/types.h>
  #include <fcntl.h>
  #include <sys/wait.h>
  #include<sys/stat.h>
  #include<iostream>
  using namespace std;

  int main()
  {
      int fd1[2];
      int fd2[2];
      pipe(fd1);
      pipe(fd2);
      
      int cpid=fork();
   if(cpid==0)
      {
     
      //child is write process
      
    close(fd2[0]);			//close the unused end of the pipe P2(Read End)
    close(fd1[1]);			// close the unused end of the pipe P1(Write End)

						//temp variable to modify data    
        char* message=new char[1770];
        int m_count=read(fd1[0],message,1770);		//making copy ofthe buffer                    
             message[m_count]='\0';
             
            	 close(fd1[0]);	// close the already used end of the pipe P1(Read End)   
            	        
           
    /* for (int i=0;message[i]!='\0';i++)
		{			
			if (message[i]>=33 && message [i]<=47 ||  message[i]==64 || message[i]==126)
			{
				for (int j=i;message[j+1]!='\0';j++)
				{
				  
					message[j]=message[j+1];
					
			        }
				i--;
			}
		}
		for(int i=0;message[i]!='\0';i++)
		{
		   if(message[i]>='a' && message[i]<='z')
                       message[i]=message[i]-32;
		}*/
		 char* buffer=new char{m_count+1]; 
                  int  buf_count=0;    
          for(int i=0;message[i]!='\0';i++)
       {
          if(!(message[i]>=47 && message[i]<58) )
            {
               if(message[i]>64 && message[i]<91)
               {
                 buffer[buf_count]=message[i]+32;
                   buf_count++;
                }
                else if(message[i]>96 && message[i]<123)
                 {
                 buffer[buf_count]=message[i]-32;
                   buf_count++;
                 }
                 else
                  {
                 buffer[buf_count]=message[i];
                   buf_count++;
                  }                  
             }       
       }		
      
       
         
        int w_count= write(fd2[1],buffer, strlen(buffer)+1); 
         	 									//writing modified data through pipe2
        			 									                                      	
        close(fd2[1]);    	// close the already used end of the pipe P2(Write End)
        _exit(0);
        
      }
      else if(cpid>0)
      {
//parent is read process
        
           close(fd2[1]);                  // close the unused end of the pipe P2(Write End)
	   close(fd1[0]);	     	    // close the unused end of the pipe P1(Read End)
          
           int f_read=open("file.txt",O_RDONLY,0);
           
         char* buffer =new char[1770];
         int r1_count=read(f_read,buffer,1770);          
                buffer[r1_count]='\0';
                
         int w1count=write(fd1[1],buffer,strlen(buffer)+1) ;
            close(fd1[1]);		// close the already used end of the pipe P1(Read End)
         
      wait(NULL);
         
 //reading converted data using pipe 2
   		char* temp =new char[1770];
           int r2_count=read(fd2[0],temp,1770);
               temp[r2_count]='\0';
		
            close(fd2[0]);    	// close the already used end of the pipe P2(Read End)
            
         int f_write=open("output.txt",O_WRONLY | O_CREAT, S_IRWXU);        
           int w2_count= write(f_write,temp, strlen(temp)); 
              
                
     _exit(0);
      
      }
     
  
   return 0;
      
  }

