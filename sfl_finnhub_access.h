#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>
#include <curl/curl.h>

#define API_KEY_ENV "LFS_API_KEY"

#define API_URL_CANDLE "https://finnhub.io/api/v1/stock/candle?symbol=%s&resolution=1&from=%s&to=%s&token=%s"
#define API_URL_FINANCIALS "https://finnhub.io/api/v1/stock/metric?symbol=%s&metric=all&token=%s"
#define API_URL_PROFILE "https://finnhub.io/api/v1/stock/profile2?symbol=%s&token=%s"
#define API_URL_QUOTE "https://finnhub.io/api/v1/quote?symbol=%s&token=%s"

#define RESPONSE_BUFFER_SIZE 18300 // Financials file is exactly 18275 bytes, TODO: use realloc

typedef struct {
  double ftw_high;
  char* ftw_high_date;
  double ftw_low;
  char* ftw_low_date;
  double dividend_yield;
  double price_earnings;
} FinnhubFinancialsData;

typedef struct {
  char *name;
  char *industry;
  char *website;
  double market_cap;
} FinnhubProfileData;

typedef struct {
  double current_price;
  double daily_high;
  double daily_low;
  double last_close_price;
  double open_price;
  double timestamp;
} FinnhubQuoteData;
  
