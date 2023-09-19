#include<iostream>
#include<string>
#include<vector>
#include<math.h>

using namespace std;

// InsertionSort. Worst case time complexity: O(n²)
void insertionSort(vector<pair<double, int>>& v){
    if(int(v.size())==1 || int(v.size()==0)) return;
    for(int i=1; i<int(v.size()); i++){
        pair<double, int> temp = v[i];
        int k=i-1;
        
        while(k>=0 && v[k].first>temp.first){
            v[k+1]=v[k];
            k--;
        }
        v[k+1]=temp;
    }
    return;
}


// BucketSort. Average case time complexity: Θ(n)
void bucketSort(vector<pair<double, int>>& numbers, int n){
    vector<vector<pair<double, int>>> buckets(n+1, vector<pair<double, int>>(0));
    for(int i = 1; i<=n; i++){
        pair<double, int> p = numbers[i];
        int index = floor(n*p.first);
        buckets[index].push_back(p);
    }
    numbers.clear();
    numbers.push_back(make_pair(0, 0));
    for(int i=0; i<=n; i++){
        insertionSort(buckets[i]);
        for(int j=0; j<int(buckets[i].size()); j++){
            numbers.push_back(buckets[i][j]);
        }
    }
}

int main(){
    long long a, c, m, seed;
    int n;
    cin >> a >> c >> m >> seed;
    cin >> n;
    vector<pair<double, int>> v(n+1);
    long long x0 = seed;
    for(int i=1; i<=n; i++){
        long long xn = (((a)*(x0%m))%m+c)%m;
        x0 = xn;
        double y = fabs((2*xn/double(m))-1);
        v[i]=make_pair(y, i);
    }
    bucketSort(v, n);
    int mid = (n/2);
    cout << v[mid].second << endl;
    return 0;
}
