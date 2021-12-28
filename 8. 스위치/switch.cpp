#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define convert(value) value < 1 ? 1:0 // 0->1 , 1->0 convert 

void click(bool* lamp, int i, int n) {
	/*
	ù ��° ����ġ Ŭ�� -> i,i+1��° ���� ���� ����
	������ ����ġ Ŭ�� -> i-1,i��° ���� ���� ����
	�������� i-1,i,i+1��° ���� ���� ����
	*/
	if (i != 0)
		lamp[i - 1] = convert(lamp[i - 1]);
	if (i != n - 1)
		lamp[i + 1] = convert(lamp[i + 1]);
	lamp[i] = convert(lamp[i]);
}

int switch_control(bool* lamp, bool* lamp_temp, int n) {
	// ����ġ Ŭ�� Ƚ�� (0�� ����ġ click, 0�� ����ġ non-click)  
	int clk, nclk;
	clk = nclk = 0;

	// ������ ��� �������� Ȯ���ϴ� ���� (0�� ����ġ click, 0�� ����ġ non-click) 
	int check, n_check;

	// 0�� ����ġ non-click
	for (int i = 1; i < n; i++) {
		if (lamp[i - 1] != 0) {
			click(lamp, i, n);
			nclk++;
		}
	}
	n_check = lamp[n - 1];

	// 0�� ����ġ click
	click(lamp_temp, 0, n);
	clk++;
	for (int i = 1; i < n; i++) {
		if (lamp_temp[i - 1] != 0) {
			click(lamp_temp, i, n);
			clk++;
		}
	}
	check = lamp_temp[n - 1];

	// ������ ��� �������� Ȯ�� -> Ŭ�� Ƚ�� ��ȯ 
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
	int n = 0; // ������ �� 
	scanf("%d", &n);

	bool* lamp = (bool*)malloc(sizeof(bool)*n); // ���� ���� �迭 
	bool* lamp_temp = (bool*)malloc(sizeof(bool)*n); // Temp �迭  

	// ���� ���� �Է� �ޱ� 
	for (int i = 0; i < n; i++) {
		scanf("%d", &lamp[i]);
		lamp_temp[i] = lamp[i];
	}

	// ��� ������ ���� ���� Ŭ�� Ƚ�� ��� 
	int num = switch_control(lamp, lamp_temp, n);
	if (num)
		printf("%d\n",num);
	else
		printf("impossible\n");

	return 0;
}

