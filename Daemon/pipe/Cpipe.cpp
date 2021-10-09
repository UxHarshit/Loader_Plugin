#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring> 
#define MAX_LINE 100

#define LINE_ARRAY_SIZE (MAX_LINE+1)

using namespace std;

struct screen
{
  int x,y;
};
struct gameInf
    {
        int playerCount = 0;
    };

int main()
{
  
  screen srcP;
  gameInf gminf;
  int socketDescriptor;
  unsigned short int serverPort;
  struct sockaddr_in serverAddress;
  struct hostent *hostInfo;
  char buf[LINE_ARRAY_SIZE], c;
  hostInfo = gethostbyname("192.168.1.2");
  serverPort = 6969;
  if (hostInfo == NULL) {
    cout << "problem interpreting host: " << buf << "\n";
    exit(1);
  }
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    cerr << "cannot create socket\n";
    exit(1);
  }
  serverAddress.sin_family = hostInfo->h_addrtype;
  memcpy((char *) &serverAddress.sin_addr.s_addr,hostInfo->h_addr_list[0], hostInfo->h_length);
  serverAddress.sin_port = htons(serverPort);
  if (connect(socketDescriptor,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) {
    cerr << "cannot connect\n";
    exit(1);
  }

  srcP.x = 1080;
  srcP.y = 2130;
  send(socketDescriptor, &srcP, sizeof(srcP), 0);

  while (strcmp(buf, ".")) {

    
    memset(buf, 0x0, LINE_ARRAY_SIZE);
    if (recv(socketDescriptor, &gminf, sizeof(gminf), 0) < 0) {

      cerr << "didn't get response from server?";

      close(socketDescriptor);

      exit(1);

    }
    printf("player count : %d\n",gminf.playerCount);
    
  }

 

  close(socketDescriptor);

  return 0;

}