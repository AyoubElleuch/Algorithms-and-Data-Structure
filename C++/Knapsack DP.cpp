#include<iostream>
#include<vector>

typedef unsigned long long ull;
typedef long long ll;


using namespace std;


ll max(ll a, ll b){
    if(a<b) return b;
    return a;
}

int main(){
    int n, w;
    cin >> n >> w;
    vector<int> W(n+1), c(n+1);
    vector<vector<ll>> dp(n+1, vector<ll>(w+1, 0));
    for(int i=0; i<n; i++){
        cin >> W[i];
    }
    for(int i=0; i<n; i++){
        cin >> c[i];
    }   
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=w; j++){
            if(j>=W[i-1]){
                dp[i][j]=max(c[i-1]+dp[i-1][j-W[i-1]], dp[i-1][j]);
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
            
        }
    }

    ll m = dp[n][w];
    if(m==0){
        cout << 0;
        return 0;
    }
    vector<int> ans;
    while(m>0){
        while(dp[n][w]==dp[n-1][w]){
            n=n-1;
        }
        ans.push_back(n);
        m-=c[n-1];
        w-=W[n-1];
        n=n-1;
    }
    cout << ans.size() << endl;
    for(int i=int(ans.size())-1; i>=0; i--){
        cout << ans[i] <<  " ";
    }
    return 0;
}   
