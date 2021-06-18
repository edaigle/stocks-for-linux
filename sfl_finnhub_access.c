#include "sfl_finnhub_access.h"

static size_t get_symbol_quote_cb(void *data, size_t size, size_t nmemb, void *userp)
{
  double *quote = (double*) userp;
  
  cJSON *response_json = cJSON_Parse ( (char*) data);
  if (!response_json) {
    fprintf (stderr, "CRITICAL: error fetching JSON.\n");
  }

  quote[0] = cJSON_GetObjectItemCaseSensitive(response_json, "c")->valuedouble;
  quote[1] = cJSON_GetObjectItemCaseSensitive(response_json, "h")->valuedouble;
  quote[2] = cJSON_GetObjectItemCaseSensitive(response_json, "l")->valuedouble;
  quote[3] = cJSON_GetObjectItemCaseSensitive(response_json, "o")->valuedouble;
  quote[4] = cJSON_GetObjectItemCaseSensitive(response_json, "pc")->valuedouble;
  quote[5] = cJSON_GetObjectItemCaseSensitive(response_json, "t")->valueint;

  cJSON_Delete (response_json);

  return size * nmemb;
}
  
double* get_sfl_symbol_quote (char *ticker)
{
  CURL *curl;
  CURLcode res;

  double *quote = malloc(6 * sizeof(double));
  char url[78];

  curl = curl_easy_init ();
  if (!curl) {
    fprintf (stderr, "CRITICAL: curl_easy_init() failed.\n");
  }

  sprintf (url, API_URL_QUOTE, ticker, getenv(API_KEY_ENV));

  curl_easy_setopt (curl, CURLOPT_URL, url);
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, get_symbol_quote_cb);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, quote);

  res = curl_easy_perform (curl);
  if (res != CURLE_OK) {
    fprintf (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }    

  curl_easy_cleanup(curl);

  return quote;
}
