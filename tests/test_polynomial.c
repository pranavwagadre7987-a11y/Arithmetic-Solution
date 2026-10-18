#include <stdio.h>
#include <string.h>
#include "../include/polynomial.h"

static int passed = 0, failed = 0;

static void check_str(const char *name, const Term *p, const char *expected) {
    char buf[256];
    poly_to_string(p, buf, sizeof buf);
    if (strcmp(buf, expected) == 0) {
        printf("  [PASS] %s -> %s\n", name, buf);
        passed++;
    } else {
        printf("  [FAIL] %s: expected \"%s\" but got \"%s\"\n", name, expected, buf);
        failed++;
    }
}

static void check_num(const char *name, double got, double expected) {
    if (got == expected) {
        printf("  [PASS] %s -> %g\n", name, got);
        passed++;
    } else {
        printf("  [FAIL] %s: expected %g but got %g\n", name, expected, got);
        failed++;
    }
}

int main(void) {
    /* P1 = 3x^2 + 2x + 1, P2 = x^2 - 2x + 4 */
    Term *p1 = NULL, *p2 = NULL;
    p1 = poly_insert(p1, 3, 2); p1 = poly_insert(p1, 2, 1); p1 = poly_insert(p1, 1, 0);
    p2 = poly_insert(p2, 1, 2); p2 = poly_insert(p2, -2, 1); p2 = poly_insert(p2, 4, 0);

    printf("Running polynomial tests...\n");

    Term *r = poly_add(p1, p2);        check_str("add", r, "4x^2 + 5");                 poly_free(r);
    r = poly_subtract(p1, p2);         check_str("subtract", r, "2x^2 + 4x - 3");      poly_free(r);
    r = poly_multiply(p1, p2);         check_str("multiply", r, "3x^4 - 4x^3 + 9x^2 + 6x + 4"); poly_free(r);
    r = poly_derivative(p1);           check_str("derivative", r, "6x + 2");            poly_free(r);
    check_num("evaluate at 2", poly_evaluate(p1, 2), 17);
    r = poly_subtract(p1, p1);         check_str("cancelling terms", r, "0");           poly_free(r);

    Term *m = NULL;
    m = poly_insert(m, 1, 0); m = poly_insert(m, 2, 3); m = poly_insert(m, 5, 3);
    check_str("merge like terms + sorting", m, "7x^3 + 1");
    poly_free(m);

    check_str("empty polynomial", NULL, "0");

    poly_free(p1);
    poly_free(p2);

    printf("\nResult: %d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}