#include <stdio.h>
#include <stdlib.h>

// k+1-부분집합 출력 
void print_kplus1(int * kset, int n, int k) {
	int* out = (int*)malloc(sizeof(int)*n + 1); // 1~n 중 출력된 것은 1처리
	int num = 0; // for-if문이 동작한 횟수  

	// 출력된 것은 1처리 
	int t;
	for (t = 1; t <= k; t++) {
		out[kset[t]] = 1;
	}

	int i;
	for (i = 1; i <= n; i++) {
		// 출력 안 된 인덱스와 함께 출력 시킴 
		if (out[i] != (num + 1)) {
			out[i] = ++num; // 출력 안 된 인덱스도 num+1처리 

			// k+1-부분집합 원소 출력 
			for (t = 1; t <= n; t++) {
				if (out[t] == num) {
					printf("%02d",t);
				}
			}
			// num에 따라 띄어쓰기 여부가 결정됨 (마지막 출력은 적용x) 
			if (num != n - k) {
				printf(" ");
			}

			// 원상복귀 (처음 출력된 인덱스는 num+1 처리)
			for (t = 1; t <= k; t++) {
				out[kset[t]] = num + 1;
			}
		}
	}
}

// 한 줄씩 부분집합 원소 출력  
int subset(int n, int k) {
	// 아무 것도 뽑지 않음 -> 공집합 -> 출력 후 빠져 나옴 
	if (k == 0) {
		printf("00 ");
		// k+1-부분집합 출력 
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

	// 출력할 부분집합이 담길 배열 
	int* kset = (int*)malloc(sizeof(int)*(k + 1));
	int i;

	// 첫 번째 출력할 부분집합 생성 
	// kset[1]=1, kset[2]=2, ... kset[k]=k 로 매치 
	// ex) (n,k)=(6,4) => 1|2|3|4 배열이 생성
	for (i = 1; i <= k; i++)
		kset[i] = i;

	int finish = 0; // 부분집합 출력이 끝나면 finish->1
	while (!finish) {
		// k부분집합 출력 
		for (i = 1; i <= k; i++) {
			printf("%02d", kset[i]);
		}
		printf(" ");
		// k+1-부분집합 출력 
		print_kplus1(kset, n, k);
		printf("\n");

		// kset[idx]가 최대치인지 검사 
		// 최대치 -> kset[--idx]가 최대치인지 검사 
		// ex) idx=4, 1|2|3|'6' 최대치-> idx=3, 1|2|'3'|6 최대치 아님
		int idx;
		for (idx = k; kset[idx] == n - k + idx; --idx) {
			// 첫 번째 원소도 최대치임 -> 모두 출력됨 
			// ex)idx=1, 3|4|5|6 <사전식 출력 완료>
			if (idx == 1) {
				finish = 1;
				break;
			}
		}
		// 출력이 끝나지 않았으면 진행 
		if (!finish) {
			// kset[idx]를 1높여서 업데이트 ex) idx=3, 1|2|'3'|6 -> 1|2|'4'|6
			kset[idx]++;
			// idx를 기준으로 뒤의 원소들도 업데이트 ex) idx=3, 1|2|'4'|6 <'4' 기준으로 뒤의 원소들 1씩 추가> -> 1|2|4|'5'
			for (i = idx + 1; i <= k; i++)
				kset[i] = kset[i - 1] + 1;
		}
	}
}


int main()
{
	int n, k;

	// n 입력 받기
	scanf("%d", &n);

	// k 입력 받기
	scanf("%d", &k);

	// 부분집합 출력 문제 풀기
	subset(n, k);
	
	return 0;
}
