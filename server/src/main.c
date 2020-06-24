#include "server.h"

int main(int argc, char **argv) {
   int sockfd, portno, clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int rc = 1;
   pthread_t x = 0;
   t_sockbd *sockbd = (t_sockbd *)malloc(sizeof(t_sockbd));

   if (argc < 2) {
        fprintf(stderr,"usage: %s port\n", argv[0]);
        return 0;
   }
   sockbd->bd = NULL;
   sockbd->sockfd = 0;
   sockbd->log_sescr = mx_create_log();
   mx_demonize(); 

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      write(sockbd->log_sescr, "ERROR: opening socket\n", 22);
      exit(1);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));

   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      write(sockbd->log_sescr, "ERROR on binding\n", 17);
      exit(1);
   }
   listen(sockfd, 5);
   clilen = sizeof(cli_addr);
   mx_data_base_creation(&sockbd->bd);
   while (true) {
      sockbd->sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
      if (sockbd->sockfd < 0) {
         write(sockbd->log_sescr, "ERROR on accept\n", 16);
         exit(1);
      }
      else {
         write(sockbd->log_sescr, "User connected from socket ", 27);
         write(sockbd->log_sescr, mx_itoa(sockbd->sockfd), 1);
         write(sockbd->log_sescr, "\n", 1);
      }
      pthread_create(&x, NULL, mx_doprocessing, (void *)sockbd);
   }
   //sqlite3_close(sockbd->bd);
}
