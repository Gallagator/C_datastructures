#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "test_utils.h"


void testbool(bool condition, char *testname) {
    printf("T %s: %s\n", testname, condition ? "OK" : "FAIL");
}

void testint(int got, int expected, char *testname) {
    printf("T %s (expected=%d, got=%d): %s\n",
           testname, expected, got, expected == got ? "OK" : "FAIL");
}

void test_uint32_t(uint32_t got, uint32_t expected, char *testname) {
    printf("T %s (expeced=%"
    PRIu32
    ", got=%"
    PRIu32
    "): %s\n",
            testname, expected, got, expected == got ? "OK" : "FAIL");
}

void testlong(long got, long expected, char *testname) {
    printf("T %s (expected=%ld, got=%ld): %s\n",
           testname, expected, got, expected == got ? "OK" : "FAIL");
}

void testdouble(double got, double expected, char *testname) {
    printf("T %s (expected=%g, got=%g): %s\n",
           testname, expected, got, expected == got ? "OK" : "FAIL");
}

void teststring(char *got, char *expected, char *testname) {
    printf("T %s (expected='%s', got='%s'): %s\n",
           testname, expected, got, strcmp(expected, got) == 0 ? "OK" : "FAIL");
}

void print_bits(uint32_t num) {
    uint32_t mask = 1 << 31;

    for (int i = 0; i < 32; i++) {
        printf("%d", num & mask ? 1 : 0);
        mask >>= 1;
    }

    printf("\n");
}
