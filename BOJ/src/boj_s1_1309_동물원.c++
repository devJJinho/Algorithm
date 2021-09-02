#include <iostream>
#define MAX 100001
#define MOD 9901
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.02

*난이도 : S1
*개인 풀이 시간 : 10min
*개인 난이도 : 1/5 
*분류 : DP
*풀이 : 사자를 놓을 수 있는 모양을 정하고 그것으로 dp를 돌린 것이 주요했다.
*느낀점 : 경우의 수의 경우 수의 증가는 거의 대부분 이전의 경우의 수를 더함으로써 생성된다
        새로운 i에서 어떤 것을 발견했다고 ++1 하는 경우 보단, d[i]=d[i-1]인 경우가 더 많다
        만약 2칸씩 띄워서 나에게 도착했다고 하면 d[i]+=d[i-2] 이런식으로 말이다.
*/

int dp[MAX][3];

int main(){
    int n;
    cin>>n;
    dp[1][0]=dp[1][1]=dp[1][2]=1;
    for(int i=2;i<=n;i++){
        dp[i][1]=(dp[i-1][0]+dp[i-1][2])%MOD;
        dp[i][0]=(dp[i][1]+dp[i-1][1])%MOD;
        dp[i][2]=(dp[i-1][0]+dp[i-1][1])%MOD;
    }
    cout<<(dp[n][0]+dp[n][1]+dp[n][2])%MOD<<endl;
}