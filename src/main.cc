#include<iostream>
#include<string>
#include"httpServer.h"
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdlib.h>
#include<fcntl.h>




#define BUFFSIZE 102400

void header(FILE * fp, char * content_type){
		std::cout<<"read a head"<<std::endl;
		fprintf(fp,"HTTP/1.0 200 OK\r\n");
		if(content_type){
			fprintf(fp,"Content-type:&s\r\n",content_type);
		}
		fprintf(fp,"hello world!");
}

void process_rq(char * rq,int fd){

	FILE* fp = fdopen(fd,"w");
	header(fp,"text/html");
	fflush(fp);
	fclose(fp);
}

int main(){

	std::cout<<"httpserver"<<std::endl;

	char recvbuff[BUFFSIZE];
	FILE *fpin;
	int server_socker = socket(AF_INET,SOCK_STREAM,0);
	
	int port = 80;
	std::string ip = "0.0.0.0";
	struct sockaddr_in address = { 0 };
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &(address.sin_addr));
    address.sin_port = htons(port);

	if(bind(server_socker,(struct sockaddr*) &address,sizeof(address))<0){
		close(server_socker);
		std::cout<<"bind error!"<<std::endl;
	}

	if(listen(server_socker,20480)<0){
		close(server_socker);
		std::cout<<"listen error!"<<std::endl;
	}

	while(1){
		struct sockaddr_in addr;
        int size = 0;
        int client_socket = 0;
        size = sizeof(struct sockaddr_in);
        client_socket = accept(server_socker, (struct sockaddr *) &addr, (socklen_t *) &size);
		if(client_socket <= 0){
			std::cout<<"accept error"<<std::endl;
		}
		fpin = fdopen(client_socket,"w+");
		fgets(recvbuff,BUFFSIZE,fpin);
		printf("request = %s",recvbuff);
		header(fpin,"text/html");
		fflush(fpin);
	//	fclose(fpin);

		//process_rq(recvbuff,client_socket);
	}

	return 0;
}
