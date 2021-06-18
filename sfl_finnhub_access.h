#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>
#include <curl/curl.h>

#define API_KEY_ENV "LFS_API_KEY"

#define API_URL_QUOTE "https://finnhub.io/api/v1/quote?symbol=%s&token=%s"
