#ifndef EXPRESSION_H
#define EXPRESSION_H
// Function prototypes
#include <stdbool.h>

void handleParseError(const char *message);
double parseExpression(const char **expr, bool *success);
double parseTerm(const char **expr, bool *success);
double parseFactor(const char **expr, bool *success);
double parseNumber(const char **expr, bool *success);
void skipWhitespace(const char **expr);
double calculate(const char *expr, bool *success);

#endif