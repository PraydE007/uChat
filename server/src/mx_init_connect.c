#include "server.h"

int mx_init_connect() {
   int sockfd, portno, clilen;
   int newsockfd = 0;
   struct sockaddr_in serv_addr, cli_addr;
   int rc = 1;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   return sockfd;
}
