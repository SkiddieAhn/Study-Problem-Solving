#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX_VERTICES 20000
#define INIT_VALUE -1
#define RED 1
#define BLUE 2

using namespace std;


/*
   �׷��� - ���� ��� ����
*/

typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;


// �׷��� �ʱ�ȭ
void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
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
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
}


/*
   �׷��� - ���� ����Ʈ ����
*/

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType2 {
	int n; // ������ ����
	GraphNode* adj_list[MAX_VERTICES];
}GraphType2;


// �׷��� �ʱ�ȭ
void init2(GraphType2* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// ���� ���� ����
void insert_vertex2(GraphType2* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge2(GraphType2* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	if (g->adj_list[u] == NULL) { // insert_first
		node = (GraphNode*)malloc(sizeof(GraphNode));
		node->vertex = v;
		node->link = g->adj_list[u];
		g->adj_list[u] = node;
	}
	else { //insert_last
		node = g->adj_list[u];
		while (node->link != NULL)
			node = node->link;
		node->link = (GraphNode*)malloc(sizeof(GraphNode));
		node->link->vertex = v;
		node->link->link = NULL;
	}
}


/*
   �˰���1 - SCC
*/

int id, VID[MAX_VERTICES];
bool finished[MAX_VERTICES];
vector<vector<int>> scc_list;
stack<int> s;

// DFS for SCC
int DFS1(GraphType* g, int v) {
	// ���ÿ� ����
	s.push(v);

	// ������ ������ ID �ο� 
	VID[v] = ++id;

	// �θ� �ڽ� ID�� ����
	int parent = VID[v];

	// DFS�� SCC ���� 
	for (int w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w]) {
			int next = w;
			// �湮���� ���� ����
			if (!VID[next])
				parent = min(parent, DFS1(g, next));
			// ó������ ����
			else if (!finished[next])
				parent = min(parent, VID[next]);
		}
	}

	// �θ� �ڽ��� ��� 
	if (parent == VID[v]) {
		vector<int> scc;
		int top_v = INIT_VALUE;

		// ���ÿ��� ���� scc�迭�� ���� 
		while (top_v != v) {
			top_v = s.top();
			s.pop();
			scc.push_back(top_v);
			finished[top_v] = true;
		}
		// scc�� scc_list�� ����
		scc_list.push_back(scc);
	}

	return parent;
}

/*
   �˰���2 - Bipartite Graph
*/

// DFS for Coloring
int* visited;
void DFS2(GraphType2* g, int v) {
	// ó�� ������ ���� ������ ĥ�� 
	if (!visited[v])
		visited[v] = RED;

	for (GraphNode* w = g->adj_list[v]; w; w = w->link) {
		// ���� �湮���� ���� �����̸� ���� ������ �ݴ� ������ ĥ��
		if (!visited[w->vertex]) {
			if (visited[v] == RED)
				visited[w->vertex] = BLUE;
			else if (visited[v] == BLUE)
				visited[w->vertex] = RED;
			DFS2(g, w->vertex);
		}
	}
}

// �̺� �׷��� üũ
bool Bipartite(GraphType2* g) {
	// ��� �������� ��ȸ�ϸ鼭 ������ �������� ���� ������ Ȯ�� 
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		int curr = i;
		while (p != NULL) {
			int next = p->vertex;
			// check bipartite
			if (visited[curr] == visited[next])
				return false;
			// update p
			p = p->link;
		}
	}
	return true;
}

// find OddCycle
int oddCycle(GraphType* g) {
	// scc �� Bipartite ã��
	for (int i = 0; i < scc_list.size(); i++) {

		// make small graph
		GraphType2* sg;
		sg = (GraphType2*)malloc(sizeof(GraphType2));
		init2(sg);

		// scc
		vector<int> list = scc_list[i];

		// init visited
		visited = new int[list.size()]{};

		// add vertex
		for (int j = 0; j < list.size(); j++)
			insert_vertex2(sg, j);

		// add edge
		for (int k = 0; k < list.size(); k++) {
			for (int h = k + 1; h < list.size(); h++) {
				int val1 = list[k];
				int val2 = list[h];

				if (g->adj_mat[val1][val2] || g->adj_mat[val2][val1]) {
					insert_edge2(sg, k, h);
					insert_edge2(sg, h, k);
				}
			}
		}

		// find Bipartite
		DFS2(sg, 0);

		bool output = Bipartite(sg);
		// Bipartite -> no odd cycle
		if (output)
			continue;
		// no Bipartite -> odd cycle
		else
			return true;

		// delete
		free(sg);
		delete[] visited;
	}

	// ��� scc�� Bipartite
	return -1;
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	// ����, ���� ���� �Է� 
	int n, m;
	cin >> n >> m;

	// ���� ���� 
	for (int i = 0; i < n; i++)
		insert_vertex(g, i);

	// ���� ����
	for (int i = 0; i < m; i++) {
		int u, v; // vertex(u) -> vertex(v)
		cin >> u >> v;
		// ������ 0���� �����ϹǷ� 1�� ����
		u = u - 1;
		v = v - 1;
		insert_edge(g, u, v);
	}

	// SCC ã�� 
	for (int i = 0; i < n; i++) {
		if (VID[i] == 0)
			DFS1(g, i);
	}

	// OddCycle ã��
	int rst = oddCycle(g);
	printf("%d\n", rst);

	free(g);
	return 0;
}

