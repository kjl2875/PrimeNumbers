/*
 * EnumPrimeNumbers.c
 * 2017-11-04
 * PrimeNumbers 순서대로 출력
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MEMORY_MAX_ADDRESS ULLONG_MAX

int main()
{
	size_t i = 0, n, idx;
	unsigned long long int *m;

	m = (unsigned long long int *)malloc(sizeof(unsigned long long int) * MEMORY_MAX_ADDRESS);
	if (m == NULL)
	{
		printf("Error: out of memory\n");
		return 1;
	}

	for (i = 0; i < MEMORY_MAX_ADDRESS; i++)
		m[i] = 2 + i;

	for (i = 0; i < MEMORY_MAX_ADDRESS; i++)
		if (m[i] != 0)
		{
			printf("%llu\n", m[i]);

			for (n = 1; ; n++)
			{
				idx = i + m[i] * n;

				if (idx < MEMORY_MAX_ADDRESS)
					m[idx] = 0;
				else
					break;
			}
		}

	free(m);
	return 0;
}