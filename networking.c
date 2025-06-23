#include "networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char *server_address)
{

  // getaddrinfo
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  getaddrinfo(server_address, PORT, hints, &results);
  int serverd;
  // create the socket
  serverd = socket(results->ai_family, results->ai_socktype, 0);
  err(serverd, "failed to init socket [LINE 17]\n");
  // connect to the server
  int serverSocket = connect(serverd, results->ai_addr, results->ai_addrlen);
  err(serverSocket, "failed to connect to the server [LINE 20]");
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket)
{
  // printf("Waiting for connection\n");
  int client_socket;
  // accept the client connection
  int clientSocket;
  socklen_t sockSize;
  struct sockaddr_storage client_address;
  sockSize = sizeof(client_address);
  client_socket = accept(listen_socket, (struct sockaddr *)&client_address, &sockSize);
  err(client_socket, "failed to accept connection [LINE 41]");
  return client_socket;
}

/*Create and bind a socket.
 * Place the socket in a listening state.
 */
int server_setup()
{
  // setup structs for getaddrinfo
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results);
  // create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  // this code should get around the address in use error
  int yes = 1;
  int sockOpt = setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt, "sockopt  error [LINE 62]");

  // bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  // set socket to listen state
  listen(clientd, 10);
  // free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return clientd;
}

void err(int i, char *message)
{
  if (i < 0)
  {
    printf("Error: %s - %s\n", message, strerror(errno));
    exit(1);
  }
}


