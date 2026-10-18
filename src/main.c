#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/polynomial.h"

#define MAX_TERMS 50

/* ---------- safe input helpers (validate everything the user types) ---------- */

static int read_int(const char *prompt, int min, int max, int *out) {
    char line[64];
    char *end;
    for (;;) {
        printf("%s", prompt);
        if (fgets(line, sizeof line, stdin) == NULL) return 0; /* EOF */
        long v = strtol(line, &end, 10);
        if (end == line || (*end != '\n' && *end != '\0')) {
            printf("  Invalid input. Please enter a whole number.\n");
            continue;
        }
        if (v < min || v > max) {
            printf("  Value must be between %d and %d.\n", min, max);
            continue;
        }
        *out = (int)v;
        return 1;
    }
}

static int read_double(const char *prompt, double *out) {
    char line[64];
    char *end;
    for (;;) {
        printf("%s", prompt);
        if (fgets(line, sizeof line, stdin) == NULL) return 0;
        double v = strtod(line, &end);
        if (end == line || (*end != '\n' && *end != '\0')) {
            printf("  Invalid input. Please enter a number.\n");
            continue;
        }
        *out = v;
        return 1;
    }
}

/* Reads a polynomial from the user. Returns 1 on success, 0 on EOF. */
static int read_polynomial(const char *name, Term **out) {
    int n;
    Term *p = NULL;
    printf("\nEnter %s\n", name);
    if (!read_int("  Number of terms (1-50): ", 1, MAX_TERMS, &n)) return 0;
    for (int i = 1; i <= n; i++) {
        int coeff, exp;
        char prompt[64];
        sprintf(prompt, "  Term %d coefficient: ", i);
        if (!read_int(prompt, -1000000, 1000000, &coeff)) { poly_free(p); return 0; }
        sprintf(prompt, "  Term %d exponent (>= 0): ", i);
        if (!read_int(prompt, 0, 1000, &exp)) { poly_free(p); return 0; }
        p = poly_insert(p, coeff, exp);
    }
    *out = p;
    return 1;
}

static void show_result(const char *title, Term *result) {
    printf("\n--- %s ---\n", title);
    poly_print("Result", result);
    poly_free(result);
}

/* ---------- demo (no typing needed) ---------- */

static void run_demo(void) {
    const char *line = "============================================================";
    printf("%s\n POLYNOMIAL ARITHMETIC USING LINKED LIST (C Demo)\n%s\n", line, line);

    Term *p1 = NULL, *p2 = NULL;
    p1 = poly_insert(p1, 3, 2); p1 = poly_insert(p1, 2, 1); p1 = poly_insert(p1, 1, 0);
    p2 = poly_insert(p2, 1, 2); p2 = poly_insert(p2, -2, 1); p2 = poly_insert(p2, 4, 0);

    printf("\n--- Input polynomials ---\n");
    poly_print("P1", p1);
    poly_print("P2", p2);

    show_result("Addition: P1 + P2", poly_add(p1, p2));
    show_result("Subtraction: P1 - P2", poly_subtract(p1, p2));
    show_result("Multiplication: P1 * P2", poly_multiply(p1, p2));
    show_result("Derivative of P1", poly_derivative(p1));

    printf("\n--- Evaluate P1 at x = 2 ---\n");
    printf("P1(2) = %g\n", poly_evaluate(p1, 2));

    printf("\n--- Edge case: unsorted input with like terms ---\n");
    Term *messy = NULL;
    messy = poly_insert(messy, 4, 0); messy = poly_insert(messy, 2, 3);
    messy = poly_insert(messy, 5, 3); messy = poly_insert(messy, 1, 1);
    poly_print("4 + 2x^3 + 5x^3 + x", messy);

    show_result("Edge case: terms cancel out (P1 - P1)", poly_subtract(p1, p1));

    poly_free(messy);
    poly_free(p1);
    poly_free(p2);
    printf("\n%s\n", line);
}

/* ---------- menu ---------- */

static void print_menu(void) {
    printf("\n========== POLYNOMIAL ARITHMETIC (Linked List) ==========\n");
    printf(" 1. Enter polynomial P1\n");
    printf(" 2. Enter polynomial P2\n");
    printf(" 3. Display P1 and P2\n");
    printf(" 4. Add        (P1 + P2)\n");
    printf(" 5. Subtract   (P1 - P2)\n");
    printf(" 6. Multiply   (P1 * P2)\n");
    printf(" 7. Derivative of P1\n");
    printf(" 8. Evaluate P1 at x\n");
    printf(" 9. Run demo\n");
    printf(" 0. Exit\n");
    printf("=========================================================\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--demo") == 0) {
        run_demo();
        return 0;
    }

    Term *p1 = NULL, *p2 = NULL;
    int have1 = 0, have2 = 0;
    int choice;

    for (;;) {
        print_menu();
        if (!read_int("Enter your choice: ", 0, 9, &choice)) break;

        if (choice == 0) break;

        if (choice == 1) {
            Term *tmp = NULL;
            if (!read_polynomial("P1", &tmp)) break;
            poly_free(p1); p1 = tmp; have1 = 1;
            poly_print("\nP1 saved", p1);
        } else if (choice == 2) {
            Term *tmp = NULL;
            if (!read_polynomial("P2", &tmp)) break;
            poly_free(p2); p2 = tmp; have2 = 1;
            poly_print("\nP2 saved", p2);
        } else if (choice == 9) {
            run_demo();
        } else if (choice == 3) {
            if (have1) poly_print("P1", p1); else printf("P1 is not entered yet.\n");
            if (have2) poly_print("P2", p2); else printf("P2 is not entered yet.\n");
        } else if (choice == 4 || choice == 5 || choice == 6) {
            if (!have1 || !have2) {
                printf("Please enter both P1 and P2 first (options 1 and 2).\n");
                continue;
            }
            if (choice == 4) show_result("Addition: P1 + P2", poly_add(p1, p2));
            else if (choice == 5) show_result("Subtraction: P1 - P2", poly_subtract(p1, p2));
            else show_result("Multiplication: P1 * P2", poly_multiply(p1, p2));
        } else if (choice == 7) {
            if (!have1) { printf("Please enter P1 first (option 1).\n"); continue; }
            show_result("Derivative of P1", poly_derivative(p1));
        } else if (choice == 8) {
            double x;
            if (!have1) { printf("Please enter P1 first (option 1).\n"); continue; }
            if (!read_double("Enter value of x: ", &x)) break;
            printf("\nP1(%g) = %g\n", x, poly_evaluate(p1, x));
        }
    }

    poly_free(p1);
    poly_free(p2);
    printf("\nGoodbye!\n");
    return 0;
}