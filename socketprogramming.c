//socket programming(client.c)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];
    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
  
  
    int num1 ;
    int num2 ;
    float ans;
    int choice;
    /* Remove if doesnt work*/ 
    
    printf("\n\nWelcome To TCP/IP Calculator\n\n");
    R:bzero(buffer,256);						
    n = read(sockfd,buffer,255);			//Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server - %s",buffer);
    scanf("%d" , &choice);				//Enter choice
    write(sockfd, &choice, sizeof(int));     		//Send choice to Server

	if (choice == 5)
	goto Q;

	//if(choice != 5)
    	//goto S;

   // read(sockfd , &ans , sizeof(int));		       //Read Answer from Server
    //printf("Server - The answer is : %d\n" , ans);  //Get Answer from server    

	
    //S:
    bzero(buffer,256);						
    n = read(sockfd,buffer,255);			//Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("\nServer - %s",buffer);
    scanf("%d" , &num1);				//Enter No 1
    write(sockfd, &num1, sizeof(int));     		//Send No 1 to Server
	
	
	
    bzero(buffer,256);						
    n = read(sockfd,buffer,255);			//Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("\nServer - %s",buffer);
    scanf("%d" , &num2);				//Enter No 2
    write(sockfd, &num2, sizeof(int));     		//Send No 2 to Server
	
	
   /* 	
    bzero(buffer,256);						
    n = read(sockfd,buffer,255);			//Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server - %s",buffer);
    scanf("%d" , &choice);				//Enter choice
    write(sockfd, &choice, sizeof(int));     		//Send choice to Server

	if (choice == 5)
	goto Q;

	 if(choice != 5)
    	goto S;
*/

    read(sockfd , &ans , sizeof(float));	       //Read Answer from Server
    printf("\nServer - \nThe answer is : %.2f\n\n\n" , ans);	//Get Answer from server
    printf("\nRerunning calculator...\n\n");
    goto R;

   
Q:  printf("\n\nYou chose to exit, Thank You so much.\n\n");
     	
       
   
    
    close(sockfd);
    return 0;
}

//server.c



Skip to content
Using Gmail with screen readers
arko 
Meet
Start a meeting
Join a meeting
11 of 14
Fwd: Project
Inbox
x

arko pal <arko.pal2000@gmail.com>
Attachments
Apr 1, 2020, 6:24 PM
to me

To run this, you need to download Ubuntu first and then you need to download a virtual machine. Go to YouTube and and see how to run Ubuntu on the virtual machine. Then enjoy

2 Attachments
Thanks, I'll check it out.What do you think?Enjoy!

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

//argc=no of connections it accepts
//arg

int main(int argc, char *argv[])
{						
	if(argc < 2)
	{
		fprintf(stderr,"\nPort number not provided.Program terminated");
	}

	int sockfd,newsockfd,portno,n;
	char buffer[255];
	
	struct sockaddr_in serv_addr,cli_addr; //sockaddr gives internet addr
	socklen_t clilen;   //socklen_t is datatype of 4 bytes in socket.h

	sockfd=socket(AF_INET,SOCK_STREAM,6);  //creates socket
	if(sockfd < 0)
	{
		error("\nError genarting the socket. ");	
	}

	bzero((char *) &serv_addr, sizeof(serv_addr)); 
	//clears all the data whatever it refers to
	portno=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		error("\nBinding failed.");
	
	listen(sockfd,5);  //5 denotes number of users
	clilen=sizeof(cli_addr);
	
	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr, &clilen);
	
	if(newsockfd<0)
		error("\nError on accepting.");
	
	int num1,num2,choice;
	float ans;

	R:n=write(newsockfd,"\nMenu :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n\nEnter Choice : ",strlen("\nMenu :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n\nEnter Choice : "));
	if(n<0)
		error("\nError writing to socket");
	read(newsockfd, &choice, sizeof(int));
	printf("\nClient - Choice is : %d\n",choice);

	//if(choice!=5)
	//	goto S;

	if(choice==5)
		goto Q;


	//S:
	n=write(newsockfd,"\nEnter Number 1 : ",strlen("\nEnter Number 1 : "));
	if(n<0)
		error("\nError writing to socket");
	read(newsockfd, &num1, sizeof(int));
	printf("\nClient - Number 1 is : %d",num1);
	
	

	n=write(newsockfd,"\nEnter Number 2 : ",strlen("\nEnter Number 2 : "));
	if(n<0)
		error("\nError writing to socket");
	read(newsockfd, &num2, sizeof(int));
	printf("\nClient - Number 2 is : %d\n",num2);

	/*
	n=write(newsockfd,"\nEnter Choice :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit ",strlen("\nEnter Choice :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit "));
	if(n<0)
		error("\nError writing to socket");
	read(newsockfd, &choice, sizeof(int));
	printf("\nClient - Choice is : %d",choice);
	*/
	
	switch(choice)
	{
		case 1:
			ans=num1+num2;
			break;
		case 2:
			ans=num1-num2;
			break;
		case 3:
			ans=num1*num2;
			break;
		case 4:
			ans=num1/num2;
			break;
		case 5:
			goto Q;
			break;
	}
	
	write(newsockfd,&ans,sizeof(float));
	printf("\n\nRerunning calculator...\n\n");	
	goto R;
	
	
	Q:close(newsockfd);  //closes newsockfd
	close(sockfd);  //closes sockfd
	return 0;
}
 