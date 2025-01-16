#include <bits/stdc++.h>
using namespace std;

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

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int dx[4] ={0,-1,0,1};
    int dy[4] ={1,0,-1,0};

    int n,m;
    cin>>n>>m;
    vector<string> v(n);
    fr(i,0,n){
        cin>>v[i];
    }

    map<int, int> mp ,mpr;
    mp[0] = 'R';mp[1] = 'U'; mp[2] = 'L'; mp[3] = 'D';
    mpr['L']=0; mpr['D']=1; mpr['R']=2; mpr['U'] = 3;

    // multisrc bfs for monsters
    queue<pair<int,int>> q;
    vvi dis(n,vi(m,1e7));
    fr(i,0,n){
        fr(j,0,m){
         if(v[i][j]=='M'){
             q.push({i,j});
             dis[i][j] = 0;
         }
        }
    }
    while(!q.empty()){
        int s = q.size();
        fr(i,0,s){
            int x =q.front().ff;
            int y =q.front().ss;
            q.pop();
            fr(k,0,4){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(nx>=0 &&ny>=0 && nx<n && ny<m && v[nx][ny]!='#' && dis[nx][ny]>1+dis[x][y]){
                    q.push({nx,ny});
                    dis[nx][ny] = 1 + dis[x][y];
                }
            }
        }
    }
    // bfs for A
    vvi d(n,vi(m,1e7));
    vvc path(n,vc(m,'Q'));
    fr(i,0,n){
        fr(j,0,m){
         if(v[i][j]=='A'){
             q.push({i,j});
             d[i][j] = 0;
             break;
         }
        }
    }
    while(!q.empty()){
        int s = q.size();
        fr(i,0,s){
            int x =q.front().ff;
            int y =q.front().ss;
            q.pop();
            if(d[x][y]>=dis[x][y]) continue;
            if(x==0 || x==n-1 || y==0 || y==m-1){
                yes;
                vc ans;
                while(path[x][y]!='Q'){
                    ans.pb(path[x][y]);
                    int tx = x+ dx[mpr[path[x][y]]];
                    int ty =y + dy[mpr[path[x][y]]];
                    x=tx;y=ty;
                }
                reverse(all(ans));
                prt(ans.size());
                for(auto j:ans) cout<<j;
                return 0;
            }
            fr(k,0,4){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(nx>=0 &&ny>=0 && nx<n && ny<m && v[nx][ny]=='.' && d[nx][ny]>1+d[x][y]){
                    q.push({nx,ny});
                    path[nx][ny] = mp[k];
                    d[nx][ny] = 1 + d[x][y];
                }
            }
        }
    }
    no;
    return 0;
}
