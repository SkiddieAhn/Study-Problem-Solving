#include <stdio.h>
#include <stdlib.h>

// k+1-�κ����� ��� 
void print_kplus1(int * kset, int n, int k) {
	int* out = (int*)malloc(sizeof(int)*n + 1); // 1~n �� ��µ� ���� 1ó��
	int num = 0; // for-if���� ������ Ƚ��  

	// ��µ� ���� 1ó�� 
	int t;
	for (t = 1; t <= k; t++) {
		out[kset[t]] = 1;
	}

	int i;
	for (i = 1; i <= n; i++) {
		// ��� �� �� �ε����� �Բ� ��� ��Ŵ 
		if (out[i] != (num + 1)) {
			out[i] = ++num; // ��� �� �� �ε����� num+1ó�� 

			// k+1-�κ����� ���� ��� 
			for (t = 1; t <= n; t++) {
				if (out[t] == num) {
					printf("%02d",t);
				}
			}
			// num�� ���� ���� ���ΰ� ������ (������ ����� ����x) 
			if (num != n - k) {
				printf(" ");
			}

			// ���󺹱� (ó�� ��µ� �ε����� num+1 ó��)
			for (t = 1; t <= k; t++) {
				out[kset[t]] = num + 1;
			}
		}
	}
}

// �� �پ� �κ����� ���� ���  
int subset(int n, int k) {
	// �ƹ� �͵� ���� ���� -> ������ -> ��� �� ���� ���� 
	if (k == 0) {
		printf("00 ");
		// k+1-�κ����� ��� 
		int* kplus1 = (int*)malloc(sizeof(int) * 1);
		int i;
		for (i = 1; i <= n; i++) {
			if (i < n)
				printf("%02d ", i);
			else
				printf("%02d", i);
		}
		printf("\n");
		return 0;
	}

	// ����� �κ������� ��� �迭 
	int* kset = (int*)malloc(sizeof(int)*(k + 1));
	int i;

	// ù ��° ����� �κ����� ���� 
	// kset[1]=1, kset[2]=2, ... kset[k]=k �� ��ġ 
	// ex) (n,k)=(6,4) => 1|2|3|4 �迭�� ����
	for (i = 1; i <= k; i++)
		kset[i] = i;

	int finish = 0; // �κ����� ����� ������ finish->1
	while (!finish) {
		// k�κ����� ��� 
		for (i = 1; i <= k; i++) {
			printf("%02d", kset[i]);
		}
		printf(" ");
		// k+1-�κ����� ��� 
		print_kplus1(kset, n, k);
		printf("\n");

		// kset[idx]�� �ִ�ġ���� �˻� 
		// �ִ�ġ -> kset[--idx]�� �ִ�ġ���� �˻� 
		// ex) idx=4, 1|2|3|'6' �ִ�ġ-> idx=3, 1|2|'3'|6 �ִ�ġ �ƴ�
		int idx;
		for (idx = k; kset[idx] == n - k + idx; --idx) {
			// ù ��° ���ҵ� �ִ�ġ�� -> ��� ��µ� 
			// ex)idx=1, 3|4|5|6 <������ ��� �Ϸ�>
			if (idx == 1) {
				finish = 1;
				break;
			}
		}
		// ����� ������ �ʾ����� ���� 
		if (!finish) {
			// kset[idx]�� 1������ ������Ʈ ex) idx=3, 1|2|'3'|6 -> 1|2|'4'|6
			kset[idx]++;
			// idx�� �������� ���� ���ҵ鵵 ������Ʈ ex) idx=3, 1|2|'4'|6 <'4' �������� ���� ���ҵ� 1�� �߰�> -> 1|2|4|'5'
			for (i = idx + 1; i <= k; i++)
				kset[i] = kset[i - 1] + 1;
		}
	}
}


int main()
{
	int n, k;

	// n �Է� �ޱ�
	scanf("%d", &n);

	// k �Է� �ޱ�
	scanf("%d", &k);

	// �κ����� ��� ���� Ǯ��
	subset(n, k);
	
	return 0;
}
