#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
#define INF 1000000001

typedef struct GraphType {
	int n; // 정점의 개수
	double weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int selected[MAX_VERTICES]; // <테이블의 s/t열> , 선택되면 s집합에 속함 
double w[MAX_VERTICES]; // <테이블의 w열> , 원소: s집합에서 해당 정점까지의 거리 

// 그래프 초기화
void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->weight[r][c] = INF;
	}
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int start, int end, double weight) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}

// s집합에 속하지 않으면서 최소 w[v] 값을 갖는 정점을 반환
int get_min_vertex(int n) {
	int v, i;
	// 선택되지 않은 정점을 선택 (v정점 지정) 
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	// v정점의 w값과 나머지 정점들의 w값을 비교하면서 최소 w값을 갖는 정점 구하기 (선택된 것은 제외) 
	for (i = 0; i < n; i++) {
		if (!selected[i] && (w[i] < w[v]))
			v = i;
	}
	return v;
}

// MST 구하는 prim 함수  
void prim(GraphType* g, int s) {
	int i, u, v;

	// s집합에 원소가 없으면 a(0)만 인접하다고 가정하고 문제를 풀음 
	for (u = 0; u < g->n; u++)
		w[u] = INF;
	w[s] = 0;

	// s집합에 원소가 한 개 이상 있을 때 반복문으로 문제 풀기 (정점을 n개 선택할 때까지)
	for (i = 0; i < g->n; i++) {
		// w배열에서 가중치가 가장 작은 정점 선택 (s에 속하지 않은 정점들로 한정) 
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (w[u] == INF) {
			printf("-> 선택할 정점이 없음\n");
			return;
		}

		// s집합과 인접한 정점들로 w배열 업데이트
		for (v = 0; v < g->n; v++) {
			// u정점을 기준으로 인접한 것을 찾음 <u정점 말고 다른 정점도 s집합에 속하지만 같은 배열을 업데이트하는 개념이므로, 이미 처리가 된 상태임>
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < w[v]) // v정점이 s집합에 속하면 처리 x, u-v의 가중치가 기존의 w배열 원소보다 작으면 업데이트 
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

// 팩토리얼 함수
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

// 조합 개수 구하는 함수 
int combi_num(int n, int r) {
	if (r >= 0 && r <= n) {
		int denominator, numerator, answer;
		denominator = factorial(n, n - r);
		numerator = factorial(r, 0);
		answer = denominator / numerator;
		return answer;
	}
}

// 두 점 사이의 거리 구하기 
double make_distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// combination작업을 이용해서 llist 제작  (k는 항상 2)
void make_dlist(Antenna* alist, Line* llist, int n) {
	// llist 초기화를 위한 변수 선언
	int x1, x2, y1, y2;
	x1 = x2 = y1 = y2 = 0;
	int l_idx = 0;

	// combination 작업을 위한 변수 선언 
	int k = 2;
	int* kset = (int*)malloc(sizeof(int)*(k));
	int i;
	for (i = 0; i < k; i++)
		kset[i] = i;
	int finish = 0;

	while (!finish) {
		// llist 초기화
		llist[l_idx].antenna1 = alist[kset[0]].code;
		llist[l_idx].antenna2 = alist[kset[1]].code;
		x1 = alist[kset[0]].x;
		x2 = alist[kset[1]].x;
		y1 = alist[kset[0]].y;
		y2 = alist[kset[1]].y;
		llist[l_idx++].distance = make_distance(x1, x2, y1, y2);

		// kset 업데이트 (combination 작업)
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

// 배열 중 가장 큰 값 찾기 
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
	int n = 0; // 안테나 개수 
	scanf("%d", &n);

	// 안테나 개수가 1개 이하면 0출력 후 종료
	if (n <= 1) {
		printf("0\n");
		return 0;
	}
	
	int line_num = combi_num(n, 2); // 두 안테나를 잇는 선의 개수 

	Antenna* alist = (Antenna*)malloc(sizeof(Antenna)*n); // antenna list
	Line* llist = (Line*)malloc(sizeof(Line)*line_num); // line list 
	
	int i; // iteration variable

	// 안테나 정보 삽입
	for (i = 0; i < n; i++) {
		alist[i].code = i;
		scanf("%d %d", &(alist[i].x), &(alist[i].y));
	}

	// line list 제작 
	make_dlist(alist, llist, n);
	
	// 안테나를 노드로 가지는 그래프 생성
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (i = 0; i < n; i++)
		insert_vertex(g, i);


	// 모든 에지 연결
	for (i = 0; i < line_num; i++) {
		int a = llist[i].antenna1;
		int b = llist[i].antenna2;
		double weight = llist[i].distance;
		insert_edge(g, a, b, weight);
	}
	
	// prim알고리즘으로 최소 신장 트리 생성 
	prim(g, 0);
	
	// 최소신장트리의 가중치 중 가장 큰 값의 절반을  출력  
	printf("%.7lf\n",find_biggest(w,n)/2);

	return 0;
}
