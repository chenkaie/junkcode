#include <stdio.h>
#include <stdlib.h>

#define N_ARRAY 10

void quicksort(int a[], int left, int right);

int main(void) {
	int a[N_ARRAY] = { 7, 3, 1, 9, -2, 0, 16, 3, 11, 4 };
	int i;

	for (i = 0; i < N_ARRAY; i++)
		printf("%5d",a[i]);
	printf("\n");
	quicksort(a, 0, N_ARRAY - 1);
	for (i = 0; i < N_ARRAY; i++)
		printf("%5d%s",a[i],i < N_ARRAY - 1 ? "":"\n");
	return 0;
}

static inline void swap(int a[], int idx1, int idx2) {
	int tmp = a[idx1]; a[idx1] = a[idx2]; a[idx2] = tmp;
}

/* pick up random number in [i, j] */
static inline int Random(int i, int j) {
	return (i + rand() % (j - i + 1));
}

void quicksort(int a[], int left, int right) {
	int last = left, i;

	if (left < right) {
		swap(a, left, Random(left, right));
		for (i = left + 1; i <= right; i++)
			if (a[i] < a[left])
				swap(a, ++last, i);
		swap(a,left,last);
		quicksort(a,left, last - 1);
		quicksort(a, last + 1, right);
	}
}

