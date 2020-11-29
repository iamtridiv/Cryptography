#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

	void decryptdatafile()
	{
		FILE *f1,*f2,*f3,*encdata,*decdata;
		f1=fopen("receiveddecryptedkeyfile1.txt","r");
		f2=fopen("receiveddecryptedkeyfile2.txt","r");
		f3=fopen("receiveddecryptedkeyfile3.txt","r");
		encdata=fopen("encrypted.txt","r");
		decdata=fopen("decrypted.txt","w");
		fclose(decdata);
		int k1,k2,k3;
		k1=getw(f1);
		fclose(f1);
		k2=getw(f2);
		fclose(f2);
		k3=getw(f3);
		fclose(f3);
		//k3=20;
		printf("\n---------------VALUE OF KEYS are %d , %d , %d---------\n",k1,k2,k3);
		decdata=fopen("decrypted.txt","a");
		

			char a;
	while((a=getc(encdata))!=EOF)
	{
	 
//	  b=encrypt(a,pub,e);//calling encrypt function..
//	  printf("%c",b); 
//	  putc(b,fw);//data placed in encoded file..

	 int data=(int)a;
		data=(data^k3);//printf("%d\n",data);

		data=~(data^k2);//printf("%d\n",data);

		data=(data^k1);//printf("%d\n",data);
	char b= (char) data;

	putc(b,decdata);

	}
	fclose(encdata);
	fclose(decdata);


	}



	int dkey(int k,int pub,int pri)
	{
	int g = k;
 	printf("THE VALUE OF G IS ==%d\n",g);
	int res=1;
	g = g % pub ;

	while(pri>0)
	{
	   if(pri & 1)
	      {
		 res=(res*g)%pub;
	      }
	   pri=pri/2;

           g=(g*g)%pub;
	}
	return res;
	}

void decryptkeyfile(int pub,int pri)
	{
		FILE *f1,*f2,*f3;
		int k1,k2,k3;
		f1=fopen("receivedencryptedkeyfile1.txt","r");
		f2=fopen("receivedencryptedkeyfile2.txt","r");
		f3=fopen("receivedencryptedkeyfile3.txt","r");
		k1=getw(f1);
		//k1= (int)x;
		fclose(f1);
//		printf("THE VALUE OF K1 is === %d\n",k1);
		k2=getw(f2);
	//	k2=(int)x;
		fclose(f2);
		k3=getw(f3);
	//	k3=(int)x;
		fclose(f3);
		int k11=dkey(k1,pub,pri);
		printf("k11==%d\n",k11);
		f1=fopen("finaldecryptedkeyfile1.txt","w");
		putw(k11,f1);
		fclose(f1);
		int k22=dkey(k2,pub,pri);
		printf("k22==%d\n",k22);
		f2=fopen("finaldecryptedkeyfile2.txt","w");
		putw(k22,f2);
		fclose(f2);
		int k33=dkey(k3,pub,pri);
		printf("k33==%d\n",k33);		
		f3=fopen("finaldecryptedkeyfile3.txt","w");
		putw(k33,f3);
		fclose(f3);				
	}



  void getoutput(int pub,int pri,int k1,int k2,int k3)
	{
		FILE *f1,*f2,*f3;
		f1=fopen("receivedencryptedkeyfile1.txt","w");
		f2=fopen("receivedencryptedkeyfile2.txt","w");
		f3=fopen("receivedencryptedkeyfile3.txt","w");
		
		putw(k1,f1);fclose(f1);
		putw(k2,f2);fclose(f2);
		putw(k3,f3);fclose(f3);
		decryptkeyfile(pub,pri);
		decryptdatafile();		
	}

 
  



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr;
     int n,opt=1;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
 
     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                               &opt, sizeof(opt)))
       {
        error("setsockopt");
       }


     portno = 5000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,2);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,1024);
     n = read(newsockfd,buffer,1024);

     if (n < 0) 
      error("ERROR reading from socket");
//-----------------------------------------------------------------
int p,q;
  p=13;				//FIRST PRIME NUMBER DECLARED..
  q=11;				//SECOND PRIME NUMBER DECLARED..

   int pub = p*q;      //THIS IS THE PUBLIC KEY WHICH IS KNOWN BY ALL..

   int nn=(p-1)*(q-1);  // NEEDED FOR EVALUATING PRIVATE KEY

   int e;		// E NEEDED FOR CALCULATING PRIVATE KEY..

  for( int i=2;i<nn;i++)
        {
          if((nn%i)!=0)
             {
               e=i;
                break;		// E FOUND... TERMINATE FROM LOOP..
             }

        }
   printf("E is=== %d \n",e);

   int k;

   int pr,pri,private;
   
   for(k=0;pr!=0;k++)
   {
     pr=(1+k*n)%e;		//CALCULATE pr SUCH THAT WHEN pr=0, TERNIMATE.
   }
  printf("k is == %d \n",--k);   

  private=(1+k*n)/e;		//PRIVATE KEY CALCULATED..WHICH IS KNOWN ONLY TO THE USER..
  
 printf("ENTER THE PRIVATE KEY \n");
  scanf("%d",&pri);


 //--------------------------------------------------------------------
FILE *fo;
fo=fopen("receivedencryptedfile.txt","w");
fclose(fo);
int i=0;
fo=fopen("receivedencryptedfile.txt","a");
while(buffer[i]!='\0')
{
char k= buffer[i];
i++;
putc(k,fo);
}
fclose(fo);
   n = write(newsockfd,"server has  succesfully received your encryptedmessage",54);
     if (n < 0) error("ERROR writing to socket");

    // bzero(buffer,1024);
    int buffer1[1024];
     n = read(newsockfd,buffer1,1024);
	
     if (n < 0)
      error("ERROR reading from socket");
    int k1,k2,k3;
	k1=buffer1[0];
	k2=buffer1[1];
	k3=buffer1[2];

	getoutput(pub,pri,k1,k2,k3);  
    
//--------------------------------------------------------------------
  /*  // printf("Here is the encrypted message: %s\n",buffer);
     printf("\nENTER THE PRIVATE KEY\n");
     int pri,i=0;
     scanf("%d",&pri);
     char dec[255];
     FILE *f;
     f=fopen("second.txt","a");
    
    while(buffer[i]!='\0')
    {
     char s = buffer[i];
     //dec[i]= calculate(pri,s);
     putc(s,f); 
     i++;
    }
    calculate(pri);
    

     printf("Here is the decrypted message: %s\n",dec);
  */   n = write(newsockfd,"server has  succesfully received your message",45);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
