#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define min2(a,b) min(a,b)
#define min3(a,b,c) min(a,min(b,c))
#define min4(a,b,c,d) min(min(a,b),min(c,d))
#define print(a,n) for(int i=0;i<n;i++){cout<<a[i];}
#define input(a,n) for(int i =0;i<n;i++){cin>>a[i];}
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define input1(a,n) for(int i =0;i<n;i++){int x;cin>>x;a.pb(x);}
#define all(x) x.begin(), x.end()
#define r return
typedef vector<int>	vi;
ll int m = 998244353;

void solve(){
    ll int a,b;
    cin>>a>>b;
    if(a==3){
        if(b>=6){
            cout<<3<<" "<<6<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    else if(a%2==0){
        if((a+2)<=b){
            cout<<a<<" "<<(a+2)<<endl;
        }
        else cout<<-1<<endl;
    }
    else if(a%3==0){
        if((a+3)<=b){
            cout<<a<<" "<<(a+3)<<endl;
        }
        else cout<<-1<<endl;
    }
    else {
        if((a+1)<=b && (a+3)<=b){
            cout<<(a+1)<<" "<<(a+3)<<endl;
        }
        else cout<<-1<<endl;
    }
    //cout<<endl;
    r;
}
 
int main() {
    ll int t; 
    cin >> t;
    while(t--){
        solve();
    }
    r 0;
}
