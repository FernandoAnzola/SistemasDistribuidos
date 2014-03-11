#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
using namespace std;



class servidor
{
public:
	static int connFd;
	 int pId, portNo, listenFd;
    socklen_t len; //store size of the address
   static bool loop ;
    struct sockaddr_in svrAdd, clntAdd;
    
    pthread_t threadA;
	

    void crearsSocket(int argc, char* argv[]){

if (argc < 2)
    {
        cerr << "Error de sintaxis : ./server <port>" << endl;
        
    }
    
    portNo = atoi(argv[1]);
    
    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Ingrese un numero de puerto entre 2000 - 65535" << endl;
       
    }
    
    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenFd < 0)
    {
        cerr << "no se puede abrir socket" << endl;
       
    }
    
    }


void bindSock(){

bzero((char*) &svrAdd, sizeof(svrAdd));
    
    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);
    
    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        
    }
}



    void listenSock(){
listen(listenFd, 5);
    
    len = sizeof(clntAdd);
    
    

    while (true)
    {
        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
           
        }
        else
        {
            cout << "Connection successful" << endl;
        }
        
        pthread_create(&threadA, NULL, leersocket, NULL); 
       pthread_join(threadA, NULL);
     
    }
    
 
    
    }
    
void leersocket ()
{
    
    //cout << "Thread No: " << pthread_self() << endl;
    char test[300];
    bzero(test, 301);
    bool loop = false;
    
    while(!loop)
      
        bzero(test, 301);
        
        
        read(connFd, test, 300);
        
        string tester (test);
        cout << "cliente dice"<<tester << endl;
             
        
        if(tester == "exit"){
     cout << "\nClosing thread and conn" << endl;
    close(connFd);
}
}

void enviarmensaje(){
char s[300];
	cout << "Enter answer: ";
        bzero(s, 301);
        cin.getline(s, 300);   
       // cout <<"escribiendole a " << connFd <<s<<endl; 
        write(connFd,s,strlen(s));

}




};

int main(int argc, char* argv[])
{
	/* code */
servidor servidor;
servidor.crearsSocket(argc,argv);
servidor.bindSock();
servidor.listenSock();
while (true){
	
	servidor.leersocket();
	servidor.enviarmensaje();
}


	return 0;
}
