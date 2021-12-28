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
	int a = 0; // list[a]~list[b]�� ���� ������ Ż �� ������ ������ �� �ʿ��� �����(�ð�), list[a]~list[b-1]�� ���� ������ ź �����
	int b = 1;
	int bus = 1;

	while (b < n){ // list[n-1]���� ������
		if (list[b] - list[a] <= max_diff) { // ���ð��� �ִ� ���ð� �����̴�.
			if ((b - a + 1) > c) { // ��� ���� �¼� ���� �Ҹ���
				bus++; // ���� �ø�
				a = b;	 // ���� ���� ó�� ����
			}
		}
		else { // ���ð��� �ִ� ���ð� �ʰ��̴�.
			bus++; // ���� �ø�
			if (bus > m) // �ִ� ���� �� �ʰ�
				break; // ���� ���� ���� 
			a = b; // ���� ���� ó�� ����
		}
		b++; // ��� �¿�, ���� ��� ���縦 ���� b�� 1����  
	}
	return bus;
}

int binary_search_compare(int* list, int first, int last, int fmd) {

	if ((last == 0) || (first == fmd)) // ó�� �� Ȥ��  ������ �� ó�� (������ ���), ���ǹ����� ���������� fisrt=last��
		return first; // ������ ������ ���� ���� ���ۿ� ���� 

	int mid = (first + last) / 2;

	int bus_mid = bus_num(list, mid); // �ִ� ���ð�(max_diff)�� mid�� ��, bus��

	if (mid == 0) { // first:0, last:1�̾ mid�� 0�̸� 'Main Part'�� ������ �Ұ��� -> ���� ó�� 
		if (bus_mid <= m) // max_diff�� 0�� �� ���� ���� -> 0�� ������ �ִ� ���ð� 
			return 0;
		else 
			return 1;
	}

	// Main Part
	if (bus_mid <= m) { // max_diff�� 0�� �ƴ� mid�� ��, bus<=m [���� ���� ����(���ų� ����)]
		if (bus_num(list, mid - 1) > m) //  max_diff�� mid�� ��, bus>m [�ٷ� ���� �� ���� �Ҹ���]
			return mid; // best_time�� mid

		else //  [�ٷ� ���� �� ���� ����]
			binary_search_compare(list, first, mid - 1, fmd); // '���� ���� �� �ϳ�'���� ������ 
	}
	else // max_diff�� 0�� �ƴ� mid�� ��, bus>m [���� ���� �Ҹ���]
		binary_search_compare(list, mid + 1, last, fmd); // '���� ���� �� �ϳ�'���� ������

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

	// make first max_diff (ù ��° �ִ� ���ð�(�ִ� �����)) 
	int fmd = 0;
	int tmp = 0;
	int idx = 0; // index of time_list 
	int M = m; // temp_m

	if ((n % c) == 0) { // n=m*c, n<m*c (n = k*c)
		if ((m * c - n) >= c) // ----- (m-��) buses can go 
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
		if ((m * c - n) >= c) // ----- (m-��) buses can go 
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
	int best_wait = binary_search_compare(time_list,0, fmd, fmd); // (����Ʈ,first,last,fmd)
	printf("%d", best_wait);
	
	return 0;
}
