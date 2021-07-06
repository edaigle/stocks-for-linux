#include "sfl-symbol.h"

/* @self: the symbol we're updating
 * 
 * Updates the financials fields for the given symbol. 
 * Returns true if successful, else false.
 */
int sfl_symbol_update_financials (SFLSymbol *self)
{
  FinnhubFinancialsData *data = finnhub_get_symbol_financials_data (self->ticker);
  if (!data) {
    fprintf(stderr, "CRITICAL: Error updating financials for %s.\n", self->ticker);
    return 0;
  }

  self->ftw_high = data->ftw_high;
  self->ftw_high_date = strdup (data->ftw_high_date);
  self->ftw_low = data->ftw_low; 
  self->ftw_low_date = strdup (data->ftw_low_date); 
  self->dividend_yield = data->dividend_yield; 
  self->price_earnings = data->price_earnings; 

  free (data->ftw_high_date);
  free (data->ftw_low_date);
  free (data);
  return 1;
}

/* @self: the symbol we're updating
 * 
 * Updates the profile fields for the given symbol. 
 * Returns true if successful, else false.
 */
int sfl_symbol_update_profile (SFLSymbol *self)
{
  FinnhubProfileData *data = finnhub_get_symbol_profile_data (self->ticker);
  if (!data) {
    fprintf(stderr, "CRITICAL: Error updating financials for %s.\n", self->ticker);
    return 0;
  }

  self->name = strdup (data->name);
  self->industry = strdup (data->industry);
  self->website = strdup (data->website);
  self->market_cap = data->market_cap;

  free (data->name);
  free (data->industry);
  free (data->website);
  free (data);
  return 1;
}

/* @self: the symbol we're updating
 * 
 * Updates the quote fields for the given symbol. 
 * Returns true if successful, else false.
 */
int sfl_symbol_update_quote (SFLSymbol *self)
{
  FinnhubQuoteData *data = finnhub_get_symbol_quote_data (self->ticker);
  if (!data) {
    fprintf(stderr, "CRITICAL: Error updating quote for %s.\n", self->ticker);
    return 0;
  }

  self->current_price = data->current_price;
  self->daily_high = data->daily_high;
  self->daily_low = data->daily_low;
  self->last_close_price = data->last_close_price;
  self->open_price = data->open_price;
  self->timestamp = data->timestamp;

  free (data);
  return 1;
}

/* @ticker: the ticker for the symbol we're creating
 * 
 * Creates a new SFLSymbol for the given ticker, initializing
 * all fields. Returns NULL if any fields fail to initialize.
 * TODO: Check symbol is valid!
 */
SFLSymbol* sfl_symbol_new (char *ticker)
{
  SFLSymbol *symbol = malloc (sizeof (SFLSymbol));
  symbol->ticker = strdup (ticker);
  
  if (!sfl_symbol_update_quote (symbol)
      || !sfl_symbol_update_financials (symbol)
      || !sfl_symbol_update_profile (symbol)) {
    sfl_symbol_destroy (symbol);
    symbol = NULL;
  }

  return symbol;
}

/* @self: the symbol we're destroying
 *
 * Destructor function for SFLSymbols.
 */
void sfl_symbol_destroy (SFLSymbol *self) {
  if (self->ticker) {
    free (self->ticker);
  }

  if (self->name) {
    free (self->name);
  }

  if (self->industry) {
    free (self->industry);
  }

  if (self->website) {
    free (self->website);
  }

  if (self->ftw_high_date) {
    free (self->ftw_high_date);
  }

  if (self->ftw_low_date) {
    free (self->ftw_low_date);
  }

  free (self);
  return;
}
