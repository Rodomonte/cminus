// CLIENT

#ifndef client_hh
#define client_hh

#include "../core/util.hh"


struct client {
  int server_id, socket_id;

  void link(int id){
    struct sockaddr_in addr;
    server_id = id;
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id == -1) kill("Could not create socket");
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8080);
    if(connect(socket_id, (struct sockaddr*)&addr, sizeof(addr)) != 0)
      kill("Could not connect to server");
  }

  void start(){
    int i;
    while(1){
      printf("client > ");
      i = 0;
      while((buf[i++] = gc()) != '\n');
      write(socket_id, buf, sizeof(buf));
      read(socket_id, buf, sizeof(buf));
      printf("server > %s\n", buf);
    }
  }
};


#endif
