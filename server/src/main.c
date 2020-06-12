#include "server.h"

int main() {
   int sockfd, portno, clilen;
   int newsockfd = 0;
   struct sockaddr_in serv_addr, cli_addr;
   //int pid;
   int rc = 1;
   pthread_t x = NULL;
   // json_object *jobj = json_object_new_object();
   // json_object *jstring = json_object_new_string("Joys of Programming");
   // json_object *jint = json_object_new_int(10);
   // json_object *jboolean = json_object_new_boolean(1);
   // json_object *jdouble = json_object_new_double(2.14);
   // json_object *jarray = json_object_new_array();
   // json_object *jstring1 = json_object_new_string("c");
   // json_object *jstring2 = json_object_new_string("c++");
   // json_object *jstring3 = json_object_new_string("php");
   // json_object_array_add(jarray,jstring1);
   // json_object_array_add(jarray,jstring2);
   // json_object_array_add(jarray,jstring3);
   // json_object_object_add(jobj,"Site Name", jstring);
   // json_object_object_add(jobj,"Technical blog", jboolean);
   // json_object_object_add(jobj,"Average posts per day", jdouble);
   // json_object_object_add(jobj,"Number of posts", jint);
   // json_object_object_add(jobj,"Categories", jarray);
   // printf("%s", json_object_to_json_string(jobj));
   // exit(0);
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
