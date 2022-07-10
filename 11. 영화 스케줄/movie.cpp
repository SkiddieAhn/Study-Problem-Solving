#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
int* s_tree; // ���׸�Ʈ Ʈ��

typedef struct Movie {
	int start, end, income;
}Movie;


// �� �ð��� �������� ��������
bool compare(Movie& m1, Movie& m2) {
	return m1.end < m2.end;
}

// �������� �ִ� ã�� 
int ret(int node, int s, int e, int l, int r) {
	if (l > e || r < s)
		return 0;

	if (l <= s && e <= r)
		return s_tree[node];

	int m = (s + e) / 2;
	return max(ret(node * 2, s, m, l, r), ret(node * 2 + 1, m + 1, e, l, r));
}

// ���׸�Ʈ Ʈ�� ������Ʈ 
int update(int node, int s, int e, int idx, int val) {
	if (s <= idx && idx <= e) {
		if (s == e) {
			/* 
				���� ���׸�Ʈ Ʈ���� val���� ���������� �� �ڵ�� max���� ���ؼ� ������
				�� ���׸�Ʈ Ʈ������ leaf node�� �迭�� ���Ұ� �ƴ϶� �迭�� ���ҿ� ���õ� � ��(c_max+income)�� ���;� �� 
				start, end ������ �����ؼ� ����ϹǷ� ���� ���� start�� ���� �� ���� end�� ���� �� ����
				ex) ��ȭ[start,end,income] = ��ȭ[9,13,300], ��ȭ[10,13,100], ��ȭ[14,16,200] �� �ִٰ� �����ϰ���
				��ȭ[14,16,200]�� '���� ���� �ð� ���� �ִ�(c_max)'�� 300�� �ž� ��
				�׷��� ��ȭ[10,13,100]�� Ȯ���ϸ鼭 v[end_idx]=13�� ���� ���׸�Ʈ Ʈ�� ���� 100���� ������Ʈ ��
				���� �ߺ��� end�� ���� ���׸�Ʈ Ʈ�� ���� �ִ�(300)�� �Ǿ�߸� ��!!
			*/
			s_tree[node] = max(s_tree[node],val);
		}
		else {
			int m = (s + e) / 2;
			s_tree[node] = max(update(node * 2, s, m, idx, val), update(node * 2 + 1, m + 1, e, idx, val));
		}
	}

	return s_tree[node];
}

// ���׸�Ʈ Ʈ�� ��� 
void sprint(int size) {
	for (int i = 1; i < size; i++) {
		cout << "[" << i << "] " << s_tree[i] << " ";
	}
	cout << endl;
}

// ���� Ž�� (x -> find v_vector_index) 
int find(vector<int> &v,int x) {
	int low = 0;
	int high = v.size() - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (v[mid] == x)
			return mid;
		else if (x > v[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}
	if (low > high)
		return -1;
}

int main(void)
{
	// ��/��� ����ȭ 
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; // ��ȭ�� ���� 
	vector<Movie> mv; // ��ȭ �ڷᱸ�� (start,end,income)
	vector<int>v; // ��ȭ�� start, end�� ��� �迭  

	// ����,���� �ʱ�ȭ 
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, e, ic;
		cin >> s >> e >> ic;
		Movie M = { s, e, ic };
		mv.push_back(M);
		v.push_back(s);
		v.push_back(e);
	}

	// ���� ���� 
	sort(mv.begin(), mv.end(), compare); // end ���� ��������
	sort(v.begin(), v.end());

	// �ߺ��Ǵ� ���� ���� 
	v.erase(unique(v.begin(), v.end()), v.end());

	// ���׸�Ʈ Ʈ�� ���� 
	int h = (int)ceil(log2(v.size()));
	int tree_size = (int)pow(2, h + 1);
	s_tree = new int[tree_size]{};

	// ���׸�Ʈ Ʈ���� �ִ� ���� ���
	int max_idx = v.size() - 1;
	int max_income, sum, c_max, s_idx, e_idx;
	max_income = sum = c_max = s_idx = e_idx = 0;

	for (int i = 0; i < n; i++) {
		// ����, �� �ð��� ���� ���� �ε��� ã��  
		s_idx = find(v,mv[i].start);
		e_idx = find(v,mv[i].end);
		// ���� ���� �ð� ���� �ִ� ã�� 
		c_max = ret(1, 0, max_idx, 0, s_idx-1);
		// MAX(���� ���� �ð� ���� �ִ� + ���� ��ȭ �ҵ�, ���� �ִ� �ҵ�) 
		sum = c_max + mv[i].income;
		max_income = max(max_income, sum);
		// �� �ð� ��ġ�� sum�� ����
		update(1, 0, max_idx, e_idx, sum);
	}

	// �ִ� ���� ��� 
	cout << max_income << endl;

	// ���� �޸� ���� 
	delete[] s_tree;

	return 0;
}

