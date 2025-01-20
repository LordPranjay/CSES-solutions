#include <bits/stdc++.h>
using namespace std;
#define fr(i, a, b) for (int i = a; i < b; i++)
#define pb push_back
#define prt(x) cout << x <<"\n"
 
void solve() {
    int n, q;
    cin>>n>>q;
    int v[200001];
    fr(i,0,n){
     cin>>v[i];
     v[i]--;
    } 
    int dp[200001][30];
    fr(i,0,n) dp[i][0] = v[i];
    fr(j,1,30){
        fr(i,0,n){
            dp[i][j] = dp[dp[i][j-1]][j-1];
            //cout<<dp[i][j];
        }
    }
 
    fr(i,0,q){
        int x, k;
        cin>>x>>k;
        x--;
        fr(i,0,30){
            if(k & (1<<i)) x = dp[x][i];
        }
        prt(x+1);
    }
    return;
}
signed main(){
    //important to use this
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    solve();
}