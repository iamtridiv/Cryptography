#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <math.h>

//##############################################################




	void encryptkey(int pub,int e)
	{
		int i;
		
		int result=0;
		FILE *f1,*f2,*f3;
		int k1,k2,k3;
		f1=fopen("keyfile1.txt","r");
		f2=fopen("keyfile2.txt","r");
		f3=fopen("keyfile3.txt","r");

		
		k1=getw(f1);
		//k1=(int)x;
		/*while((k1=getc(f1))!=EOF)
		{
		//long long int result=0;
		i++;
		printf("k1 is ==%d\n",k1);
		result = result * (pow(10,i)) + k1; 
		}*/
		printf("key1 is ==%d\n",k1);
		result=k1;
		printf("result is ==%d\n",result);
		int power = 1;
		for(i=1;i<=e;i++) //pow(result,e)
         	{

               	power=power*result;

          	}
		power= power % pub;
		fclose(f1);
		f1=fopen("encryptedkeyfile1.txt","w");
		printf("power ==%d\n",power);
		putw(power,f1);
		fclose(f1);
		//fopen("encryptedkeyfile1.txt","r");
		//char x=getc(f1);
		//printf("X is %c\n=",x);
		//int xx = (int)x;
		//printf("xx is =%d\n",xx);
		//fclose(f1);
		i=0;
		result=0;
		/*while((k2=getc(f2))!=EOF)
		{
		//long long int result=0;
		i++;
		result = result * (pow(10,i)) + k2; 
		}*/
		k2=getw(f2);
		//k2=(int)x;
		printf("k2 is ==%d\n",k2);
		result=k2;
		printf("result is ==%d\n",result);
		power = 1;
		for(i=1;i<=e;i++) //pow(result,e)
         	{

               	power=power*result;

          	}
		power= power % pub;
		fclose(f2);
		f2=fopen("encryptedkeyfile2.txt","w");
		putw(power,f2);
		fclose(f2);

		i=0;
		result=0;
		/*while((k3=getc(f3))!=EOF)
		{
		//long long int result=0;
		i++;
		result = result * (pow(10,i)) + k3; 
		}*/
		k3=getw(f3);
		//k3=(int)x;
		printf("k3 is ==%d\n",k3);
		result=k3;
		printf("result is ==%d\n",result);
		power = 1;
		for(i=1;i<=e;i++) //pow(result,e)
         	{

               	power=power*result;

          	}
		power= power % pub;
		fclose(f3);
		f3=fopen("encryptedkeyfile3.txt","w");
		putw(power,f3);
		fclose(f3);

	}



	void encrypt(int key1,int key2,int key3)
	{
	FILE *fr,*fw;
	fr=fopen("newfile.txt","r");
	fw=fopen("encrypted.txt","w");
	fclose(fw);
	fw=fopen("encrypted.txt","a");
	char a;
	while((a=getc(fr))!=EOF)
	{
	 
//	  b=encrypt(a,pub,e);//calling encrypt function..
//	  printf("%c",b); 
//	  putc(b,fw);//data placed in encoded file..

	 int data=(int)a;
		data=(data^key1);//printf("%d\n",data);

		data=~(data^key2);//printf("%d\n",data);

		data=(data^key3);//printf("%d\n",data);
	char b= (char) data;

	putc(b,fw);

	}
	fclose(fr);
	fclose(fw);
	}




		void getinput(int pub,int e)
	{
		
		int key1,key2,key3;
		printf("Enter the first key  ==== ");
		scanf("%d",&key1);
		printf("Enter the second key ==== ");
		scanf("%d",&key2);
		printf("Enter the third key  ==== ");
		scanf("%d",&key3);
//		printf("Enter the first key to be used==== ");
		FILE *f1,*f2,*f3;
		f1=fopen("keyfile1.txt","w");
		putw(key1,f1);
		f2=fopen("keyfile2.txt","w");
		putw(key2,f2);
		f3=fopen("keyfile3.txt","w");
		putw(key3,f3);
		printf("uutiutiti\n");		
		fclose(f1);fclose(f2);fclose(f3);
		printf("etya data encryptr kaaam tu korim\n");
		encrypt(key1,key2,key3);
		printf("etya encrypt keyr kaam tu korim\n");
		encryptkey(pub,e);
		printf("get inputor kaam hoi gol\n");

	}

int get1()
{

FILE *fo= fopen("encryptedkeyfile1.txt","r");
int k = getw(fo);
fclose(fo);
return k;

}

