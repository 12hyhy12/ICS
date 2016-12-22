//1500012703 ::13368
//Zhang Yuhao
#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

void getHost(char*uri,char*host,char*port,char*path)
//parse the uri and get the host
{
	int st=0,cnt=0,l=strlen(uri);
	if (uri[0]=='h') st=7;
	for(;st<l&&uri[st]!='/'&&uri[st]!=':';st++) host[cnt++]=uri[st];
	host[cnt]='\0';
	port[0]='8';
    port[1]='0';
    port[2]='\0';
	if (uri[st]==':')
    {
        int i=0;
		for(st++;uri[st]>='0'&&uri[st]<='9';st++) port[i++]=uri[st];
        port[i]='\0';
    }
    if (st>=l)
    {
        path[0]='\\';
        path[1]='\0';
    }
    else 
    {
        int i=0;
        for(;st<l;st++) path[i++]=uri[st];
        path[i]='\0';
    }
}

void doit(int fd) 
//get the server host name and port, then send them a request
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char portNum[MAXLINE], path[MAXLINE], host[MAXLINE];
    rio_t rio,ser_rio;
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))  
        return;
    //printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcmp(version,"HTTP/1.1")==0)
    {
        fprintf(stderr,"Version: %s change to HTTP/1.0\n",version);
        version[strlen(version)-1]='0';
    }
    if (strcmp(method,"GET")) 
    {
        fprintf(stderr,"Method: %s unhandled\n",method);
        return;
    }
    getHost(uri,host,portNum,path);
    
    int serverfd=open_clientfd(host,portNum);
    fprintf(stderr,"%s %s %s\n",host,portNum,path);
    if (serverfd<0) fprintf(stderr,"Open_clientfd for server error!\n");
    else
    {
        //printf("Connected!\n");
        Rio_readinitb(&ser_rio, serverfd);
        //printf("%d\n",MAXLINE);
        char buffer[MAXLINE*10];
        sprintf(buffer,
            "%s %s %s\r\nHost: %s \r\n%s"
            "Connection: close\r\nProxy-Connection: close\r\n\r\n",
            method,path,version,host,user_agent_hdr);
        //printf("%s\n",buffer);
        Rio_writen(serverfd,buffer,MAXLINE);
        Close(serverfd);
    }
}

int main(int argc,char** argv)
{
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	int listenfd,connfd;
	char hostname[MAXLINE], port[MAXLINE];
    
    if (argc!=2)
    {
    	fprintf(stderr,"usage: %s <port>\n",argv[0]);
    	return 0;
    }
    listenfd=Open_listenfd(argv[1]);
    while (1)
    {
    	clientlen=sizeof(clientaddr);
    	connfd=Accept(listenfd,(SA*)&clientaddr,&clientlen);
    	Getnameinfo((SA*)&clientaddr,clientlen,hostname,MAXLINE,port,MAXLINE,0);
    	fprintf(stderr,"Accepted connection from (%s,%s)\n",hostname,port);
    	doit(connfd);
    	Close(connfd);
    }
    
    return 0;
}
