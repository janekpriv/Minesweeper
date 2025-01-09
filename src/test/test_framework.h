#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H

# include <stdio.h>
# include <stdlib.h>

# define ASSERT_EQ(expected, actual) \
	if ((expected) != (actual))     \
	{                               \
		printf("Test failed at %s:%d\nExpected: %d, Actual: %d\n", __FILE__, __LINE__, (expected), (actual)); \
		exit(1); \
	} else { \
		printf("Test passed\n"); \
	}

# define TEST(name) \
	void name(void)

#endif // TEST_FRAMEWORK_H