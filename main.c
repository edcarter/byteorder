#include "byteorder.h"

#include <stdio.h>
#include <assert.h>

int main(void)
{
	uint32_t a, b;
	uint16_t c, d;

	a = 0xDEADBEEF;

	b = htonl(a);
	printf("%#010x\n", b);
	assert(b == 0xEFBEADDE);

	b = ntohl(b);
	printf("%#010x\n", b);
	assert(b == a);

	c = 0xDEAD;

	d = htons(c);
	printf("%#6x\n", d);
	assert(d == 0xADDE);

	d = ntohs(d);
	printf("%#6x\n", d);
	assert(d == c);
}
