// 문제 설명
// N개의 건물 (M개의 커피점 + P개의 제과점 +나머지 주택)
// 제한거리 R
// 커피점과의 거리가 R 이하, 제과점과의 거리가 R 이하인 주택중에서 두 거리를 합한 값이 최소가 되는 값을 찾는다.

// 문제 풀이
// 멀티 소스 다익스트라
// 1. 모든 주택에 대해 가장 가까운 커피점을 구한다 (거리가 R 이상이면 패스)
// 2. 모든 주택에 대해 가장 가까운 제과점을 구한다.(거리가 R 이상이면 패스)
// 3. 주택을 돌면서 커피점과 제과점의 거리합이 작은걸 구한다.

#include <vector>
using namespace std;
#define MAX_BUILDING 10001
vector<pair<int, int>> adj[MAX_BUILDING]; // 도착지, 거리
int _N;

void init(int N, int K, int sBuilding[], int eBuilding[], int mDistance[])
{
	_N = N;
	for (int i = 0; i < MAX_BUILDING; i++)
	{
		adj[i].clear();
	}
	for (int i = 0; i < K; i++)
	{
		adj[sBuilding[i]].push_back(make_pair(eBuilding[i], mDistance[i]));
	}
	return;
}

void add(int sBuilding, int eBuilding, int mDistance)
{
	adj[sBuilding].push_back(make_pair(eBuilding, mDistance));
	return;
}

int calculate(int M, int mCoffee[], int P, int mBakery[], int R) {
	return 0;
}