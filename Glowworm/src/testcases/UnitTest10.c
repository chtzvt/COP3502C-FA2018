// Sean Szumlanski
// COP 3502, Fall 2018

// ======================
// Glowworm: UnitTest10.c
// ======================
// This test case helps ensure that your hoursSpent() function is implemented
// correctly.
//
// For instructions on compiling your program with this source code, please see
// the assignment PDF.


#include <stdio.h>
#include "Glowworm.h"

// This acts as the main() function for this test case.
int unit_test(int argc, char **argv)
{
	int success = 1;

	// hoursSpent() must be strictly greater than zero.
	if (hoursSpent() <= 0)
		success = 0;

	printf("%s\n", success ? "Success!" : "Fail whale!");
	return 0;
}
