#include "server.h"

void *doprocessing (void *data) {
   int socket = *(int *)data;
   int n;
   char buffer[256];

while (true) {
   bzero(buffer,256);
   n = read(socket,buffer,255);
   if (n <= 0) {
      printf("\n%s", "User ");
      printf("\033[0;35m");
      printf("%d", socket);
      printf("\033[0m");
      printf("\033[0;31m");
      printf("%s", " Disconnected\n");
      printf("\033[0m");
      close(socket);
      return 0;
   }

   printf("%s", "\033[0mTaked \033[0m");
   printf("\033[0;36m");

   for (int i = 0; buffer[i] != '\n'; i++) {
      printf("%c", buffer[i]);
   }

   printf("\033[0m from ");
   printf("\033[1;35m");
   printf("%d", socket);
   printf("\033[0m");
   printf("%c", '\n');

   n = write(socket,"Got it!\n", 8);

   if (n <= 0) {
      break;
   }
}
return 0;
}
