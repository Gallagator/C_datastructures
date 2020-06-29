#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>
#include <stdint.h>

// Lightweight library for unit testing our programs

void testbool(bool condition, char *testname);

void testint(int got, int expected, char *testname);

void test_uint32_t(uint32_t got, uint32_t expected, char *testname);

void testlong(long got, long expected, char *testname);

void testdouble(double got, double expected, char *testname);

void teststring(char *got, char *expected, char *testname);

// Utility function to print bits of instructions or numbers
void print_bits(uint32_t num);

#endif
