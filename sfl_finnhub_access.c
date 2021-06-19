#include "sfl_finnhub_access.h"

struct write_result {
  char *data;
  int pos;
};

static size_t curl_write_cb(void *data, size_t size, size_t nmemb, void *userp) {
  struct write_result *res = (struct write_result*) userp;

  memcpy(res->data + res->pos, data, size * nmemb);

  res->pos += size * nmemb;

  return size * nmemb;
}

FinnhubFinancialsData* finnhub_get_symbol_financials_data (char *ticker)
{
  FinnhubFinancialsData *financials_data = malloc (sizeof (FinnhubFinancialsData));
  
  CURL *curl;
  CURLcode http_res;

  char *api_key = getenv(API_KEY_ENV);
  char url[80];

  char *buf = malloc (RESPONSE_BUFFER_SIZE);
  struct write_result api_response = {
    .data = buf,
    .pos = 0
  };

  // Make API call
  
  curl = curl_easy_init();

  sprintf (url, API_URL_FINANCIALS, ticker, api_key);
  
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, &api_response);
  curl_easy_setopt (curl, CURLOPT_URL, url);

  http_res = curl_easy_perform (curl);
  if (http_res != CURLE_OK) {
    fprintf (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(http_res));
  }

  buf[api_response.pos] = '\0';

  // Process JSON
  
  cJSON *response_json = cJSON_Parse (buf);
  if (!response_json) {
    fprintf (stderr, "CRITICAL: error fetching JSON.\n");
  }

  cJSON *metrics = cJSON_GetObjectItemCaseSensitive(response_json, "metric");

  financials_data->ftw_high = cJSON_GetObjectItemCaseSensitive(metrics, "52WeekHigh")->valuedouble;
  financials_data->ftw_high_date = strdup (cJSON_GetObjectItemCaseSensitive(metrics, "52WeekHighDate")->valuestring);
  financials_data->ftw_low = cJSON_GetObjectItemCaseSensitive(metrics, "52WeekLow")->valuedouble;
  financials_data->ftw_low_date = strdup (cJSON_GetObjectItemCaseSensitive(metrics, "52WeekLowDate")->valuestring);
  financials_data->dividend_yield = cJSON_GetObjectItemCaseSensitive(metrics, "currentDividendYieldTTM")->valuedouble;
  financials_data->price_earnings = cJSON_GetObjectItemCaseSensitive(metrics, "peBasicExclExtraTTM")->valuedouble;

  // Cleanup and return
  
  cJSON_Delete (response_json);
  curl_easy_cleanup(curl);
  free(buf);

  return financials_data;
}

FinnhubProfileData* finnhub_get_symbol_profile_data (char *ticker)
{
  FinnhubProfileData *profile_data = malloc (sizeof (FinnhubProfileData));
  
  CURL *curl;
  CURLcode http_res;

  char *api_key = getenv(API_KEY_ENV);
  char url[80];

  char *buf = malloc (1024); //TODO: Fix magic #
  struct write_result api_response = {
    .data = buf,
    .pos = 0
  };

  // Make API call
  
  curl = curl_easy_init();

  sprintf (url, API_URL_PROFILE, ticker, api_key);
  
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, &api_response);
  curl_easy_setopt (curl, CURLOPT_URL, url);

  http_res = curl_easy_perform (curl);
  if (http_res != CURLE_OK) {
    fprintf (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(http_res));
  }

  buf[api_response.pos] = '\0';

  // Process JSON
  
  cJSON *response_json = cJSON_Parse (buf);
  if (!response_json) {
    fprintf (stderr, "CRITICAL: error fetching JSON.\n");
  }

  profile_data->name = strdup (cJSON_GetObjectItemCaseSensitive(response_json, "name")->valuestring);
  profile_data->industry = strdup (cJSON_GetObjectItemCaseSensitive(response_json, "finnhubIndustry")->valuestring);
  profile_data->website = strdup (cJSON_GetObjectItemCaseSensitive(response_json, "weburl")->valuestring);
  profile_data->market_cap = cJSON_GetObjectItemCaseSensitive(response_json, "marketCapitalization")->valuedouble;

  // Cleanup and return
  
  cJSON_Delete (response_json);
  curl_easy_cleanup(curl);
  free(buf);

  return profile_data;
}

FinnhubQuoteData* finnhub_get_symbol_quote_data (char *ticker)
{
  FinnhubQuoteData *quote_data = malloc (sizeof (FinnhubQuoteData));
  
  CURL *curl;
  CURLcode http_res;

  char *api_key = getenv(API_KEY_ENV);
  char url[80];

  char *buf = malloc (1024); //TODO: Fix magic #
  struct write_result api_response = {
    .data = buf,
    .pos = 0
  };

  // Make API call
  
  curl = curl_easy_init();

  sprintf (url, API_URL_QUOTE, ticker, api_key);
  
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, &api_response);
  curl_easy_setopt (curl, CURLOPT_URL, url);

  http_res = curl_easy_perform (curl);
  if (http_res != CURLE_OK) {
    fprintf (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(http_res));
  }

  buf[api_response.pos] = '\0';

  // Process JSON
  
  cJSON *response_json = cJSON_Parse (buf);
  if (!response_json) {
    fprintf (stderr, "CRITICAL: error fetching JSON.\n");
  }

  quote_data->current_price = cJSON_GetObjectItemCaseSensitive(response_json, "c")->valuedouble;
  quote_data->daily_high = cJSON_GetObjectItemCaseSensitive(response_json, "h")->valuedouble;
  quote_data->daily_low = cJSON_GetObjectItemCaseSensitive(response_json, "l")->valuedouble;
  quote_data->last_close_price = cJSON_GetObjectItemCaseSensitive(response_json, "pc")->valuedouble;
  quote_data->open_price = cJSON_GetObjectItemCaseSensitive(response_json, "o")->valuedouble;
  quote_data->timestamp = cJSON_GetObjectItemCaseSensitive(response_json, "t")->valuedouble;

  // Cleanup and return
  
  cJSON_Delete (response_json);
  curl_easy_cleanup(curl);
  free(buf);

  return quote_data;
}
