//
// Created by heatesc on 1/08/25.
//

#ifndef CONNECTION_H
#define CONNECTION_H

typedef struct
{
   int sockfd;
} connection_info;

connection_info* connection_init(char* url);
void connection_destroy(connection_info* info);

#endif //CONNECTION_H

