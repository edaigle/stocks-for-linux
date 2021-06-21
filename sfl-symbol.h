#include <stdio.h>
#include <stdlib.h>

#include "sfl-finnhub-access.h"

typedef struct {
  char *ticker;
  
  char *name;
  char *industry;
  char *website;
  double market_cap;

  double current_price;
  double daily_high;
  double daily_low;
  double last_close_price;
  double open_price;
  double timestamp;

  double ftw_high;
  char* ftw_high_date;
  double ftw_low;
  char* ftw_low_date;
  double dividend_yield;
  double price_earnings;
} SFLSymbol;

int sfl_symbol_update_financials (SFLSymbol *self);
int sfl_symbol_update_profile (SFLSymbol *self);
int sfl_symbol_update_quote (SFLSymbol *self);

SFLSymbol* sfl_symbol_new (char* ticker);
void sfl_symbol_destroy (SFLSymbol *self);
  
