#include "socket_networking.h"


/*=========================
  server_setup
  args:
  returns socket descriptor
  =========================*/
int server_setup() {
  // sets up addrinfo and hints to set up socket
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; // for TCP ports
  hints->ai_flags = AI_PASSIVE; // ???
  getaddrinfo(NULL, "80", hints, &results); // NULL to connect with multiple clients, port 80
  // does the search for the ports and stuff

  // make the socket
  int soc = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  // bind the port
  bind(soc,results->ai_addr, results->ai_addrlen);
  printf("setup completed\n");
  return soc;
}

/*=========================
  server_connect
  args: int socket_descriptor
  =========================*/
int server_connect(int soc) {
  // set up addrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; // for TCP ports
  hints->ai_flags = AI_PASSIVE; // ???
  getaddrinfo(NULL, "80", hints, &results);

  // listen
  listen(soc,10);

  // accept
  int client_socket; 
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  printf("[server] server waiting to accept\n");
  client_socket = accept(soc,(struct sockaddr *)&client_address, &sock_size);

  // free
  free(hints);
  freeaddrinfo(results);
}


/*=========================
  client_handshake
  args:
  =========================*/
int client_handshake() {
  // set up addrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; // for TCP ports
  getaddrinfo("127.0.0.1", "80", hints, &results); // localhost rn


  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  connect(sd, results->ai_addr, results->ai_addrlen);
}