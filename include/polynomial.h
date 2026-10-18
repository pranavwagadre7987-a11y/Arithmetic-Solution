#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>

/* One term of a polynomial, e.g. 3x^2 -> coeff = 3, exp = 2.
 * A polynomial is a singly linked list of terms, sorted by exp (highest first). */
typedef struct Term {
    int coeff;
    int exp;
    struct Term *next;
} Term;

/* Insert a term (keeps list sorted, merges like terms, removes zero terms).
 * Returns the new head of the list. */
Term *poly_insert(Term *head, int coeff, int exp);

/* Each of these returns a NEW polynomial; the inputs are not modified. */
Term *poly_add(const Term *a, const Term *b);
Term *poly_subtract(const Term *a, const Term *b);
Term *poly_multiply(const Term *a, const Term *b);
Term *poly_derivative(const Term *a);

double poly_evaluate(const Term *a, double x);

void poly_free(Term *head);

/* Writes e.g. "3x^2 + 2x + 1" into buf (writes "0" for an empty polynomial). */
void poly_to_string(const Term *p, char *buf, size_t size);

/* Prints the polynomial and its linked-list form to stdout. */
void poly_print(const char *label, const Term *p);

#endif