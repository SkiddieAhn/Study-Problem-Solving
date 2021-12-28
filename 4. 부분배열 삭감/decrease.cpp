#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define max 100002

typedef struct {
	int key;
	int list_idx;
}helement;

typedef struct {
	helement heap[max];
	int heap_size; 
}HeapType;
typedef HeapType* HeapType_ptr;

// ���� �Լ�
HeapType_ptr hcreate() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void hinit(HeapType_ptr h) {
	h->heap_size = 0;
}

// ���� �Լ�
void insert_max_heap(HeapType_ptr h, helement item) {
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  
		i /= 2;
	}
	h->heap[i] = item; 
}

// ���� �Լ� 
helement delete_max_heap(HeapType_ptr h) {
	int parent, child;
	helement item, temp;
	item = h->heap[1]; 
	temp = h->heap[(h->heap_size)--]; 
	parent = 1;
	child = 2; 
	while (child <= h->heap_size) {
		if ((h->heap[parent * 2].key >= 0) && (h->heap[(parent * 2) + 1].key >= 0)) {
			if ((h->heap[parent * 2].key) > (h->heap[(parent * 2) + 1].key))
				child = parent * 2;
			else
				child = (parent * 2) + 1;
		}
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

typedef struct {
	int infor;
	int freq;
	int left;
	int right;
	bool check;
}element;

typedef struct {
	element array[max];
	int size;
}ArrayListType;
typedef ArrayListType * ArrayList_ptr;

// ����Ʈ ũ�� �ʱ�ȭ
void init(ArrayList_ptr list) {
	list->size = 0;
}

// ����Ʈ ����
ArrayList_ptr create() {
	return (ArrayList_ptr)malloc(sizeof(ArrayListType));
}

// �� ����Ʈ Ȯ��
int is_empty(ArrayList_ptr list) {
	if (list->size == 0)
		return 1;
	else
		return 0;
}

// Ǯ ����Ʈ Ȯ��
int is_full(ArrayList_ptr list) {
	if (list->size == max)
		return 1;
	else
		return 0;
}

// ������ ���� 
void insert(ArrayList_ptr list, element item) {
	if (!is_full(list)) {
		int	pos = list->size;
		list->array[pos] = item;
		list->size++;
	}
	else
		printf("����Ʈ�� �� ���ֽ��ϴ�\n");
}

// �ε����� ������ ���� (���x) 
void delete_idx(ArrayList_ptr list, int pos) {
	if (!is_empty(list)) {
		element tmp = list->array[pos];
		for (int i = pos + 1; i < list->size; i++)
			list->array[i - 1] = list->array[i];
		list->size--;
	}
	else
		printf("����Ʈ�� ��� �ֽ��ϴ�\n");
}

// ����Ʈ ��� (���x) 
void print_list(ArrayList_ptr list) {
	printf("\ninfor:");
	for (int i = 0; i < list->size; i++) {
		if (list->array[i].check) {
			printf("[%d(%d)] ", list->array[i].infor,i);
		}
	}
	printf("\nfreq:");
	for (int i = 0; i < list->size; i++) {
		if (list->array[i].check) {
			printf("[%d(%d)] ", list->array[i].freq,i);
		}
	}
}

// �κй迭 �谨 
int decrease(int* array, int n) {
	ArrayList_ptr list = create(); // ����Ʈ ����
	init(list); // �ʱ�ȭ

	HeapType_ptr heap = hcreate(); // �� ����
	hinit(heap); // �ʱ�ȭ 

	int num = 0;
	int i;

	// ��,�󵵼�,�¿� �ε��� ���ϱ� 
	for (i = -1; i <= n; i++) {
		if (i == -1 || i == n) { // �ܼ��� ũ�� �񱳸� ���ؼ� ���
			element e = { -1,-1, -1, -1,false };
			insert(list, e);
		}
		else if (i == 0 || array[i] != array[i - 1]) {
			element e = { array[i],1,list->size - 1,list->size+1,true };
			helement h = { array[i], list->size };
			insert(list, e);
			insert_max_heap(heap, h);
		}
		else {
			list->array[list->size-1].freq++;
		}
	}
	
	while (1) {
		// ���� ū ���� �������� ���� 
		int idx=0;
		while (!list->array[idx].check) {
			idx = delete_max_heap(heap).list_idx;
		}
		int left_idx = list->array[idx].left;
		int right_idx = list->array[idx].right;

		// ������ ���� (�� ���ڰ� n��)
		if (list->array[idx].freq == n) {
			if (list->array[idx].infor == 0) {
				return num;
			}
			else {
				return ++num;
			}
		}

		// �������� �� ŭ -> ������ ���� frequency�� ä��
		else if (list->array[left_idx].infor < list->array[right_idx].infor) {
			list->array[right_idx].freq += list->array[idx].freq;
			list->array[left_idx].right = right_idx; // ���� ����� right�� ������ ���
			list->array[right_idx].left = left_idx; // ������ ����� left�� ���� ���
			list->array[idx].check = false;
			num++;
		}

		// ������ �� ŭ -> ���� ���� frequency�� ä��
		else if (list->array[left_idx].infor > list->array[right_idx].infor) {
			list->array[left_idx].freq += list->array[idx].freq;
			list->array[left_idx].right = right_idx; // ���� ����� right�� ������ ���
			list->array[right_idx].left = left_idx; // ������ ����� left�� ���� ���
			list->array[idx].check = false;
			num++;
		}

		// �����ʰ� ������ ���� 
		else {
			// �������� frequency�� ������
			list->array[left_idx].freq += list->array[right_idx].freq; 
			list->array[left_idx].freq += list->array[idx].freq;
			list->array[left_idx].right = list->array[right_idx].right; // ���� ����� right�� �������� ������ ���
			list->array[list->array[right_idx].right].left = left_idx; // �������� ������ ����� left�� ���� ���  
			list->array[idx].check = list->array[right_idx].check = false;
			num++;
		}
	}
}

int main() {
	int n = 0;
	scanf("%d", &n);
	int* array = (int*)malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &array[i]);
	}
	printf("%d\n", decrease(array, n));
	return 0;
}
