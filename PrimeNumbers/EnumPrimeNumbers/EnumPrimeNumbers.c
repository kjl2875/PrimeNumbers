/*
 * EnumPrimeNumbers.c
 * 2017-11-04
 * PrimeNumbers 순서대로 출력
 * 최대 소수크기 한계점과 연산속도의 과제가 남아있음.
 * Windows Visual Studio 2015 Community Required
 */

#define IMPL_003

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

#if defined IMPL_001
	void impl(void);
#elif defined IMPL_002
	void impl(void);
#elif defined IMPL_003
	int impl(void);
	void uiHelp(void);
	errno_t saveFile(const unsigned long long int *const n, const int *const c, const unsigned long long int *const m, const unsigned long long int *const p);
	errno_t loadFile(const unsigned long long int *n, const int *c, const unsigned long long int *m, const unsigned long long int *p);
#endif


int main()
{
	int code = impl();
	return code;
}

#ifdef IMPL_003

int impl(void)
{
	FILE *fp;
	unsigned long long int n = 2;
	signed int c = 0;
	// size_t c = 0;
	// size_t i = 0; // error C3016: 'i': OpenMP 'for' 문의 인덱스 변수는 부호 있는 정수 계열 형식이어야 합니다.
	signed int i = 0;
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
				printf("%d Primes, Max number %llu\n", c, p[c - 1]);
				break;
			case 'e':
				inturrpt = 1;
				break;
			case 's':
				fflush(stdin);
				printf("c: %d\nm[%d]: %llu\np[%d]: %llu\n", c, c-1, m[c - 1], c-1, p[c - 1]);
				saveFile(&n, &c, m ,p);
				break;
			case 'l':
				fflush(stdin);
				printf("c: %d\nm[%d]: %llu\np[%d]: %llu\n", c, c - 1, m[c - 1], c - 1, p[c - 1]);
				loadFile(&n, &c, m, p);
				printf("c: %d\nm[%d]: %llu\np[%d]: %llu\n", c, c - 1, m[c - 1], c - 1, p[c - 1]);
				continue;
			case 'h':
				uiHelp();
				break;
			}
		}

		f = 1;
#pragma omp parallel for private(i)
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

	if (c == INT_MAX)
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

errno_t saveFile(const unsigned long long int *const n, const int *const c, const unsigned long long int *const m, const unsigned long long int *const p)
{
	char fpath[256];
	FILE *fp;
	int i;
	errno_t errno;

	printf("path: ");
	scanf_s("%s", fpath);
	printf("path: %s: ", fpath);

	switch (errno = fopen_s(&fp, fpath, "w"))
	{
	case 0:
		fprintf_s(fp, "%d %llu\n", *c, *n);

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

errno_t loadFile(const unsigned long long int *n, const int *c, const unsigned long long int *m, const unsigned long long int *p)
{
	char fpath[256];
	FILE *fp;
	int i;
	errno_t errno;

	printf("path: ");
	scanf_s("%s", fpath);
	printf("path: %s: ", fpath);

	switch (errno = fopen_s(&fp, fpath, "r"))
	{
	case 0:
		fscanf_s(fp, "%d %llu\n", c, n);

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
