//
// Created by heatesc on 1/08/25.
//

#include "../include/utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

char* extract_hostname(char* url)
{
    // gemini url format: gemini://
    // e.g. gemini://example.com/
    // extract the hostname from the url
    int host_len = 0;
    while (url[GEMINI_PREFIX_LEN + ++host_len] != '/');
    char* hostname = malloc(host_len + 1);
    if (NULL == hostname)
    {
        perror("malloc");
        return NULL;
    }
    strncpy(hostname, url + GEMINI_PREFIX_LEN, host_len);
    return hostname;
}

bool url_valid(char* url)
{
    //TODO
    return true;
}

