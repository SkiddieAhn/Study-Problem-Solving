#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX 1001;

typedef struct subarray {
	int* list;
	int size;
}subarray;

// 순차 탐색  
int sequentialSearch(int* list, int n, double x) {
	int idx = 0;
	while (idx < n && list[idx] != x)
		idx++;
	if (idx < n)
		return 1;
	else if (idx == n)
		return 0;
}

// subarray 초기화 
void sub_init(subarray* s, int n) {
	s->size = 0;
	s->list = (int*)malloc(sizeof(int)*n);
	int i;
	for (i = 0; i < n; i++)
		s->list[i] = MAX;
}

// 평균 원소의 개수 찾기
int find_average_num(int A[], int n) {
	subarray* s = (subarray*)malloc(sizeof(subarray));

	int ThisSum;
	double ThisAverage;
	int average_num = 0;

	int i, j;
	for (i = 0; i < n; i++) {
		sub_init(s, n);
		ThisSum = 0;
		for (j = i; j < n; j++) {
			s->list[s->size++] = A[j];
			ThisSum = ThisSum + A[j];
			ThisAverage = (double)ThisSum / (double)(j - i + 1);
			
			if (ThisAverage / (int)ThisAverage == 1) {
				if (sequentialSearch(s->list, s->size, ThisAverage)) {
					average_num++;
				}
			}
		}
		free(s->list);
	}
	return 	average_num++;
}

int main() {
	int n = 0;
	scanf("%d", &n);

	int* array = (int*)malloc(sizeof(int) * n);

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &array[i]);
	}

	printf("%d\n", find_average_num(array, n));

	return 0;
}
