#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

void print(const vector<vector<int>> &map,int n, int m);
void zero_print(const vector<pair<int, int>> &zero);
void dfs(vector<vector<int>> &map, int n, int m, const pair<int, int> &xy);
int zero_count(vector<vector<int>> &map, int n, int m);

vector<pair<int, int>> d = { {-1,0},{0,1},{1,0},{0,-1} };

void main() {

	int n = 0, m = 0; // n : ����, m : ����
	scanf("%d %d\n", &n, &m);
	
	vector<vector<int>> map(n + 1, vector<int>(m + 1, -1));
	vector<vector<int>> temp_map(n + 1, vector<int>(m + 1, -1));
	vector<pair<int, int>> zero;
	vector<pair<int, int>> two;

	int temp;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			scanf("%d", &temp);
			map[i][j] = temp;
		}
	}
	
	
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (map[i][j] == 0) {
				zero.push_back({ i,j });
			}
			else if (map[i][j] == 2) {
				two.push_back({ i,j });
			}
		}
	}

	int count;
	int maximum = INT_MIN;
	for (int i = 0; i < zero.size(); i++) {
		for (int j = i + 1; j < zero.size(); j++) {
			for (int k = j + 1; k < zero.size(); k++) {
				temp_map.clear();
				temp_map.assign(map.begin(), map.end());
				
				temp_map[zero[i].first][zero[i].second] = 1;
				temp_map[zero[j].first][zero[j].second] = 1;
				temp_map[zero[k].first][zero[k].second] = 1;
				
				for (int i = 0; i < two.size(); i++) {
					dfs(temp_map, n, m, two[i]);
				}
				
				count = zero_count(temp_map, n, m);
				if (maximum < count) {
					maximum = count;
				}
			}
		}
	}

	printf("\n");
	printf("maximum = %d\n", maximum);
}

void zero_print(const vector<pair<int, int>> &zero) 
{
	//printf("zero_size = %d\n", zero.size());
	for (int i = 0; i < zero.size(); i++) {
		printf("(%d, %d)\n", zero[i].first, zero[i].second);
	}
}

void dfs(vector<vector<int>>& map, int n, int m, const pair<int, int>& xy)
{
	int col, row;
	for (int i = 0; i < 4; i++) {
		col = xy.first + d[i].first;
		row = xy.second + d[i].second;
		if( 0 < col && col < n + 1 && 0 < row && row < m + 1){
			if (map[col][row] == 0) {
				map[col][row] = 2;
				dfs(map, n, m, { col, row });
			}
		}
	}
}

int zero_count(vector<vector<int>>& map, int n, int m)
{
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (map[i][j] == 0) {
				count++;
			}
		}
	}
	return count;
}

void print(const vector<vector<int>> &map, int n, int m)
{
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			printf("%d ", map[i][j]);
			//printf("(%d, %d) = %d ", i, j, map[i][j]);
		}
		printf("\n");
	}
}
