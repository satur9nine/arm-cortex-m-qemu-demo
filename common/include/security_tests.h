#ifndef SECURITY_TESTS_H
#define SECURITY_TESTS_H

int test_stack_buffer_overflow(unsigned int number);

void test_fortify_source_level2(void);

void test_fortify_source_level3(void);

#endif // SECURITY_TESTS_H
