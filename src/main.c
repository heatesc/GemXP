//
// Created by heatesc on 31/07/25.
//
#include <connection.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

#define STDIN_BUF_SZ (256)

int main(int argc, char** argv)
{
    // retrieve url from user
    printf("Enter (gemini) url: ");
    char url[STDIN_BUF_SZ];
    fgets(url, sizeof(url), stdin);
    url[strlen(url) - 1] = '\0';
    if (!url_valid(url)) return 1; // bug: clion says cannot resolve symbol 'url_valid'
    connection_info* con_info = connection_init(url);

    connection_destroy(con_info);
    return 0;
}



