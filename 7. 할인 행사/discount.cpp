#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define ull unsigned long long

// 배열의 두 요소의 위치를 바꿔주는 함수
void swap_elements(int* list, int index1, int index2) {
	int temp = list[index1];
	list[index1] = list[index2];
	list[index2] = temp;
}

// 퀵 정렬에서 사용되는 partition 함수
int partition(int* list, int start, int end) {

	int i, b;
	i = b = start;
	int p = end;

	while (i < p) {
		if (list[i] >= list[p]) {
			swap_elements(list, i, b);
			b += 1;
		}
		i += 1;
	}
	swap_elements(list, b, p);
	p = b;

	return p;
}

// 퀵 정렬 
int quicksort(int* list, int start, int end) {
	if (end - start < 1)
		return 0;

	int p = partition(list, start, end);
	quicksort(list, start, p - 1);
	quicksort(list, p + 1, end);
}

// 최소 가격 찾기
ull find_best(int* array, int n, int x) {
	ull* dptable = (ull*)malloc(sizeof(ull)*n); // i개의 상품을 살 때 최소 가격 모음 (i=1,2,3,...n)

	// dptable 초기 세팅
	dptable[0] = array[0] * (100 - x) / 100;
	dptable[1] = (array[0] + array[1]) * (100 - x) / 100;
	ull candi_1 = array[0] + array[1];
	ull candi_2 = (array[0] + array[1] + array[2]) * (100 - x) / 100;
	dptable[2] = (candi_1 < candi_2) ? candi_1 : candi_2;

	// dptable 활용해서 최소 가격 찾기 
	if (n > 3) {
		ull candi1, candi2, candi2_1,candi2_2;
		for (int i = 3; i < n; i++) {
			candi1 = dptable[i - 1] + (array[i] * (100 - x) / 100);
			candi2_1 = dptable[i - 3] + array[i - 2] + array[i - 1];
			candi2_2 = dptable[i - 3] + (array[i-2] + array[i-1] + array[i]) * (100 - x) / 100;
			candi2 = (candi2_1 < candi2_2) ? candi2_1 : candi2_2;
			dptable[i] = (candi1 < candi2) ? candi1 : candi2;
		}
		return dptable[n - 1]; // n개의 상품을 살 때 최소 가격
	}
	else
		return dptable[2]; // 3개의 상품을 살 때 최소 가격
}

int main(void) {
	int n, x; // 상품의 개수, 할인율
	scanf("%d %d", &n, &x);
	int* array = (int*)malloc(sizeof(int)*n); // 상품의 가격 모음 

	// 상품의 가격 입력 
	for (int i = 0; i < n; i++) {
		scanf("%d", &(array[i]));
	}

	// 케이스에 따라 처리
	if (n <= 0) 
		printf("%d\n", 0);

	else if (n == 1) 
		printf("%d\n", array[0] * (100 - x) / 100);

	else if(n==2) 
		printf("%d\n", (array[0] + array[1]) * (100 - x) / 100);

	else {
		quicksort(array, 0, n - 1); // 내림차순 
		ull sum_price = find_best(array, n, x); // n개의 상품을 살 때 최소 가격
		printf("%llu\n", sum_price);
	}

	return 0;
}
