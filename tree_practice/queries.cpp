#include <iostream>
#include <vector>
using namespace std;


const int MAX_N = 200005;
const int LOG = 20;
vector<vector<int> > tree(MAX_N);

//here we are assuming that all ndoes are 1-based indices

int bl[MAX_N][LOG]; // 2**log ancestor of a given node
int parent[MAX_N]; //gives the parent of a node
int d[MAX_N]; //gives the depth of a node

int tin[MAX_N]; //In times of the DFS
int tout[MAX_N]; //Out times of the DFS
int timer = 0;

void dfs(int p, int node, int depth) {
    parent[node] = p;
    d[node] = depth;
    tin[node] = ++timer;
    for(int neigh : tree[node]) {
        if(neigh == p) {continue;}
        dfs(node, neigh, depth + 1);
    }
    tout[node] = ++timer;
}

void build_bl(int n) {
    for(int j = 0; j < LOG; j++) {
        for(int i = 1; i <= n; i++) {
            bl[i][j] = -1;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        bl[i][0] = i;
        bl[i][1] = parent[i];
    }
    for(int j = 2; j < LOG; j++) {
        for(int i = 1; i <= n; i++) {
            if(1 <= bl[i][j - 1] && bl[i][j - 1] <= n) {
                bl[i][j] = bl[bl[i][j - 1]][j - 1];
            }
        }
    }
}

//Is node a an ancestor of node b
bool is_ancestor(int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int LCA(int a, int b, int n) {
    if(is_ancestor(a,b)) {return a;}
    if(is_ancestor(b,a)) {return b;}

    for(int i = LOG - 1; i >= 0; i--) {
        if(1 <= bl[a][i] && bl[a][i] <= n) {
            if(!is_ancestor(bl[a][i], b)) {a = bl[a][i];}
        }
    }
    return parent[a];
}


int main() {
    int n, q;
    cin >> n >> q;

    for(int i = 1; i < MAX_N; i++) {
        tin[i] = 0;
        tout[i] = 0;
    }

    for(int i = 0; i < n - 1; i++) {
        int a,b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    dfs(-1,1,0); //root the tree at 1 and perform DFS
    build_bl(n); //build the binary lifting table

    
    for(int i = 0; i < q; i++) {
        int a,b;
        cin >> a >> b;
        int lca = LCA(a,b,n);
        cout << d[a] - d[lca] + d[b] - d[lca] << "\n";
    }
    return 0;
}