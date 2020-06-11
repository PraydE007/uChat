#include "server.h"

int main() {
   int sockfd, portno, clilen;
   int newsockfd = 0;
   struct sockaddr_in serv_addr, cli_addr;
   //int pid;
   int rc = 1;
   pthread_t x = NULL;

   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
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

   listen(sockfd,5);
   clilen = sizeof(cli_addr);

   while (true) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      else {
         printf("%s ", "\033[0;32mUser connected with id:\033[0;32m");
         printf("%d\n", newsockfd);
      }

      pthread_create(&x, NULL, doprocessing, (void *)&newsockfd);
      /* Create child process */
      //pid = fork();

      // if (pid < 0) {
      //    perror("ERROR on fork");
      //    exit(1);
      // }
      // else if (pid == 0) {
      //    close(sockfd);
      //    doprocessing(newsockfd);
      //    exit(0);
      // }
      }
}
