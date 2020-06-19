#include "server.h"
static void if_disconnect(int socket) {
      printf("\n%s", "User from socket");
      printf("\033[0;35m");
      printf("%d", socket);
      printf("\033[0m");
      printf("\033[0;31m");
      printf("%s", " Disconnected\n");
      printf("\033[0m");
      close(socket);
}

void *doprocessing (void *data) {
   int socket = *(int *)data;
   int n;
   char buffer[2048];
   json_object *jobj = json_object_new_object();

while (true) {
   bzero(buffer,2048);
   n = recv(socket, buffer, sizeof(buffer), 0);

   if (n <= 0) {
      if_disconnect(socket);
      return 0;
   }

   printf("%s", "\033[0mTaked \033[0m");
   printf("\033[0;36m");
   printf("%s", buffer);
   printf("\033[0m from socket: ");
   printf("\033[1;35m");
   printf("%d", socket);
   printf("\033[0m");
   printf("%c", '\n');

   jobj = json_tokener_parse(buffer);
   /////////////
   /////////////

   //json_object *if_logging(json_object *jobj); //prototype

   //////////////
   //////////////
   n = send(socket, "Got it!\n", 8, 0);

   if (n <= 0) {
      break;
   }
}
return 0;
}
