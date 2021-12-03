#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <cutil/sstring.h>

int main(const int argc,const char* argv[])
{
	sstr_t		*s=sstr_new();

	(void)argc;
	(void)argv;
	sstr_free(&s);
	return 0;
}
