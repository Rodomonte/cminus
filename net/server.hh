// SERVER

#ifndef server_hh
#define server_hh

#include "../core/util.hh"


#define PORT 65432

struct server {
  int id, socket_id;
  server(int _id): id(_id) {}

  void start(){
    int i, len;
    struct sockaddr_in srv_addr, cli_addr;
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id == -1) kill("Could not create socket");
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(PORT);
    if(bind(socket_id, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
      kill("Could not bind socket");
    if(listen(socket_id, 5) != 0)
      kill("Could not verify socket connection");
    len = sizeof(cli_addr);
    if((socket_id = accept(socket_id, (struct sockaddr*)&cli_addr, &len)) < 0)
      kill("Could not accept connection verification");
    inet_ntop(AF_INET, &cli_addr.sin_addr, buf, INET_ADDRSTRLEN);
    printf("%s connected\n", buf);

    while(1){
      read(socket_id, buf, sizeof(buf));
      printf("client > %s\n", buf);
      printf("server > ");
      i = 0;
      while((buf[i++] = getchar()) != '\n');
      write(socket_id, buf, strlen(buf));
    }
  }
};


#endif
