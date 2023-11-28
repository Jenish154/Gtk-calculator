#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "expressionEvaluator.h"

// Helper function to handle errors
void handleParseError(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// Function to skip whitespaces in the input string
void skipWhitespace(const char **expr) {
    while (isspace(**expr)) {
        (*expr)++;
    }
}

// Function to parse a number from the input string
double parseNumber(const char **expr, bool *success) {
    skipWhitespace(expr);

    char *endptr;
    double result = strtod(*expr, &endptr);

    if (endptr == *expr) {
        *success = false;
        handleParseError("Invalid number");
    }

    *expr = endptr; // Update the expression pointer to the next character after the number
    return result;
}

// Function to parse a factor (number or subexpression) from the input string
double parseFactor(const char **expr, bool *success) {
    skipWhitespace(expr);

    if (**expr == '(') {
        (*expr)++; // Move past the '('
        double result = parseExpression(expr, success);
        skipWhitespace(expr);

        if (**expr == ')') {
            (*expr)++; // Move past the ')'
            return result;
        } else {
            *success = false;
            handleParseError("Expected ')' in expression");
        }
    } else {
        return parseNumber(expr, success);
    }
}

// Function to parse a term (* or / operation) from the input string
double parseTerm(const char **expr, bool *success) {
    double left = parseFactor(expr, success);
    skipWhitespace(expr);

    while (**expr == '*' || **expr == '/') {
        char op = *(*expr)++;
        double right = parseFactor(expr, success);

        if (op == '*') {
            left *= right;
        } else {
            if (right != 0) {
                left /= right;
            } else {
                *success = false;
                handleParseError("Division by zero");
            }
        }

        skipWhitespace(expr);
    }

    return left;
}

// Function to parse an expression (+ or - operation) from the input string
double parseExpression(const char **expr, bool *success) {
    double left = parseTerm(expr, success);
    skipWhitespace(expr);

    while (**expr == '+' || **expr == '-') {
        char op = *(*expr)++;
        double right = parseTerm(expr, success);

        if (op == '+') {
            left += right;
        } else {
            left -= right;
        }

        skipWhitespace(expr);
    }

    return left;
}

// Main calculator function
double calculate(const char *expr, bool *success) {
    *success = true;
    return parseExpression(&expr, success);
}

/*
int main() {
    // Example usage
    const char *expression = "3 + 4 *  5 - 2  / 0";
    bool success;
    double result = calculate(expression, &success);

    if (success) {
        printf("Result: %lf\n", result);
    }

    return 0;
}
*/