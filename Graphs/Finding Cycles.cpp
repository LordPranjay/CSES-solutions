#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr(i, a, b) for (int i = a; i < b; i++)
#define pb push_back
#define vi vector<int>
#define vc vector<char>
#define vvc vector<vc>
#define vvi vector<vi>
#define all(x) (x).begin(), (x).end()
#define nl cout << "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define prt(x) cout << x << endl
#define ff first
#define ss second

struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;

void solve() {
    cin>>n>>m;
    vector<int> d(n, 0);
    vector<int> p(n, -1);
    fr(i,0,m){
        int a,b,c;
        cin>>a>>b>>c;
        a--;b--;
        edges.pb(Edge{a,b,c});
    }
    int x;

    d[0] = 0;

    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges) {
            if (d[e.a] + e.cost < d[e.b]) {
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if (x == -1) {
        cout << "NO";
    } else {
        for (int i = 0; i < n; ++i) 
            x = p[x];

        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        yes;
        for (int v : cycle)
            cout << v+1 << ' ';
        cout << endl;
    }
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    solve();
}
