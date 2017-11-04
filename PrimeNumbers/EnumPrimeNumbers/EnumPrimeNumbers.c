/*
 * EnumPrimeNumbers.c
 * 2017-11-04
 * PrimeNumbers 순서대로 출력
 */

#define IMPL_002

#ifdef IMPL_001
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MEMORY_MAX_ADDRESS ULLONG_MAX
#endif

#ifdef IMPL_002
#include <stdio.h>
#include <stdlib.h>

//#define MEMORY_MAX_ADDRESS ULLONG_MAX
#define MEMORY_MAX_ADDRESS (1024*1024*1024)
#endif

void impl(void);

int main()
{
	impl();
	
	return 0;
}

#ifdef IMPL_002
void impl(void)
{
	unsigned long long int n = 2;
	size_t c = 0;
	size_t i = 0;
	unsigned long long int *m, *p;
	int f;

	m = malloc(sizeof(unsigned long long int) * MEMORY_MAX_ADDRESS);
	p = malloc(sizeof(unsigned long long int) * MEMORY_MAX_ADDRESS);

	while (c < MEMORY_MAX_ADDRESS)
	{
		f = 1;
		for (i = 0; i<c; i++)
			if (m[i] == n)
			{
				m[i] += p[i];
				f = 0;
			}

		if (f)
		{
			p[c] = n;
			m[c] = n + n;
			++c;
			printf("%llu\n", n);
		}

		n++;
	}
	
	free(m);
	free(p);
}
#endif

#ifdef IMPL_001
void impl(void)
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
}
#endif
