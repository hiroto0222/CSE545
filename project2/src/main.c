#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int port = 0;
int rsock, wsock;

void client_accept(struct sockaddr_in addr);
void SIGINT_handler(int signal_num);

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

  // handle ctrl + c
  signal(SIGINT, SIGINT_handler);

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

  // accept incoming connections
  client_accept(addr);

  return 0;
}

void client_accept(struct sockaddr_in addr)
{
  char *ok_response_header = "HTTP/1.1 200 OK\n"
                             "Content-Type: text/html\n"
                             "Accept-Ranges: bytes\n"
                             "Connection: close\n"
                             "\n";
  char *not_found_response_header = "HTTP/1.1 404 NOTFOUND\n"
                                    "Content-Type: text/html\n"
                                    "Accept-Ranges: bytes\n"
                                    "Connection: close\n"
                                    "\n";
  char *get_request = "GET";

  // accept incoming connections
  while (1)
  {
    int len_addr = sizeof(addr);
    wsock = accept(rsock, (struct sockaddr *)&addr, &len_addr);
    if (wsock < 0)
    {
      fprintf(stderr, "Error. Client connection failed\n");
      continue;
    }

    char buff[1000];
    char url[1000];

    read(wsock, buff, 1000);
    printf("%s\n", buff);

    char *response = NULL;
    char response_header[1000];
    strcpy(response_header, ok_response_header);

    response = malloc(strlen(response_header) + 10);
    strcpy(response, response_header);

    send(wsock, response, strlen(response), 0);
    close(wsock);
    printf("Message sent: \n%s\n", response);

    // clear buffers
    memset(buff, 0, sizeof(buff));
    memset(url, 0, sizeof(url));
    memset(response, 0, sizeof(response));
    memset(response_header, 0, sizeof(response_header));
  }
}

void SIGINT_handler(int signal_num)
{
  // release port
  close(rsock);
  shutdown(rsock, 2);
  exit(0);
}