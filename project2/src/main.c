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

  // to check for proper req
  char *precmd = "GET";
  char *postcmd = "HTTP/1.1";

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
    char *cmd;
    char command_result[1000];
    char response_header[1000];

    // check for 404
    if ((strstr(buff, precmd) == NULL) || (strstr(buff, postcmd) == NULL))
    {
      strcpy(response_header, not_found_response_header);
      strcpy(command_result, "Invalid request, only GET is allowed.");
    }
    // send 200 OK
    else
    {
      cmd = strtok(buff + 4, " ");
      printf("cmd: %s\n", cmd);
      // decode cmd incase hex vals are present
      char *decoded_cmd = (char *)malloc(strlen(cmd) * sizeof(char));
      urldecode(decoded_cmd, cmd);

      // check for invalid command
      if (strstr(decoded_cmd, "/exec/") == NULL)
      {
        strcpy(response_header, not_found_response_header);
        strcpy(command_result, "Invalid command");
      }
      else
      {
        printf("cmd to exec: %s\n", decoded_cmd);

        strcpy(response_header, ok_response_header);
      }
    }

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

/* handle ctrl + c */
void SIGINT_handler(int signal_num)
{
  // release port
  close(rsock);
  shutdown(rsock, 2);
  exit(0);
}

/* decode url */
void urldecode(char *dst, const char *src)
{
  char a, b;
  while (*src)
  {
    if ((*src == '%') &&
        ((a = src[1]) && (b = src[2])) &&
        (isxdigit(a) && isxdigit(b)))
    {
      if (a >= 'a')
        a -= 'a' - 'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a' - 'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';
      *dst++ = 16 * a + b;
      src += 3;
    }
    else if (*src == '+')
    {
      *dst++ = ' ';
      src++;
    }
    else
    {
      *dst++ = *src++;
    }
  }
  *dst++ = '\0';
}