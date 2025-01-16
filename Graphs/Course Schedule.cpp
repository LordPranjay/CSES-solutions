#include <bits/stdc++.h>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace chrono;
// using namespace __gnu_pbds;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
#define ll long long
#define int long long int
#define test      \
    int _TEST;    \
    cin >> _TEST; \
    while (_TEST--)
#define mod 1000000007
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
        cout << a[i]+1 << " ";    \
    }
#define all(x) (x).begin(), (x).end()
#define nl cout << "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define prt(x) cout << x << endl
#define prdouble(x) cout << fixed << setprecision(10) << x
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define cont continue
/**********************************************************/
ll lcm(ll a, ll b)
{
    return a * b / __gcd(a, b);
}
// binary modular exponentiation
ll binpow(ll a, ll b)
{
    if (b == 0)
        return 1;
    ll res = binpow(a, b / 2);
    if (b & 1)
        return res * res * a;
    else
        return res * res;
}
ll binpowmod(ll a, ll b, ll m=MOD)
{
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
ll mminvprime(ll a, ll b)
{ // gives modulo inverse of a wrt b where b is prime
    return binpowmod(a, b - 2, b);
}
ll mod_add(ll a, ll b, ll m=MOD)
{
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
ll mod_mul(ll a, ll b, ll m=MOD)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll mod_sub(ll a, ll b, ll m=MOD)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
ll mod_div(ll a, ll b, ll m=MOD)
{
    a = a % m;
    b = b % m;
    return (mod_mul(a, mminvprime(b, m), m) + m) % m;
} // only for prime m
// returns sorted prime factorisation in sqrt(N)
vi primefactorisation1(int n)
{
    vi factorisation;
    for (ll d = 2; d * d <= n; d++)
    {
        while (n % d == 0)
        {
            factorisation.pb(d);
            n /= d;
        }
    }
    if (n > 1)
    {
        factorisation.pb(n);
    }
    return factorisation;
}
 
/****************************************************************/
// precomputation in o(n) time
vector<ll> fact;
vector<ll> ifact;
void combination(int n)
{
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fact[i] = mod_mul(fact[i - 1], i, MOD);
    }
    ifact[n] = mminvprime(fact[n], MOD);
    for (int i = n - 1; i >= 0; i--)
    {
        ifact[i] = mod_mul(ifact[i + 1], i + 1, MOD);
    }
}
ll ncr1(ll n, ll r, ll m = MOD)
{
    return mod_mul(fact[n], mod_mul(ifact[r], ifact[n - r], m), m);
}
// for individual ncr in o(r) time
int ncr2(int n, int r)
{
    long long p = 1, k = 1;
    if (n - r < r)
        r = n - r;
    if (r != 0)
    {
        while (r)
        {
            p *= n;
            k *= r;
            long long m = __gcd(p, k);
            p /= m;
            k /= m;
            n--;
            r--;
        }
    }
    else
        p = 1;
    return p;
}
/************************************************************/
// sieve of eratosthenes -> precomputation of primes in Nlog(log(N))
vb isprime;
vi spf;
void sieve(int n = 1e6)
{
    isprime.resize(n + 1, true);
    spf.resize(n + 1, 1e9);
    isprime[0] = isprime[1] = false;
 
    for (ll i = 2; i <= n; i++)
    {
        if (isprime[i])
        {
            spf[i] = i;
            for (ll j = i * i; j <= n; j += i)
            {
                isprime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}
// call sieve first from main
vpii primefactorisation(int x)
{
    vpii ans;
    while (x != 1)
    {
        int prime = spf[x];
        int cnt = 0;
        while (x % prime == 0)
        {
            cnt++;
            x /= prime;
        }
        ans.pb({prime, cnt});
    }
    return ans;
}
vi phi;
// call sieve first from main
void calphi(int n)
{ // precomputes phi from 1 to n in o(nlogn)
    phi.resize(n + 1);
    fr(i, 0, n + 1)
    {
        phi[i] = i;
    }
    fr(i, 2, n + 1)
    {
        if (isprime[i])
        {
            phi[i] = i - 1;
            for (int j = 2 * i; j <= n; j += i)
            {
                phi[j] -= phi[j] / i;
            }
        }
    }
}
/***************************************************************************************************************************************/
vvi dig(int m,int n){ //m is edges and n is vertices, it assumes directed edge from ff to ss
    vpii e(m);
    vvi adj(n);
    fr(i,0,m){
        cin>>e[i].ff>>e[i].ss;
        adj[--e[i].ff].pb(--e[i].ss);
    }
  return adj;
}
 
//Function to return vector containing vertices in Topological order.
    vector<int> topoSort(int V, vector<vector<int>> &adj){
        vector<int> indegree(V,0);
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }
 
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            // node is in your topo sort
            // so please remove it from the indegree
 
            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) q.push(it);
            }
        }
        return topo;
    }
 
 
signed main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n,m;
    cin>>n>>m;
    vvi adj=dig(m,n);
vi a= topoSort(n,adj);
if(a.size()!=n){
    cout<<"IMPOSSIBLE";
}
else{
    output(a,n)
}
 
}