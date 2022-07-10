#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
int* s_tree; // 세그먼트 트리

typedef struct Movie {
	int start, end, income;
}Movie;


// 끝 시간을 기준으로 오름차순
bool compare(Movie& m1, Movie& m2) {
	return m1.end < m2.end;
}

// 구간에서 최댓값 찾기 
int ret(int node, int s, int e, int l, int r) {
	if (l > e || r < s)
		return 0;

	if (l <= s && e <= r)
		return s_tree[node];

	int m = (s + e) / 2;
	return max(ret(node * 2, s, m, l, r), ret(node * 2 + 1, m + 1, e, l, r));
}

// 세그먼트 트리 업데이트 
int update(int node, int s, int e, int idx, int val) {
	if (s <= idx && idx <= e) {
		if (s == e) {
			/* 
				기존 세그먼트 트리는 val값을 저장하지만 이 코드는 max값을 비교해서 저장함
				이 세그먼트 트리에서 leaf node는 배열의 원소가 아니라 배열의 원소와 관련된 어떤 값(c_max+income)이 나와야 됨 
				start, end 값들을 압축해서 사용하므로 여러 개의 start에 대해 한 개의 end가 나올 수 있음
				ex) 영화[start,end,income] = 영화[9,13,300], 영화[10,13,100], 영화[14,16,200] 이 있다고 가정하겠음
				영화[14,16,200]의 '현재 시작 시간 기준 최댓값(c_max)'은 300이 돼야 함
				그런데 영화[10,13,100]을 확인하면서 v[end_idx]=13에 대한 세그먼트 트리 값이 100으로 업데이트 됨
				따라서 중복된 end에 대한 세그먼트 트리 값은 최댓값(300)이 되어야만 함!!
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

// 세그먼트 트리 출력 
void sprint(int size) {
	for (int i = 1; i < size; i++) {
		cout << "[" << i << "] " << s_tree[i] << " ";
	}
	cout << endl;
}

// 이진 탐색 (x -> find v_vector_index) 
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
	// 입/출력 최적화 
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; // 영화의 개수 
	vector<Movie> mv; // 영화 자료구조 (start,end,income)
	vector<int>v; // 영화의 start, end가 담긴 배열  

	// 변수,벡터 초기화 
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, e, ic;
		cin >> s >> e >> ic;
		Movie M = { s, e, ic };
		mv.push_back(M);
		v.push_back(s);
		v.push_back(e);
	}

	// 벡터 정렬 
	sort(mv.begin(), mv.end(), compare); // end 기준 오름차순
	sort(v.begin(), v.end());

	// 중복되는 원소 삭제 
	v.erase(unique(v.begin(), v.end()), v.end());

	// 세그먼트 트리 생성 
	int h = (int)ceil(log2(v.size()));
	int tree_size = (int)pow(2, h + 1);
	s_tree = new int[tree_size]{};

	// 세그먼트 트리로 최대 수입 얻기
	int max_idx = v.size() - 1;
	int max_income, sum, c_max, s_idx, e_idx;
	max_income = sum = c_max = s_idx = e_idx = 0;

	for (int i = 0; i < n; i++) {
		// 시작, 끝 시간을 보고 벡터 인덱스 찾기  
		s_idx = find(v,mv[i].start);
		e_idx = find(v,mv[i].end);
		// 현재 시작 시간 기준 최댓값 찾기 
		c_max = ret(1, 0, max_idx, 0, s_idx-1);
		// MAX(현재 시작 시간 기준 최댓값 + 현재 영화 소득, 이전 최대 소득) 
		sum = c_max + mv[i].income;
		max_income = max(max_income, sum);
		// 끝 시간 위치에 sum값 저장
		update(1, 0, max_idx, e_idx, sum);
	}

	// 최대 수입 출력 
	cout << max_income << endl;

	// 동적 메모리 해제 
	delete[] s_tree;

	return 0;
}

