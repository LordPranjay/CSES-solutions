#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define int long long int
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
#define vvvvi vector<vvvi>
#define vs vector<string>
#define pii pair<int, int>
#define vpii vector<pii>
#define mpi map<int, int>
#define ff first
#define ss second
#define input(a, n)             \
    for (int i = 0; i < n; i++) \
    {                           \
        cin >> a[i];            \
    }
#define output(a, n)            \
    for (int i = 0; i < n; i++) \
    {                           \
        cout << a[i] << " ";    \
    }                           \
    cout<<endl;                 
#define all(x) (x).begin(), (x).end()
#define nl cout << "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define prt(x) cout << x << endl
#define prdouble(x) cout << fixed << setprecision(10) << x
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define cont continue
#define br break
/*--------------------------------------------------------------------------------------------------------------------------*/

template<typename Node, typename Update>
struct SegTree {

    vector<Node> tree; // sgt array
    vector<ll> arr; // input array
    int n; //size of input array
    int s; //size of sgt tree array

    SegTree(int a_len, vector<ll> &a) { // change if type updated
        arr = a;
        n = a_len;
        s = 1;
        while(s < 2 * n){
            s = s << 1; // find first power of 2 greater than equal to 2n
        }
        
        tree.resize(s);  
        fill(all(tree), Node());
        
        build(0, n - 1, 1);   
    }
    
    
    void build(int start, int end, int index){  // Never change this
        if (start == end) {
            tree[index] = Node(arr[start]); //we've reached leaf node
            return;
        }
        
        int mid = (start + end) / 2;
        build(start, mid, 2 * index); //left
        build(mid + 1, end, 2 * index + 1); //right
        tree[index].merge(tree[2 * index], tree[2 * index + 1]); //combine
    }
    
    
    
    void update(int start, int end, int index, int query_index, Update &u){  // Never Change this
        if (start == end) {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (mid >= query_index)
            update(start, mid, 2 * index, query_index, u);
        else
            update(mid + 1, end, 2 * index + 1, query_index, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    
    void make_update(int index, ll val) {  // pass in as many parameters as required 
        Update new_update = Update(val); // may change
        update(0, n - 1, 1, index, new_update); //done for abstraction purposes
    }
    
    Node query(int start, int end, int index, int left, int right) { // Never change this
        if (start > right || end < left){ /// complete disjoint
            return Node(); //deafult value
        }
        if (start >= left && end <= right){ // complete overlap
            return tree[index];
        }

        int mid = (start + end) / 2;
        Node l, r, ans;
        l = query(start, mid, 2 * index, left, right);
        r = query(mid + 1, end, 2 * index + 1, left, right);
        ans.merge(l, r);
        return ans;
    }
    
    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right); //done for abstraction purposes
    }   
};

struct Node1 {
    ll val; // may change
    Node1() {
        val = 0;  //this is the default value and should be defined in a way such that x = f(x,default) ie. no change
    }

    Node1(ll p1) {
        val = p1; // may change
    }
    
    void merge(Node1 &l, Node1 &r) { // this fn defines how we'll combine the result freom 2 child nodes
        val = l.val + r.val;
    }
};

struct Update1 {
    ll val; // may changem // information required to update the segtree node

    Update1(ll p1) { // Actual Update // pass in the relevant information
        val = p1; // may change
    }
    
    void apply(Node1 &a) { // apply update to given node
        // Node1 a is the leaf node
        // this node stores the sum of values in the range
        a.val += val; // may change
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
// returns number of employees with salaries between lo and hi
int calc(int lo, int hi, map<int,int>& sal2freq)
{
    int res = 0;
    auto it = sal2freq.lower_bound(lo);
    while(it != sal2freq.end() && it->first <= hi){
        res += it->second;
        it++;
    }
    return res;
}
//returns the bucket number to which x belongs
int bucket_no(int x)
{
    // 1-100 in block 0 but 100/100 = 1
    if(x % 100 == 0)
        x--;
    return (x / 100);
}


/*************************************************************************************/
signed main(){

// can refer to https://codeforces.com/blog/entry/77128
// the 1st submission was AC becasue i copieed above solution
// however using the same concept on my custom-made segment tree (below solution) was leading to TLE 
// anyways so focus more on concept on buckets creation and less on getting AC
// also refer to https://usaco.guide/problems/cses-1144-salary-queries/solution for ordered set solution

    fast_io;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int n,q;
    cin >> n >> q;

    vector < int > employee(n);
    vector< int > buckets(10000000, 0);

    // salary = key, number of employees with this salary = value
    map < int, int> salary2freq;

    for(int  i = 0 ; i < n; i++)
    {
        int salary;
        cin >> salary;

        employee[i] = salary;
        salary2freq[salary]++;

        buckets[bucket_no(salary)]++;
    }
    SegTree<Node1, Update1> sgt = SegTree<Node1, Update1>(10000000, buckets);
    while(q--)
    {
        char ch;
        cin >> ch;
        if(ch == '!'){
            int k,x;
            cin >> k >> x;
            int prev_salary = employee[k-1];
            employee[k-1] = x;

            int prev_bucket = bucket_no(prev_salary);
            int new_bucket = bucket_no(x);
            sgt.make_update(prev_bucket, -1);
            sgt.make_update(new_bucket, 1);
            salary2freq[prev_salary]--;
            salary2freq[x]++;
        }
        else{
            int a,b;
            cin >> a >> b;

            int lbucket = bucket_no(a);
            int rbucket = bucket_no(b);

            int ans = calc(a, min((lbucket+1)*100, b), salary2freq);
            ans  = ans + ((lbucket!=rbucket) ? calc(max(a, rbucket*100 + 1), b, salary2freq) : 0);
            ans  = ans + sgt.make_query(lbucket+1, rbucket-1).val;

            cout << ans << '\n';
        }
    }

    return 0;
}