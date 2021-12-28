#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
#define INF 1000000001

typedef struct GraphType {
	int n; // ������ ����
	double weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int selected[MAX_VERTICES]; // <���̺��� s/t��> , ���õǸ� s���տ� ���� 
double w[MAX_VERTICES]; // <���̺��� w��> , ����: s���տ��� �ش� ���������� �Ÿ� 

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->weight[r][c] = INF;
	}
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int start, int end, double weight) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}

// s���տ� ������ �����鼭 �ּ� w[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n) {
	int v, i;
	// ���õ��� ���� ������ ���� (v���� ����) 
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	// v������ w���� ������ �������� w���� ���ϸ鼭 �ּ� w���� ���� ���� ���ϱ� (���õ� ���� ����) 
	for (i = 0; i < n; i++) {
		if (!selected[i] && (w[i] < w[v]))
			v = i;
	}
	return v;
}

// MST ���ϴ� prim �Լ�  
void prim(GraphType* g, int s) {
	int i, u, v;

	// s���տ� ���Ұ� ������ a(0)�� �����ϴٰ� �����ϰ� ������ Ǯ�� 
	for (u = 0; u < g->n; u++)
		w[u] = INF;
	w[s] = 0;

	// s���տ� ���Ұ� �� �� �̻� ���� �� �ݺ������� ���� Ǯ�� (������ n�� ������ ������)
	for (i = 0; i < g->n; i++) {
		// w�迭���� ����ġ�� ���� ���� ���� ���� (s�� ������ ���� ������� ����) 
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (w[u] == INF) {
			printf("-> ������ ������ ����\n");
			return;
		}

		// s���հ� ������ ������� w�迭 ������Ʈ
		for (v = 0; v < g->n; v++) {
			// u������ �������� ������ ���� ã�� <u���� ���� �ٸ� ������ s���տ� �������� ���� �迭�� ������Ʈ�ϴ� �����̹Ƿ�, �̹� ó���� �� ������>
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < w[v]) // v������ s���տ� ���ϸ� ó�� x, u-v�� ����ġ�� ������ w�迭 ���Һ��� ������ ������Ʈ 
					w[v] = g->weight[u][v];
			}
		}
	}
}

typedef struct Antenna {
	short code;
	int x, y;
}Antenna;

typedef struct Line {
	short antenna1;
	short antenna2;
	double distance;
}Line;

// ���丮�� �Լ�
int factorial(int a, int b) {
	if (a == 0)
		return 1;
	else {
		int result = 1;
		int i;
		for (i = a; i > b; i--)
			result *= i;
		return result;
	}
}

// ���� ���� ���ϴ� �Լ� 
int combi_num(int n, int r) {
	if (r >= 0 && r <= n) {
		int denominator, numerator, answer;
		denominator = factorial(n, n - r);
		numerator = factorial(r, 0);
		answer = denominator / numerator;
		return answer;
	}
}

// �� �� ������ �Ÿ� ���ϱ� 
double make_distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// combination�۾��� �̿��ؼ� llist ����  (k�� �׻� 2)
void make_dlist(Antenna* alist, Line* llist, int n) {
	// llist �ʱ�ȭ�� ���� ���� ����
	int x1, x2, y1, y2;
	x1 = x2 = y1 = y2 = 0;
	int l_idx = 0;

	// combination �۾��� ���� ���� ���� 
	int k = 2;
	int* kset = (int*)malloc(sizeof(int)*(k));
	int i;
	for (i = 0; i < k; i++)
		kset[i] = i;
	int finish = 0;

	while (!finish) {
		// llist �ʱ�ȭ
		llist[l_idx].antenna1 = alist[kset[0]].code;
		llist[l_idx].antenna2 = alist[kset[1]].code;
		x1 = alist[kset[0]].x;
		x2 = alist[kset[1]].x;
		y1 = alist[kset[0]].y;
		y2 = alist[kset[1]].y;
		llist[l_idx++].distance = make_distance(x1, x2, y1, y2);

		// kset ������Ʈ (combination �۾�)
		int idx;
		for (idx = k - 1; kset[idx] == n - k + idx; --idx) {
			if (idx == 0) {
				finish = 1;
				break;
			}
		}
		if (!finish) {
			kset[idx]++;
			for (i = idx + 1; i < k; i++)
				kset[i] = kset[i - 1] + 1;
		}
	}
}

// �迭 �� ���� ū �� ã�� 
double find_biggest(double* w,int size) {
	double biggest = w[0];
	int i;
	for (i = 1; i < size; i++) {
		if (biggest < w[i])
			biggest = w[i];
	}
	return biggest;
}


int main() {
	int n = 0; // ���׳� ���� 
	scanf("%d", &n);

	// ���׳� ������ 1�� ���ϸ� 0��� �� ����
	if (n <= 1) {
		printf("0\n");
		return 0;
	}
	
	int line_num = combi_num(n, 2); // �� ���׳��� �մ� ���� ���� 

	Antenna* alist = (Antenna*)malloc(sizeof(Antenna)*n); // antenna list
	Line* llist = (Line*)malloc(sizeof(Line)*line_num); // line list 
	
	int i; // iteration variable

	// ���׳� ���� ����
	for (i = 0; i < n; i++) {
		alist[i].code = i;
		scanf("%d %d", &(alist[i].x), &(alist[i].y));
	}

	// line list ���� 
	make_dlist(alist, llist, n);
	
	// ���׳��� ���� ������ �׷��� ����
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (i = 0; i < n; i++)
		insert_vertex(g, i);


	// ��� ���� ����
	for (i = 0; i < line_num; i++) {
		int a = llist[i].antenna1;
		int b = llist[i].antenna2;
		double weight = llist[i].distance;
		insert_edge(g, a, b, weight);
	}
	
	// prim�˰������� �ּ� ���� Ʈ�� ���� 
	prim(g, 0);
	
	// �ּҽ���Ʈ���� ����ġ �� ���� ū ���� ������  ���  
	printf("%.7lf\n",find_biggest(w,n)/2);

	return 0;
}
