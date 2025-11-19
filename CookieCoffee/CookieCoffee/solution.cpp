// 문제 설명
// N개의 건물 (M개의 커피점 + P개의 제과점 +나머지 주택)
// 제한거리 R
// 커피점과의 거리가 R 이하, 제과점과의 거리가 R 이하인 주택중에서 두 거리를 합한 값이 최소가 되는 값을 찾는다.

// 문제 풀이
// 멀티 소스 다익스트라
// 1. 모든 주택에 대해 가장 가까운 커피점을 구한다 (거리가 R 이상이면 패스)
// 2. 모든 주택에 대해 가장 가까운 제과점을 구한다.(거리가 R 이상이면 패스)
// 3. 주택을 돌면서 커피점과 제과점의 거리합이 작은걸 구한다.
#include <queue>
#include <vector>
using namespace std;
#define MAX_BUILDING 10001
#define _INF 10e9
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

	//// 일반 다익스트라(시작점 - 모든 노드의 최단거리를 구함)
	//vector<int> dist(_N, _INF); // _N 개를 _INF로 초기화
	//priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	////시작점 초기화
	//int start = 0; 
	//dist[start] = 0;
	//pq.push(make_pair(start, 0)); // 정점, cost

	//while (!pq.empty())
	//{
	//	pair <int, int> top = pq.top();
	//	int now = top.first;
	//	int cost = top.second;
	//	pq.pop();

	//	if (dist[now] < cost) continue;

	//	for (int i = 0; i < adj[now].size(); i++)
	//	{
	//		int nextnode = adj[now][i].first;
	//		int w = adj[now][i].second;

	//		int nextdist = cost + w;
	//		if (nextdist < dist[nextnode])
	//		{
	//			dist[nextnode] = nextdist;
	//			pq.push(make_pair(nextdist, nextnode));
	//		}
	//	}
	//}
	//return 0;

    int cDist[MAX_BUILDING], bDist[MAX_BUILDING];
    memset(cDist, 0x7f, sizeof(cDist));
    memset(bDist, 0x7f, sizeof(bDist));


    priority_queue<int, vector<int>, greater<int>> pq;


    for (int i = 0; i < M; ++i) {
        cDist[mCoffee[i]] = 0;
        pq.emplace(1 << 16 | mCoffee[i]);
    }


    for (int i = 0; i < P; ++i) {
        bDist[mBakery[i]] = 0;
        pq.emplace(mBakery[i]);
    }


    int ret = R * 2 + 1;
    while (!pq.empty()) {
        int curr = pq.top();
        pq.pop();


        int currCost = curr >> 32;
        int isCoffee = (curr >> 16) & 0xffff;
        int u = curr & 0xffff;


        if (currCost >= ret || currCost > R) break;


        if (isCoffee) {
            if (cDist[u] < currCost) continue;
            if (currCost > 0 && currCost <= R && bDist[u] > 0 && bDist[u] <= R && currCost + bDist[u] < ret) {
                ret = currCost + bDist[u];
            }


            for (int val : adj[u]) {
                int v = val >> 16;
                int nextCost = currCost + val & 0xffff;


                if (nextCost >= ret) continue;
                if (cDist[v] > nextCost) {
                    cDist[v] = nextCost;
                    pq.emplace(nextCost << 32 | 1 << 16 | v);
                }
            }
        }
        else {
            if (bDist[u] < currCost) continue;
            if (currCost > 0 && currCost <= R && cDist[u] > 0 && cDist[u] <= R && currCost + cDist[u] < ret) {
                ret = currCost + cDist[u];
            }


            for (int val : adj[u]) {
                int v = val >> 16;
                int nextCost = currCost + val & 0xffff;


                if (nextCost >= ret) continue;
                if (bDist[v] > nextCost) {
                    bDist[v] = nextCost;
                    pq.emplace(nextCost << 32 | v);
                }
            }
        }
    }


    return (ret <= 2 * R) ? ret : -1;

}