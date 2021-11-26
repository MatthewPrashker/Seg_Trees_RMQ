#include <iostream>
using namespace std;
typedef long long ll;
const int MAX_N = 2005;
const int LOG = 20;
 
void buildRMQ(int n, const ll (&A)[MAX_N], ll (&RMQ)[MAX_N][LOG]) {
    for(int i = 0; i < n; i++) {
        RMQ[i][0] = A[i];
    }
 
    for(int l = 1; l < LOG; l++) {
        for(int i = 0; i < n; i++) {
            if(i + (1 << (l - 1)) >= n) {
                RMQ[i][l] = RMQ[i][l - 1];
            } else {
                RMQ[i][l] = min(RMQ[i][l - 1], RMQ[i + (1 << (l - 1))][l - 1]);
            }
        }
    }
    
}
//find first power of 2 which is greater than or equal to d
int log(int d) {
    int ans = 0;
    for(int i = 0; i < 31; i++) {
        if((d >> i)&1) {
            ans = i;
        }
    }
    return ans;
}
int log_arr[MAX_N];
void init_log() {
    for(int i = 0; i < MAX_N; i++) {
        log_arr[i] = log(i);
    }
}
 
 
ll minQuery(int l, int r, const ll (&RMQ)[MAX_N][LOG]) {
    if(l == r) {return RMQ[r][0];}
    int d = log_arr[r - l + 1];
    return min(RMQ[l][d], RMQ[r - (1 << d) + 1][d]);
}

int main() {
    ll A[MAX_N];
    ll RMQ[MAX_N][LOG];
    for(int i = 0; i < 100; i++) {
        A[i] = i;
    }
    buildRMQ(100, A, RMQ);
    cout << minQuery(0,1,RMQ) << "\n";
}