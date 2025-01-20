#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define MOD 1000000007
vector<ll> dp(1e5+1,0);
vector<int> vis(1e5+1,-1);
vector<vector<int>> adj(1e5+1);

void dfs(int node){
    vis[node] = 0;
    
    for(int v : adj[node]){
        if(vis[v] == -1) dfs(v);
        dp[node] = (dp[node] + dp[v])%MOD;
    }
}
int  main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int n, m , a , b;
    cin>>n>>m;
    dp[n-1] = vis[n-1] = 1;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        a--; b--;
        adj[a].push_back(b);
    }
    
    dfs(0);
    cout<<dp[0];
    return 0;
}