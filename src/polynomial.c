#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/polynomial.h"

static Term *new_term(int coeff, int exp, Term *next) {
    Term *node = (Term *)malloc(sizeof(Term));
    if (node == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    node->coeff = coeff;
    node->exp = exp;
    node->next = next;
    return node;
}

Term *poly_insert(Term *head, int coeff, int exp) {
    if (coeff == 0) return head;

    Term *prev = NULL;
    Term *curr = head;
    while (curr != NULL && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && curr->exp == exp) {
        /* same exponent: merge coefficients */
        curr->coeff += coeff;
        if (curr->coeff == 0) {
            /* term cancelled out: remove it */
            if (prev == NULL) head = curr->next;
            else prev->next = curr->next;
            free(curr);
        }
        return head;
    }

    Term *node = new_term(coeff, exp, curr);
    if (prev == NULL) head = node;
    else prev->next = node;
    return head;
}

Term *poly_add(const Term *a, const Term *b) {
    Term *result = NULL;
    for (const Term *t = a; t != NULL; t = t->next) result = poly_insert(result, t->coeff, t->exp);
    for (const Term *t = b; t != NULL; t = t->next) result = poly_insert(result, t->coeff, t->exp);
    return result;
}

Term *poly_subtract(const Term *a, const Term *b) {
    Term *result = NULL;
    for (const Term *t = a; t != NULL; t = t->next) result = poly_insert(result, t->coeff, t->exp);
    for (const Term *t = b; t != NULL; t = t->next) result = poly_insert(result, -t->coeff, t->exp);
    return result;
}

Term *poly_multiply(const Term *a, const Term *b) {
    Term *result = NULL;
    for (const Term *x = a; x != NULL; x = x->next) {
        for (const Term *y = b; y != NULL; y = y->next) {
            result = poly_insert(result, x->coeff * y->coeff, x->exp + y->exp);
        }
    }
    return result;
}

Term *poly_derivative(const Term *a) {
    Term *result = NULL;
    for (const Term *t = a; t != NULL; t = t->next) {
        if (t->exp > 0) result = poly_insert(result, t->coeff * t->exp, t->exp - 1);
    }
    return result;
}

double poly_evaluate(const Term *a, double x) {
    double sum = 0.0;
    for (const Term *t = a; t != NULL; t = t->next) {
        double power = 1.0;
        for (int i = 0; i < t->exp; i++) power *= x;
        sum += t->coeff * power;
    }
    return sum;
}

void poly_free(Term *head) {
    while (head != NULL) {
        Term *next = head->next;
        free(head);
        head = next;
    }
}

/* helper: append formatted text to buf without overflowing */
static void append(char *buf, size_t size, size_t *off, const char *fmt, ...) {
    if (*off >= size) return;
    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(buf + *off, size - *off, fmt, args);
    va_end(args);
    if (n > 0) *off += (size_t)n;
}

void poly_to_string(const Term *p, char *buf, size_t size) {
    size_t off = 0;
    if (size == 0) return;
    buf[0] = '\0';
    if (p == NULL) {
        append(buf, size, &off, "0");
        return;
    }
    for (const Term *t = p; t != NULL; t = t->next) {
        int c = t->coeff;
        int a = c < 0 ? -c : c;

        if (t == p) {
            if (c < 0) append(buf, size, &off, "-");
        } else {
            append(buf, size, &off, c < 0 ? " - " : " + ");
        }

        if (t->exp == 0) {
            append(buf, size, &off, "%d", a);
        } else {
            if (a != 1) append(buf, size, &off, "%d", a);
            append(buf, size, &off, "x");
            if (t->exp != 1) append(buf, size, &off, "^%d", t->exp);
        }
    }
}

void poly_print(const char *label, const Term *p) {
    char buf[1024];
    poly_to_string(p, buf, sizeof buf);
    printf("%s: %s\n", label, buf);
    printf("   linked list: ");
    for (const Term *t = p; t != NULL; t = t->next) {
        printf("[%d | x^%d] -> ", t->coeff, t->exp);
    }
    printf("NULL\n");
}