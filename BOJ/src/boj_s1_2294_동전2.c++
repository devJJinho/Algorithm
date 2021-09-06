#include <iostream>
#include <vector>
#define INF 2000000
#define MAX 10000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.06

*난이도 : S1
*개인 풀이 시간 : 20min 
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : 동전1에선 가능한 경우의 수였기 때문에 dp[i]를 i원 만들 수 있는 경우의 수로 규정하고 풀었다.
       동전2에선 최소를 물었기 때문에 dp[i]를 i원 만드는데 드는 최소 동전수로 규정하고 풀었다.
*느낀점 : 
       dp의 정의를 스스로 정하고 시작하자.
*/

vector<int> dp(MAX+1,INF);
int coin[101];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>coin[i];
    }
    //j와 동전값이 같다면 0+1 즉 동전 하나로 만들 수 있음을 표현한다.
    dp[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=coin[i];j<=k;j++){
            dp[j]=min(dp[j],dp[j-coin[i]]+1);
        }
    }
    cout<<(dp[k]==INF?-1:dp[k])<<endl;
    return 0;
}