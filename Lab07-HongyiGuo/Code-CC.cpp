#include <vector>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

#define MAXN 100010

vector<int> G[MAXN];
vector<int> CC[MAXN];
int cc_cnt;
int ccno[MAXN];

void dfs(int u) {
    ccno[u] = cc_cnt;
    CC[cc_cnt].push_back(u);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!ccno[v]) dfs(v);
    }
}

int main()
{
	freopen("Data-CCC.txt", "r", stdin);
	freopen("Output-CC-516030910306.txt", "w", stdout);

	int n, m;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
        G[v].push_back(u);
	}

	for (int u = 0; u < n; u++)
		if (!ccno[u]) {
            cc_cnt++;
            dfs(u);
        }

    int maxCC = 1;
	for (int i = 1; i <= cc_cnt; i++)
		if (CC[i].size() > CC[maxCC].size()) 
			maxCC = i;

	printf("%d\n", cc_cnt);
	sort(CC[maxCC].begin(), CC[maxCC].end());
	for (int i = 0; i < CC[maxCC].size(); i++)
		printf("%d ", CC[maxCC][i]);
	return 0;
}