int get2()
{

FILE *fo= fopen("encryptedkeyfile2.txt","r");
int k = getw(fo);
fclose(fo);
return k;

}

int get3()
{

FILE *fo= fopen("encryptedkeyfile3.txt","r");
int k = getw(fo);
fclose(fo);
return k;

}



//##############################################################


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];
//    int buffer1[1024],store1[1024];
    char store[1024];
    portno = 5000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) 
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    error("ERROR connecting\n");
    printf("Please enter the file: \n");
    bzero(buffer,1024);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

   int pr,private;
   
   for(k=0;pr!=0;k++)
   {
     pr=(1+k*nn)%e;		//CALCULATE pr SUCH THAT WHEN pr=0, TERNIMATE.
   }
  printf("k is == %d \n",--k);   

  private=(1+k*nn)/e;		//PRIVATE KEY CALCULATED..WHICH IS KNOWN ONLY TO THE USER..
  


    
 // getinput(pub,e);              // CALLING THE FUNCTION NAMED getinput()..AND SENDING "public key" and "e" as parameters

 // printf("THE PRIVATE KEY IS= %d...\n",private);   //

 // int pri;
  //printf("ENTER THE PRIVATE KEY\n");
  //scanf("%d",&pri);
  //getoutput(pub,pri);               // 





	 getinput(pub,e);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++     
    FILE *fo,*fk1,*fk2,*fk3;
    fo=fopen("encryptedfile.txt","r");
 //   fk1=fopen("encryptedkeyfile1.txt","r");
 //   fk2=fopen("encryptedkeyfile2.txt","r");
 //   fk3=fopen("encryptedkeyfile3.txt","r");

    fgets(buffer,1024,fo);
	printf("encrupted file tu bhoralu bufferot\n");
    	int k1=get1();
	int k2=get2();
	int k3=get3();

	int buffer1[1024];
	buffer1[0]=k1;
	buffer1[1]=k2;
	buffer1[2]=k3;
printf("bhorua kaam hoi gl\n");
//send
    int i=0;
    while(buffer[i]!='\0')
    {
     char k = buffer[i];
     store[i]=k;
     i++;
    }
   

    n = write(sockfd,store,strlen(store));
    if (n < 0) 
         error("ERROR writing to socket");
	
    bzero(store,1024);
	n=read(sockfd,store,1024);
	printf("%s\n",store);
	n = write(sockfd,buffer1,strlen(buffer1));
 if (n < 0)
         error("ERROR writing to socket");
    bzero(store,1024);

    n = read(sockfd,store,1024);
    if (n < 0) 
    error("ERROR reading from socket");
    printf("%s\n",store);


//int l=getw(fk2);
//-------------------------------------

/*  	fk1=fopen("encryptedkeyfile.1","r");
	 bzero(buffer,1024);
	 bzero(store,1024);
	fge:ts(buffer,1024,fk1);
	i=0;
    while(buffer[i]!='\0')
    {
     int k = (int)buffer[i];
     store1[i]=k;
     i++;
    }

 n = write(sockfd,store1,strlen(store1));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(store,1024);
    n = read(sockfd,store,1024);
    if (n < 0) 
    error("ERROR reading from socket");
       printf("%s\n",store);
*/
//----------------------------------------------
/*

   	fk2=fopen("encryptedkeyfile.2","r");
	 bzero(buffer1,1024);
	 bzero(store1,1024);
	buffer1[0]=fgetw(fk2);
	i=0;
    while(buffer1[i]!='\0')
    {
      k = buffer1[i];
     store1[i]=k;
     i++;
    }

 n = write(sockfd,store1,strlen(store1));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(store1,1024);
    n = read(sockfd,store1,1024);
    if (n < 0) 
    error("ERROR reading from socket");
       printf("%s\n",store1);

//----------------------------------


   	fk3=fopen("encryptedkeyfile.3","r");
	 bzero(buffer1,1024);
	 bzero(store1,1024);
	buffer1[0]=fgetw(fk3);
	i=0;
    while(buffer1[i]!='\0')
    {
      k = buffer1[i];
     store1[i]=k;
     i++;
    }

 n = write(sockfd,store1,strlen(store1));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(store1,1024);
    n = read(sockfd,store,1024);
    if (n < 0) 
    error("ERROR reading from socket");
       printf("%s\n",store);



//---------------------------------
 */   close(sockfd);
    return 0;
}
