#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#pragma warning(disable:4996)

typedef struct Infor {
	int mul; // 점수의 곱 
	int sum; // 점수의 합
	int num; // 선수의 등번호
}Infor;

Infor sorted[MAX];

// 합병정렬 (안정정렬에 속함) 
void merge(Infor* list, int left, int mid, int right, int code) {
	int i, j, k;
	i = left; // 오른쪽 Part의 시작 위치
	j = mid + 1; // 왼쪽 Part의 시작 위치
	k = left; // 정렬될 리스트의 시작 위치 

	// 작은 순서대로 합병 (오른쪽 or 왼쪽 Part가 전부 복사될 때까지)
	while (i <= mid && j <= right) {
		if (code == 0) { // mul을 기준으로 합병
			if (list[i].mul <= list[j].mul)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
		else if (code == 1) { // sum을 기준으로 합병
			if (list[i].sum <= list[j].sum)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
		else { // num을 기준으로 합병
			if (list[i].num <= list[j].num)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
	}
	// 남은 요소 일괄 복사 (오른쪽 Part)
	if (i > mid) {
		for (int idx = j; idx <= right; idx++)
			sorted[k++] = list[idx];
	}
	// 남은 요소 일괄 복사 (왼쪽 Part)
	else {
		for (int idx = i; idx <= mid; idx++)
			sorted[k++] = list[idx];
	}
	// sorted 배열 내용을 list로 복사
	for (int idx = left; idx <= right; idx++)
		list[idx] = sorted[idx];
}

void merge_sort(Infor* list, int left, int right, int code) {
	int mid;
	// 배열의 크기가 2이상일 때 동작 
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid, code);
		merge_sort(list, mid + 1, right, code);
		merge(list, left, mid, right, code);
	}
}

int main() {
	// 선수의 명수
	int n = 0;
	scanf("%d", &n);

	int* b = (int*)malloc(sizeof(int)*n); // 선수의 등번호
	int* p = (int*)malloc(sizeof(int)*n); // 리드 종목 점수
	int* q = (int*)malloc(sizeof(int)*n); // 스피드 종목 점수
	int* r = (int*)malloc(sizeof(int)*n); // 볼더링 종목 점수

	// 입력 
	for (int i = 0; i < n; i++)
		scanf("%d %d %d %d", &(b[i]), &(p[i]), &(q[i]), &(r[i]));

	// infor 배열 생성
	Infor* infor = (Infor*)malloc(sizeof(Infor)*n);
	for (int i = 0; i < n; i++) {
		infor[i].mul = p[i] * q[i] * r[i];
		infor[i].sum = p[i] + q[i] + r[i];
		infor[i].num = b[i];
	}

	// 등번호를 기준으로 infor배열 정렬
	merge_sort(infor, 0, n - 1, 2);

	// 점수의 합을 기준으로 infor배열 정렬
	merge_sort(infor, 0, n - 1, 1);

	// 점수의 곱을 기준으로 infor배열 정렬
	merge_sort(infor, 0, n - 1, 0);

	// 금,은,동 선수 출력
	printf("%d %d %d\n", infor[0].num, infor[1].num, infor[2].num);
}
