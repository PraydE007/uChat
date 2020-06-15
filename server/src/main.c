#include "server.h"

int main() {
   int sockfd, portno, clilen;
   int newsockfd = 0;
   struct sockaddr_in serv_addr, cli_addr;
   int rc = 1;
   pthread_t x = NULL;
   // json_object *jobj = json_object_new_object();
   // json_object *jstring = json_object_new_string("Joys of Programming");
   // json_object *jint = json_object_new_int(10);
   // json_object *jboolean = json_object_new_boolean(1);
   // json_object *jdouble = json_object_new_double(2.14);
   // json_object_object_add(jobj,"Site Name", jstring);
   // json_object_object_add(jobj,"Technical blog", jboolean);
   // json_object_object_add(jobj,"Average posts per day", jdouble);
   // json_object_object_add(jobj,"Number of posts", jint);
   // const char *test;
   // struct json_object *parsed;
   // struct json_object *name;

   // //mx_data_base_creation();

   // test = json_object_to_json_string(jobj);
   // parsed = json_tokener_parse(test);
   // json_object_object_get_ex(parsed, "Site Name", &name);

   // printf("%s", json_object_to_json_string(name));
   // exit(0);
   /* First call to socket() function */
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
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   mx_data_base_creation();
   while (true) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      else {
         printf("%s ", "\033[0;32mUser connected from socket:\033[0;32m");
         printf("%d\n", newsockfd);
      }
      pthread_create(&x, NULL, doprocessing, (void *)&newsockfd);
   }
}
