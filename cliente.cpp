#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

class cliente
{
public:

	
		
int listenFd, portNo;
    static bool  loop;
    struct sockaddr_in svrAdd;
    struct hostent *server;
	int checker;
	
    void crearSocket(int argc, char* argv[]){
    	 if(argc < 3)
    {
        cerr<<"Escriba asi : ./cliente <host name> <port>"<<endl;
     
    }
    
    portNo = atoi(argv[2]);
    
    if((portNo > 65535) || (portNo < 2000))
    {
        cerr<<"ingrese un numero de puerto entre 2000 - 65535"<<endl;
     
    }       
    
    //create cliente skt
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenFd < 0)
    {
        cerr << "no se puede abrir el socket" << endl;
        
    }
    
    server = gethostbyname(argv[1]);
    
    if(server == NULL)
    {
        cerr << "el host no existe" << endl;
       
    } 

    }


    void conectar(){

     bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    
    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
    
    svrAdd.sin_port = htons(portNo);
    
    int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    
    if (checker < 0)
    {
        cerr << "no se puede conectar!" << endl;
       
    }

    }

void enviarmensaje(){

	for(;;)
    {
        char s[300];
        
        //cin.clear();
        //cin.ignore(256, '\n');
        cout << "Enter stuff: ";
        bzero(s, 301);
        cin.getline(s, 300);
        
        write(listenFd, s, strlen(s));
	recibirmensaje();
}
}

	void recibirmensaje (){
char answer[300];
bzero(answer,301);
        cout << checker << " esperando a leer" <<endl;
        read(listenFd,answer,300);
        string answers(answer);
        cout << "el servidor dice " <<answers << endl;
        if (answers=="exit"){
            cout   <<"closing"<<endl;
            close(listenFd);
}
}
};

 

int main(int argc, char* argv[])
{
	/* code */

	cliente cliente;
	cliente.crearSocket(argc,argv);
	cliente.conectar();
	while (true){
	cliente.enviarmensaje();
cliente.recibirmensaje();
}
	return 0;
}
