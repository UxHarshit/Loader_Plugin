#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

 

#define MAX_MSG 100

#define LINE_ARRAY_SIZE (MAX_MSG+1)

 

using namespace std;

char buf[256] = "recived";


int main()

{

    struct sCli
    {
        int scrX,scrY;
    };
    
    struct gameInf
    {
        int playerCount = 0;
    };
  
  gameInf gminf;
  int listenSocket, connectSocket, i;
  unsigned short int listenPort;
  socklen_t clientAddressLength;
  struct sockaddr_in clientAddress, serverAddress;
  char line[LINE_ARRAY_SIZE];

  listenPort = 6969;
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (listenSocket < 0) {
    cerr << "cannot create listen socket";
    exit(1);
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(listenPort);

  sCli scli{};
 

  if (bind(listenSocket,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) {
    cerr << "cannot bind socket";
    exit(1);
  }

  listen(listenSocket, 5);

  while (1) {

    cout << "Waiting for TCP connection on port " << listenPort << " ...\n";

    clientAddressLength = sizeof(clientAddress);

    connectSocket = accept(listenSocket,(struct sockaddr *) &clientAddress,&clientAddressLength);

    if (connectSocket < 0) {

      cerr << "cannot accept connection ";

      exit(1);

    }
    cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);
    cout << ":" << ntohs(clientAddress.sin_port) << "\n";
    memset(line, 0x0, LINE_ARRAY_SIZE);

    while (recv(connectSocket,&scli,sizeof(scli),0) > 0) {

        printf("X : %d\n",scli.scrX);
        printf("Y : %d\n",scli.scrY);
        gminf.playerCount = 90;
        for (int i = 0; i < 10; i++)
        {
            send(connectSocket, &gminf, sizeof(gminf), 0);
            sleep(3);
        }
    }

  }

}