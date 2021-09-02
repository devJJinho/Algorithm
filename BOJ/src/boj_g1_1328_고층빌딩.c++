#include <iostream>
#define MAX 101
#define MOD 1000000007
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.19

*난이도 : G1
*개인 풀이 시간 : 1.5hour 
*개인 난이도 : 3/5 
*분류 : DP
*풀이 :  dp[n][l][r];
        직전 경우에서의 빌딩의 높이를 1씩 올리자. => 경우의 수는 동일함
        높이가 1인 빌딩을 넣는다. 가능한 경우는 왼쪽 맨앞, 오른쪽 맨앞, 가운데
        왼쪽 맨앞의 경우 n의 수가 하나 적고 현재 경우보다 왼쪽에서 보인느 수가 하나 작은 dp[n-1][l-1][r] 의 경우와 같다
        같은 식으로 오른쪽의 경우 dp[n-1][l][r-1]이다.
        가운데 놓는 경우는 dp[n-1][l][r]*(n-2)이다. 가운데 놓기 때문에 외부로 보이는 l,r의 차이는 없으며 양쪽 끝 값을 제외한 안쪽(n-2)에 높이 1인 빌딩을 놓을 수 있기 때문에.

*느낀점 : 상상도 못하는 점화식이었다.
        문제를 더 작은 단위의 문제로 쪼개서 생각하는게 DP의 핵심이다.

*/

int dp[MAX][MAX][MAX]={0};
int main(){
    int n,l,r;
    cin>>n>>l>>r;

    dp[1][1][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=l;j++){
            for(int k=1;k<=r;k++){
                dp[i][j][k]=((long long)dp[i-1][j][k]*(i-2)+dp[i-1][j-1][k]+dp[i-1][j][k-1])%MOD;
            }
        }
    }
    cout<<dp[n][l][r]<<endl;
    return 0;
}