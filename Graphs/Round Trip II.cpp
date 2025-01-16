#include <bits/stdc++.h>
using namespace std;
//using namespace chrono;
//using namespace __gnu_pbds;
//typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
#define ll long long
#define int long long int
#define test      \
    int _TEST;    \
    cin >> _TEST; \
    while (_TEST--)
#define fr(i, a, b) for (int i = a; i < b; i++)
#define rfr(i, a, b) for (int i = b; i >= a; i--)
#define ld long double
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vc vector<char>
#define vvc vector<vc>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vs vector<string>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mpi map<int, int>
#define ff first
#define ss second
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRandomNumber(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
#define input(a, n)             \
    for (int i = 0; i < n; i++) \
    {                           \
        cin >> a[i];            \
    }
#define output(a, n)            \
    for (int i = 0; i < n; i++) \
    {                           \
        cout << a[i] << " ";    \
    }
#define all(x) (x).begin(), (x).end()
#define nl cout << "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define prt(x) cout << x << endl
#define prdouble(x) cout << fixed << setprecision(10) << x
#define PI 3.1415926535897932384626433832795
#define MOD 998244353
#define cont continue
#define br break
    ll lcm(ll a, ll b){
    return a * b / __gcd(a, b);
}
// binary modular exponentiation
ll binpow(ll a, ll b){
    if (b == 0)
        return 1;
    ll res = binpow(a, b / 2);
    if (b & 1)
        return res * res * a;
    else
        return res * res;
}
ll binpowmod(ll a, ll b, ll m=MOD){
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll mminvprime(ll a, ll b){ // gives modulo inverse of a wrt b where b is prime
    return binpowmod(a, b - 2, b);
}
ll mod_add(ll a, ll b, ll m=MOD){
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
ll mod_mul(ll a, ll b, ll m=MOD){
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll mod_sub(ll a, ll b, ll m=MOD){
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
ll mod_div(ll a, ll b, ll m=MOD){
    a = a % m;
    b = b % m;
    return (mod_mul(a, mminvprime(b, m), m) + m) % m;
}
void debug(){
    cout<<"HEY THERE!"<<endl;
}

 
/***************************************************************************/
vvi adj;
vi vis, pathvis;
bool dfs(int node, int par, vi &ans){
    ans.pb(node);
    if(pathvis[node]) return true;
    vis[node] = pathvis[node] = 1;
    for(auto j:adj[node]){
        if(pathvis[j]){
            ans.pb(j);
            return true;
        }
        if(vis[j]==0 && dfs(j,node,ans)) return true;
    }
    ans.pop_back();
    pathvis[node] = 0;
    return false;
}
void solve() {
    int n,m;
    cin>>n>>m;
    adj.resize(n);
    vis.resize(n,0);
    pathvis.resize(n,0);
    fr(i,0,m){
        int a,b;
        cin>>a>>b;
        a--;b--;
        adj[a].pb(b);
    }

    fr(i,0,n){
        vi ans;
        if(vis[i]==0){
            //debug();
            //prt(i+1);
            if(dfs(i,-1,ans)){
                reverse(all(ans));
                //prt(ans.size());
                vi w;
                int req = ans[0];
                w.pb(req);
                int i=1;
                while(i<ans.size() && ans[i]!=req){
                    w.pb(ans[i]);
                    i++;
                }
                w.pb(req);
                reverse(all(w));
                prt(w.size());
                for(auto i:w){
                    cout<<i+1<<" ";  
                }
                return;
            }
        }
    }
    cout<<"IMPOSSIBLE"<<endl;
    return;    
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
     //test{
        solve();
     //}
}
