// Sean Szumlanski
// COP 3502, Fall 2018

// ============================
// Glowworm: UnitTestLauncher.c
// ============================
// This code simply calls the unit_test() function in whatever test case is
// compiled with the program. This only works if Glowworm.h is set to re-define
// main() as __hidden_main__(). Otherwise, compiling this with Glowworm.c will
// result in two definitions of the main() function: one in Glowworm.c, and one
// in this file.


int unit_test(int argc, char **argv);

int main(int argc, char **argv)
{
	unit_test(argc, argv);
	return 0;
}
