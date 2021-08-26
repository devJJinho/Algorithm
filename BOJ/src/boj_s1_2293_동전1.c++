#include <iostream>
#define MAX 10000
using namespace std;

int dp[MAX+2]={0};

int main(){
int coin[100];
int n,k;
cin>>n>>k;
for(int i=0;i<n;i++){
    cin>>coin[i];
}
dp[0]=1;
for(int j=0;j<n;j++)
    for(int i=coin[j];i<=k;i++){
        dp[i]=dp[i]+dp[i-coin[j]];
    }
}
//코인의 크기만큼 내려가면서 확인해야된다.
//dp[i]+=dp[i-1]를 하면 안된다. 이건 1이 있을때나 가능.
cout<<dp[k]<<endl;
}