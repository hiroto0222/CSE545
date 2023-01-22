#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int port = 0;
int rsock, wsock;

int main(int argc, char *argv[])
{
  // check if port number was passed on execution
  if (argc < 2)
  {
    fprintf(stderr, "Missing port number on ./normal_web_server execution\n");
    exit(1);
  }

  port = atoi(argv[1]);

  // init socket
  rsock = socket(AF_INET, SOCK_STREAM, 0); // IPv4 with bytestream
  if (rsock < 0)
  {
    fprintf(stderr, "Error. Cannot make socket\n");
    exit(1);
  }

  // create server address
  struct sockaddr_in addr;
  int len;
  int bind_status;
  int listen_status;

  // socket setting
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  // bind socket
  bind_status = bind(rsock, (struct sockaddr *)&addr, sizeof(addr));
  if (bind_status < 0)
  {
    fprintf(stderr, "Error. Cannot bind socket\n");
    exit(1);
  }

  // listen to socket
  listen_status = listen(rsock, 5);
  if (listen_status < 0)
  {
    fprintf(stderr, "Error. Failed to listen to port\n");
    exit(1);
  }

  // send message
  write(wsock, "HTTP1.1 200 OK", 14);

  // close tcp connection
  close(wsock);
  close(rsock);

  return 0;
}