//
// Created by heatesc on 1/08/25.
//

#include "../include/connection.h"
#include "../include/common.h"
#include "../include/utils.h"

#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include  <sys/types.h>



connection_info* connection_init(char* url)
{
   connection_info* ret = malloc(sizeof(connection_info));
   if (NULL == ret)
   {
      perror("malloc");
      return NULL;
   }
   ret->sockfd = -1;

   // use getaddrinfo to get connect() and socket() args, until
   // we achieve a successful connection
   struct addrinfo hints;
   struct addrinfo* result;
   char* hostname = extract_hostname(url);

   if (NULL == hostname)
   {
      free(ret);
      return NULL;
   }
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC; // allow both ipv4 and ipv6
   hints.ai_socktype = SOCK_STREAM; // ensure tcp
   hints.ai_flags = 0;
   hints.ai_protocol = 0;

   int gai_ret = getaddrinfo(hostname, GEMINI_CONNECTION_PORT, &hints, &result);
   printf("Attempting to connect to host: '%s' on port '%s'\n", hostname, GEMINI_CONNECTION_PORT);
   free(hostname);
   hostname = NULL;

   if (0 != gai_ret)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_ret));
      free(ret);
      return NULL;
   }

   fflush(stdout);

   bool connected = false;
   for (struct addrinfo* cand = result; cand; cand = cand->ai_next)
   {
      // create socket
      int sockfd_tmp = socket(cand->ai_family, cand->ai_socktype, cand->ai_protocol);
      if (-1 == sockfd_tmp)
      {
         // if socket creation fails, go to next candidate
         perror("socket failed");
         continue;
      }
      // attempt to connect
      if (-1 != connect(sockfd_tmp, cand->ai_addr, cand->ai_addrlen))
      {
         ret->sockfd = sockfd_tmp;
         connected = true;
         break;
      }

      // if connection fails, go to next candidate
      perror("connection failed");
      close(sockfd_tmp);
   }

   // cleanup
   freeaddrinfo(result);
   if (!connected)
   {
      fprintf(stderr, "failed to connect to any address for %s\n", url);
      free(ret);
      return NULL;
   }
   printf("successfully connected to host\n");
   return ret;
}


void connection_destroy(connection_info* info)
{
   free(info);
}
