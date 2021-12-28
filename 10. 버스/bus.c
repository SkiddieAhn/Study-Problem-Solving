#include <stdio.h>
#include <stdlib.h>

int n, m, c;

void swap_elements(int* list, int index1, int index2) {
	int temp = list[index1];
	list[index1] = list[index2];
	list[index2] = temp;
}

int partition(int* list, int start, int end) {
	int i, b;
	i = b = start;
	int p = end;

	while (i < p) {
		if (list[i] <= list[p]) {
			swap_elements(list, i, b);
			b += 1;
		}
		i += 1;
	}
	swap_elements(list, b, p);
	p = b;

	return p;
}

int quick_sort(int* list, int start, int end) {
	if (end - start < 1)
		return 0;

	int p = partition(list, start, end);
	quick_sort(list, start, p - 1);
	quick_sort(list, p + 1, end);
}

int bus_num(int* list, int max_diff) {
	int a = 0; // list[a]~list[b]는 현재 버스에 탈 수 있을지 조사할 때 필요한 사람들(시각), list[a]~list[b-1]은 현재 버스에 탄 사람들
	int b = 1;
	int bus = 1;

	while (b < n){ // list[n-1]까지 존재함
		if (list[b] - list[a] <= max_diff) { // 대기시간이 최대 대기시간 이하이다.
			if ((b - a + 1) > c) { // 사람 수가 좌석 수에 불만족
				bus++; // 버스 늘림
				a = b;	 // 다음 버스 처리 시작
			}
		}
		else { // 대기시간이 최대 대기시간 초과이다.
			bus++; // 버스 늘림
			if (bus > m) // 최대 버스 수 초과
				break; // 버스 조사 끝냄 
			a = b; // 다음 버스 처리 시작
		}
		b++; // 사람 태움, 다음 경우 조사를 위해 b를 1증가  
	}
	return bus;
}

int binary_search_compare(int* list, int first, int last, int fmd) {

	if ((last == 0) || (first == fmd)) // 처음 값 혹은  마지막 값 처리 (최종의 경우), 조건문에서 생략했지만 fisrt=last임
		return first; // 최종의 경우까지 오면 나올 수밖에 없음 

	int mid = (first + last) / 2;

	int bus_mid = bus_num(list, mid); // 최대 대기시간(max_diff)이 mid일 때, bus값

	if (mid == 0) { // first:0, last:1이어서 mid가 0이면 'Main Part'의 연산이 불가능 -> 따로 처리 
		if (bus_mid <= m) // max_diff가 0일 때 조건 만족 -> 0이 최적의 최대 대기시간 
			return 0;
		else 
			return 1;
	}

	// Main Part
	if (bus_mid <= m) { // max_diff가 0이 아닌 mid일 때, bus<=m [현재 조건 만족(적거나 같음)]
		if (bus_num(list, mid - 1) > m) //  max_diff가 mid일 때, bus>m [바로 전일 때 조건 불만족]
			return mid; // best_time은 mid

		else //  [바로 전일 때 조건 만족]
			binary_search_compare(list, first, mid - 1, fmd); // '이전 값들 중 하나'에서 재조사 
	}
	else // max_diff가 0이 아닌 mid일 때, bus>m [현재 조건 불만족]
		binary_search_compare(list, mid + 1, last, fmd); // '다음 값들 중 하나'에서 재조사

}


int main() {
	int i; // for iteration

	// input processing
	scanf("%d %d %d", &n, &m, &c);

	// find error
	if (n < c) {
		printf("[n<c] error");
		return 0;
	}
	if (m * c < n) {
		printf("[mc<n] error");
		return 0;
	}
	// end
	if (n <= 1 || c == 1) {
		printf("0");
		return 0;
	}

	int* time_list = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		scanf("%d", &time_list[i]);

	// sorting
	quick_sort(time_list, 0, n - 1);

	// make first max_diff (첫 번째 최대 대기시간(최대 대기차)) 
	int fmd = 0;
	int tmp = 0;
	int idx = 0; // index of time_list 
	int M = m; // temp_m

	if ((n % c) == 0) { // n=m*c, n<m*c (n = k*c)
		if ((m * c - n) >= c) // ----- (m-α) buses can go 
			M = n / c;
		for (i = 0; i < M; i++) {
			tmp = time_list[idx + (c - 1)] - time_list[idx];
			idx += c;
			//find max
			if (tmp >= fmd)
				fmd = tmp;
		}
	}
	else { // n<m*c (n != k*c)
		if ((m * c - n) >= c) // ----- (m-α) buses can go 
			M = (n / c) + 1;
		for (i = 0; i < M; i++) {
			if (i == M - 1) {
				tmp = time_list[idx + ((n % c) - 1)] - time_list[idx];
			}
			else {
				tmp = time_list[idx + (c - 1)] - time_list[idx];
				idx += c;
			}
			//find max
			if (tmp >= fmd)
				fmd = tmp;
		}
	}

	// find best max_diff 
	int best_wait = binary_search_compare(time_list,0, fmd, fmd); // (리스트,first,last,fmd)
	printf("%d", best_wait);
	
	return 0;
}
