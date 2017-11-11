/*
 * EnumPrimeNumbers.c
 * 2017-11-04
 * PrimeNumbers 순서대로 출력
 * 최대 소수크기 한계점과 연산속도의 과제가 남아있음.
 * Windows Visual Studio 2015 Community Required
 */

#define IMPL_001_1

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

#ifdef IMPL_003
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>

//#define MEMORY_MAX_ADDRESS ULLONG_MAX
#define MEMORY_MAX_ADDRESS (1024*1024*1024)
#define PREOGRAM_VERSION "1.0"
#endif

#ifdef IMPL_001_1
#include <stdio.h>
#include <stdlib.h>
#endif

#if defined IMPL_001
	void impl(void);
#elif defined IMPL_002
	void impl(void);
#elif defined IMPL_003
	int impl(void);
	void uiHelp(void);
	errno_t saveFile(const unsigned long long int *const n, const unsigned long long int *const c, const unsigned long long int *const m, const unsigned long long int *const p);
	errno_t loadFile(const unsigned long long int *n, const unsigned long long int *c, const unsigned long long int *m, const unsigned long long int *p);
#elif defined IMPL_001_1
	int impl(void);
#endif


int main()
{
	int code = impl();
	return code;
}

#ifdef IMPL_001_1
	#define NUM_FIELD_SIZE (1024)
	#define	PNUM_FIELD_SIZE (1024 * 1024 * 1024)

	typedef unsigned long long int numberic;

	int impl(void)
	{
		numberic offset = 2;
		numberic *numField;
		numberic *pnumField, *pnumIdx;

		size_t i;
		size_t pnumCount = 0;
		int fStop = 0;

		numField = malloc(sizeof(numberic) * NUM_FIELD_SIZE);
		pnumField = malloc(sizeof(numberic) * PNUM_FIELD_SIZE);
		pnumIdx = malloc(sizeof(numberic) * PNUM_FIELD_SIZE);

		if (numField == NULL || pnumField == NULL || pnumIdx == NULL)
		{
			printf("Error: out of memory.\n");
			if (numField != NULL) free(numField);
			if (pnumField != NULL) free(pnumField);
			return 1;
		}

		while (!fStop)
		{
			for (i = 0; i < NUM_FIELD_SIZE; i++)
				numField[i] = i + offset;

			for (i = 0; i < pnumCount; i++)
			{
				pnumIdx[i] -= NUM_FIELD_SIZE;
				while (pnumIdx[i] < NUM_FIELD_SIZE)
				{
					numField[pnumIdx[i]] = 0;
					pnumIdx[i] += pnumField[i];
				}
			}

			for (i = 0; i < NUM_FIELD_SIZE; i++)
			{
				if (numField[i] == 0)
					continue;

				printf("%llu\n", numField[i]);

				pnumField[pnumCount] = numField[i];
				pnumIdx[pnumCount] = i + numField[i] + numField[i];

				while (pnumIdx[pnumCount] < NUM_FIELD_SIZE)
				{
					numField[pnumIdx[pnumCount]] = 0;
					pnumIdx[pnumCount] += pnumField[pnumCount];
				}

				if (++pnumCount == PNUM_FIELD_SIZE)
				{
					fStop = 1;
					break;
				}
			}

			offset += NUM_FIELD_SIZE;
		}

		free(numField);
		free(pnumField);
		free(pnumIdx);
		
		return 0;
	}
#endif

#ifdef IMPL_003

int impl(void)
{
	FILE *fp;
	unsigned long long int n = 2;
	size_t c = 0;
	size_t i = 0;
	unsigned long long int *m, *p;
	int f, inturrpt = 0;
	errno_t errno;

	m = malloc(sizeof(unsigned long long int) * MEMORY_MAX_ADDRESS - 1);
	p = malloc(sizeof(unsigned long long int) * MEMORY_MAX_ADDRESS);

	if (INT_MAX < MEMORY_MAX_ADDRESS)
	{
		printf("Error: MEMORY_ADDRESS_OVERFLOW: MAX_VALUE: %d\n", INT_MAX);
		return 1;
	}
	
	if (m == NULL || p == NULL)
	{
		printf("Error: Out of memory\n");
		if( m != NULL ) free(m);
		return 1;
	}

	uiHelp();

	while (c < MEMORY_MAX_ADDRESS && inturrpt == 0)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'c':
				printf("%llu Primes, Max number %llu\n", c, p[c - 1]);
				break;
			case 'e':
				inturrpt = 1;
				break;
			case 's':
				fflush(stdin);
				printf("c: %llu\nm[%llu]: %llu\np[%llu]: %llu\n", c, c-1, m[c - 1], c-1, p[c - 1]);
				saveFile(&n, &c, m ,p);
				break;
			case 'l':
				fflush(stdin);
				printf("c: %llu\nm[%llu]: %llu\np[%llu]: %llu\n", c, c - 1, m[c - 1], c - 1, p[c - 1]);
				loadFile(&n, &c, m, p);
				printf("c: %llu\nm[%llu]: %llu\np[%llu]: %llu\n", c, c - 1, m[c - 1], c - 1, p[c - 1]);
				continue;
			case 'h':
				uiHelp();
				break;
			}
		}

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
		}

		n++;
	}

	if (c == UINT_MAX)
		printf("Prime check number is maximun: %d\n", c);

	printf("%llu\n", p[c-1]);
	saveFile(&n, &c, m, p);

	free(m);
	free(p);

	return 0;
}

void uiHelp(void)
{
	printf("Enum PrimeNumbers v%s\n", PREOGRAM_VERSION);
	printf("Check number: 'c'\n");
	printf("Save to file: 's'\n");
	printf("Load from file: 'l'\n");
	printf("Exit program: 'e'\n");
	printf("Program is running...\n");
}

errno_t saveFile(const unsigned long long int *const n, const unsigned long long int *const c, const unsigned long long int *const m, const unsigned long long int *const p)
{
	char fpath[256];
	FILE *fp;
	size_t i;
	errno_t errno;

	printf("path: ");
	scanf_s("%s", fpath);
	printf("path: %s: ", fpath);

	switch (errno = fopen_s(&fp, fpath, "w"))
	{
	case 0:
		fprintf_s(fp, "%llu %llu\n", *c, *n);

		for (i = 0; i < *c; i++)
			fprintf_s(fp, "%llu ", m[i]);
		fputc('\n', fp);

		for (i = 0; i < *c; i++)
			fprintf_s(fp, "%llu ", p[i]);

		printf("saved: %llu\n", p[*c - 1]);

		if (fclose(fp) != 0)
			printf("error: close file fail\n");

		break;
	default:
		printf("error: save fail(%d)\n", errno);
	}

	return errno;
}

errno_t loadFile(const unsigned long long int *n, const unsigned long long int *c, const unsigned long long int *m, const unsigned long long int *p)
{
	char fpath[256];
	FILE *fp;
	size_t i;
	errno_t errno;

	printf("path: ");
	scanf_s("%s", fpath);
	printf("path: %s: ", fpath);

	switch (errno = fopen_s(&fp, fpath, "r"))
	{
	case 0:
		fscanf_s(fp, "%llu %llu\n", c, n);

		for (i = 0; i < *c; i++)
			fscanf_s(fp, "%llu ", &m[i]);

		for (i = 0; i < *c; i++)
			fscanf_s(fp, "%llu ", &p[i]);

		printf("loaded: %llu\n", p[*c - 1]);

		if (fclose(fp) != 0)
			printf("error: close file fail\n");

		break;
	default:
		printf("error: load fail(%d)\n", errno);
	}

	return errno;
}
#endif

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
