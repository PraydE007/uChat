#include "server.h"

int main() {
   int sockfd, portno, clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int rc = 1;
   pthread_t x = 0;
   t_sockbd *sockbd = (t_sockbd *)malloc(sizeof(t_sockbd));

   sockbd->bd = NULL;
   sockbd->sockfd = 0;
   // if (fork()!=0)
   // exit(0);
   // setsid();
   // close(1);
   // close(2);
   // close(3);
   // chdir("/");

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
   listen(sockfd, 5);
   clilen = sizeof(cli_addr);
   mx_data_base_creation(&sockbd->bd);
   while (true) {
      sockbd->sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
      if (sockbd->sockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      else {
         printf("%s ", "\033[0;32mUser connected from socket:\033[0;32m");
         printf("%d\n", sockbd->sockfd);
      }
      pthread_create(&x, NULL, mx_doprocessing, (void *)sockbd);
   }
}
