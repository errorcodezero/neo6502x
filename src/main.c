#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

// int main(int argc, char *argv[])
int main()
{
	VirtualMachine vm = init_vm();
	vm.accum++;
	return EXIT_SUCCESS;
}
