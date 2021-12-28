#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define convert(value) value < 1 ? 1:0 // 0->1 , 1->0 convert 

void click(bool* lamp, int i, int n) {
	/*
	첫 번째 스위치 클릭 -> i,i+1번째 전등 상태 변경
	마지막 스위치 클릭 -> i-1,i번째 전등 상태 변경
	나머지는 i-1,i,i+1번째 전등 상태 변경
	*/
	if (i != 0)
		lamp[i - 1] = convert(lamp[i - 1]);
	if (i != n - 1)
		lamp[i + 1] = convert(lamp[i + 1]);
	lamp[i] = convert(lamp[i]);
}

int switch_control(bool* lamp, bool* lamp_temp, int n) {
	// 스위치 클릭 횟수 (0번 스위치 click, 0번 스위치 non-click)  
	int clk, nclk;
	clk = nclk = 0;

	// 전등이 모두 꺼졌는지 확인하는 변수 (0번 스위치 click, 0번 스위치 non-click) 
	int check, n_check;

	// 0번 스위치 non-click
	for (int i = 1; i < n; i++) {
		if (lamp[i - 1] != 0) {
			click(lamp, i, n);
			nclk++;
		}
	}
	n_check = lamp[n - 1];

	// 0번 스위치 click
	click(lamp_temp, 0, n);
	clk++;
	for (int i = 1; i < n; i++) {
		if (lamp_temp[i - 1] != 0) {
			click(lamp_temp, i, n);
			clk++;
		}
	}
	check = lamp_temp[n - 1];

	// 전등이 모두 꺼졌는지 확인 -> 클릭 횟수 반환 
	if (check == 0 && n_check == 0)
		return clk < nclk ? clk : nclk;
	else if (check == 0)
		return clk;
	else if (n_check == 0)
		return nclk;
	else
		return 0;
}

int main() {
	int n = 0; // 전등의 수 
	scanf("%d", &n);

	bool* lamp = (bool*)malloc(sizeof(bool)*n); // 전등 상태 배열 
	bool* lamp_temp = (bool*)malloc(sizeof(bool)*n); // Temp 배열  

	// 전등 상태 입력 받기 
	for (int i = 0; i < n; i++) {
		scanf("%d", &lamp[i]);
		lamp_temp[i] = lamp[i];
	}

	// 모든 전등을 끄기 위한 클릭 횟수 출력 
	int num = switch_control(lamp, lamp_temp, n);
	if (num)
		printf("%d\n",num);
	else
		printf("impossible\n");

	return 0;
}

