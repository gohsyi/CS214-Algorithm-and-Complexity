#include <vector>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

#define MAXN 100010

vector<int>G[MAXN];
vector<int>SCC[MAXN];
int dfs_clock, scc_cnt;
int sccno[MAXN], pre[MAXN], lowlink[MAXN];
stack<int> S;

void dfs(int u)
{
	pre[u] = lowlink[u] = ++dfs_clock;
	S.push(u);
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			dfs(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		}
		else if(!sccno[v]) {
			lowlink[u] = min(lowlink[u], pre[v]);
		}
	}
	if (pre[u] == lowlink[u]) {
		++scc_cnt;
		while (1) {
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			SCC[scc_cnt].push_back(x);
			if (x == u) break;
		}
	}
}

int main()
{
	freopen("Data-CCC.txt", "r", stdin);
	freopen("Output-SCC-516030910306.txt", "w", stdout);

	int n, m;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}

	for (int u = 0; u < n; u++)
		if (!pre[u]) dfs(u);

	int maxSCC = 1;
	for (int i = 1; i <= scc_cnt; i++)
		if (SCC[i].size() > SCC[maxSCC].size()) 
			maxSCC = i;

	printf("%d\n", scc_cnt);
	sort(SCC[maxSCC].begin(), SCC[maxSCC].end());
	for (int i = 0; i < SCC[maxSCC].size(); i++)
		printf("%d ", SCC[maxSCC][i]);
	return 0;
}