#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define max 30

typedef char element;
typedef struct {
	element array[max];
	int size;
}ArrayListType;
typedef ArrayListType * ArrayList_ptr;

// 리스트 초기화
void init(ArrayList_ptr list) {
	list->size = 0;
}
// 리스트 생성
ArrayList_ptr create() {
	return (ArrayList_ptr)calloc(1, sizeof(ArrayListType));
}

// 빈 리스트 확인
int is_empty(ArrayList_ptr list) {
	if (list->size == 0)
		return 1;
	else
		return 0;
}

// 풀 리스트 확인
int is_full(ArrayList_ptr list) {
	if (list->size == max)
		return 1;
	else
		return 0;
}

// 아이템 삽입
void insert_last(ArrayList_ptr list, element item) {
	if (!is_full(list)) {
		int pos = list->size;
		list->array[pos] = item;
		list->size++;
	}
	else
		printf("리스트가 꽉 차있습니다\n");
}

// 아이템 삭제 
void delete_last(ArrayList_ptr list) {
	if (!is_empty(list)) {
		list->size--;
	}
	else
		printf("리스트가 비어 있습니다\n");
}

int n; // 2xn개의 타일에서 'n'
int count; // 문양의 개수 
char tiles[500][31]; // 문양 모음

// recursion-call
int tile30(int i, int j, int ThisSum, ArrayList_ptr list) {
	// n=1
	if (n == 1) {
		tiles[count++][0] = '|'; // 1tile
		return count;
	}

	// n=2
	if (n == 2) {
		tiles[count][0] = '=';
		tiles[count++][1] = '='; // 1tile
		tiles[count][0] = '|';
		tiles[count++][1] = '|'; // 2tiles
		return count;
	}

	// first call 
	if (i == 0 && j == 0) {
		tile30(2, 1, 0, list);
		tile30(1, 2, 0, list);
		tile30(1, 1, 0, list);
	}
	ThisSum += i + j;
	int dist = n - ThisSum;

	// case 1
	if (i == 2 && j == 1) {
		insert_last(list, '=');
		insert_last(list, '=');
		insert_last(list, '|');

		if (dist >= 3) {
			// string incomplete -> call 
			tile30(2, 1, ThisSum, list);
			tile30(1, 2, ThisSum, list);
			delete_last(list);
			delete_last(list);
			delete_last(list);
		}
		else if (dist == 2) {
			// string complete -> return
			insert_last(list, '=');
			insert_last(list, '=');
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
		else if (dist == 1) {
			// string complete -> return
			insert_last(list, '|');
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
		else {
			// string complete -> return
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
	}
	// case 2
	else if (i == 1 && j == 2) {
		insert_last(list, '|');
		insert_last(list, '=');
		insert_last(list, '=');

		if (dist >= 3) {
			// string incomplete -> call 
			tile30(1, 2, ThisSum, list);
			tile30(1, 1, ThisSum, list);
			delete_last(list);
			delete_last(list);
			delete_last(list);
		}
		else if (dist == 2) {
			// string incomplete -> call
			tile30(1, 1, ThisSum, list);
			delete_last(list);
			delete_last(list);
			delete_last(list);
		}
		else if (dist == 1) {
			// string complete -> return
			insert_last(list, '|');
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
		else {
			// string complete -> return
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);
			count++;
			return 0;
		}
	}
	// case 3
	else if (i == 1 && j == 1) {
		insert_last(list, '|');
		insert_last(list, '|');

		if (dist >= 3) {
			// string incomplete -> call 
			tile30(2, 1, ThisSum, list);
			delete_last(list);
			delete_last(list);
		}
		else if (dist == 2) {
			// string complete -> return
			insert_last(list, '=');
			insert_last(list, '=');
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
		else if (dist == 1) {
			// string incomplete -> pass & return 
			delete_last(list);
			delete_last(list);
			return 0;
		}
		else {
			// string complete -> return
			for (int j = 0; j < list->size; j++) {
				tiles[count][j] = list->array[j];
			}
			delete_last(list);
			delete_last(list);

			count++;
			return 0;
		}
	}
	return count;
}

int one_array[1000001];
int two_array[1000001];
int thr_array[1000001];

// dynamic-programming (사용 x - stack overflow)
int tile(int i, int j, int ThisN) {
	// first call
	if (i == 0 && j == 0) {
		int r;
		for (r = 0; r <= n; r++) {
			one_array[r] = two_array[r] = thr_array[r] = -1;
		}
		one_array[ThisN] = tile(2, 1, n - 3) % 20201212;
		two_array[ThisN] = tile(1, 2, n - 3) % 20201212;
		thr_array[ThisN] = tile(1, 1, n - 2) % 20201212;

		count = ((one_array[ThisN] + two_array[ThisN] + thr_array[ThisN])) % 20201212;
		return count;
	}

	// base_case
	if (ThisN <= 2) {
		if (ThisN == 1 && (i == 1 && j == 1))
			return 0;
		else
			return 1;
	}

	// return cache
	if (i == 2 && j == 1) {
		if ((one_array[ThisN] != -1) && (two_array[ThisN] != -1)) {
			return one_array[ThisN] + two_array[ThisN];
		}
	}
	else if (i == 1 && j == 2) {
		if ((two_array[ThisN] != -1) && (thr_array[ThisN] != -1)) {
			return two_array[ThisN] + thr_array[ThisN];
		}
	}
	else if (i == 1 && j == 1) {
		if (one_array[ThisN] != -1) {
			return one_array[ThisN];
		}
	}

	// case 1
	if (i == 2 && j == 1) {
		one_array[ThisN] = tile(2, 1, ThisN - 3) % 20201212;
		two_array[ThisN] = tile(1, 2, ThisN - 3) % 20201212;
		return one_array[ThisN] + two_array[ThisN];
	}
	// case 2
	else if (i == 1 && j == 2) {
		two_array[ThisN] = tile(1, 2, ThisN - 3) % 20201212;
		thr_array[ThisN] = tile(1, 1, ThisN - 2) % 20201212;
		return two_array[ThisN] + thr_array[ThisN];
	}
	// case 3
	else if (i == 1 && j == 1) {
		one_array[ThisN] = tile(2, 1, ThisN - 3) % 20201212;
		return one_array[ThisN];
	}
}

// use two expressions  
// an = 2a(n-3)-a(n-6)+a(n-8)
// an+bn+cn=a(n-2)+3a(n-3)+a(n-5)-2a(n-6)+2a(n-8)
int tile_iter() {
	int infor[11] = { -1,-1,-1,1,1,1,2,2,2,3,4 };
	int* array = (int*)malloc(sizeof(int)*1000001);
	for (int i = 0; i <= 10; i++) {
		array[i] = infor[i];
	}
	for (int i = 11; i <= n; i++) {
		array[i] = ((2 * array[i - 3]) - array[i - 6] + array[i - 8])%20201212;
	}	
	count = (array[n - 2] + (3 * array[n - 3]) + array[n - 5] - (2 * array[n - 6]) + (2 * array[n - 8])) % 20201212;
	return count;
}                                                            

int main() {
	count = 0;
	scanf("%d", &n);

	// n이 30이하일 때 
	if (n <= 30) {
		ArrayList_ptr list = create();
		init(list);
		printf("%d\n", tile30(0, 0, 0, list));
		for (int i = 0; i < count; i++) {
			printf("%s\n", tiles[i]);
		}
	}

	// n이 30초과일 때 
	else {
		printf("%d\n", tile_iter());
	}


	return 0;
}
