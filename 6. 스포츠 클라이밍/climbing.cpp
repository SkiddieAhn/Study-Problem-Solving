#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#pragma warning(disable:4996)

typedef struct Infor {
	int mul; // ������ �� 
	int sum; // ������ ��
	int num; // ������ ���ȣ
}Infor;

Infor sorted[MAX];

// �պ����� (�������Ŀ� ����) 
void merge(Infor* list, int left, int mid, int right, int code) {
	int i, j, k;
	i = left; // ������ Part�� ���� ��ġ
	j = mid + 1; // ���� Part�� ���� ��ġ
	k = left; // ���ĵ� ����Ʈ�� ���� ��ġ 

	// ���� ������� �պ� (������ or ���� Part�� ���� ����� ������)
	while (i <= mid && j <= right) {
		if (code == 0) { // mul�� �������� �պ�
			if (list[i].mul <= list[j].mul)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
		else if (code == 1) { // sum�� �������� �պ�
			if (list[i].sum <= list[j].sum)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
		else { // num�� �������� �պ�
			if (list[i].num <= list[j].num)
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
	}
	// ���� ��� �ϰ� ���� (������ Part)
	if (i > mid) {
		for (int idx = j; idx <= right; idx++)
			sorted[k++] = list[idx];
	}
	// ���� ��� �ϰ� ���� (���� Part)
	else {
		for (int idx = i; idx <= mid; idx++)
			sorted[k++] = list[idx];
	}
	// sorted �迭 ������ list�� ����
	for (int idx = left; idx <= right; idx++)
		list[idx] = sorted[idx];
}

void merge_sort(Infor* list, int left, int right, int code) {
	int mid;
	// �迭�� ũ�Ⱑ 2�̻��� �� ���� 
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid, code);
		merge_sort(list, mid + 1, right, code);
		merge(list, left, mid, right, code);
	}
}

int main() {
	// ������ ���
	int n = 0;
	scanf("%d", &n);

	int* b = (int*)malloc(sizeof(int)*n); // ������ ���ȣ
	int* p = (int*)malloc(sizeof(int)*n); // ���� ���� ����
	int* q = (int*)malloc(sizeof(int)*n); // ���ǵ� ���� ����
	int* r = (int*)malloc(sizeof(int)*n); // ������ ���� ����

	// �Է� 
	for (int i = 0; i < n; i++)
		scanf("%d %d %d %d", &(b[i]), &(p[i]), &(q[i]), &(r[i]));

	// infor �迭 ����
	Infor* infor = (Infor*)malloc(sizeof(Infor)*n);
	for (int i = 0; i < n; i++) {
		infor[i].mul = p[i] * q[i] * r[i];
		infor[i].sum = p[i] + q[i] + r[i];
		infor[i].num = b[i];
	}

	// ���ȣ�� �������� infor�迭 ����
	merge_sort(infor, 0, n - 1, 2);

	// ������ ���� �������� infor�迭 ����
	merge_sort(infor, 0, n - 1, 1);

	// ������ ���� �������� infor�迭 ����
	merge_sort(infor, 0, n - 1, 0);

	// ��,��,�� ���� ���
	printf("%d %d %d\n", infor[0].num, infor[1].num, infor[2].num);
}
