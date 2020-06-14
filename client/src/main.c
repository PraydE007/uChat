#include "client.h"

int main(int argc, char *argv[]) {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256];
   int rc = 0;

   /////////
   //mx_interface(argc, argv);
   ///////
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }

   portno = atoi(argv[2]);

   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   server = gethostbyname(argv[1]);

   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);

   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   } else
      printf("%s", "Connected!\n");

   /* Now ask for a message from the user, this message
      * will be read by server
   */

while(true) {
   printf("%s", ": ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   json_object *jobj = json_object_new_object();
   json_object *jstring = json_object_new_string("Joys of Programming");
   json_object *jint = json_object_new_int(10);
   json_object *jboolean = json_object_new_boolean(1);
   json_object *jdouble = json_object_new_double(2.14);
   json_object_object_add(jobj,"Site Name", jstring);
   json_object_object_add(jobj,"Technical blog", jboolean);
   json_object_object_add(jobj,"Average posts per day", jdouble);
   json_object_object_add(jobj,"Number of posts", jint);
   // const char *test;
   // struct json_object *parsed;
   // struct json_object *name;
   /* Send message to the server */
   printf("%s", json_object_to_json_string(jobj));
   n = send(sockfd, jobj, sizeof(jobj), false);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

   /* Now read server response */
   bzero(buffer,256);
   n = recv(sockfd, buffer, 255, false);

   if (n <= 0) {
      printf("%s","Lost connection with the server\n");
      while (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
         printf("%s", "Reconnecting...\n");
         close(sockfd);
         sockfd = socket(AF_INET, SOCK_STREAM, 0);
         sleep(3);
      }
   }

   printf("%s", buffer);
}
   return 0;
}
