/*
 
@author  :  Jinho Jeong
@date    :  2022.01.24

*난이도 : Silver 5
*개인 풀이 시간 : 1hour
*개인 난이도 : 3/5
*분류 : 오버플로우처리, 수학, 조합, dp
*풀이 : 처음엔 n!/(n-r)!*r! 의 항 각각을 계산해서 풀었더니 unsigned long long에서도 오버플로우가 났음.
       때문에 위 식을 정리해서 r개 만큼 곱하고 나누는 과정을 통해 long long 변수 하나로 연산이 가능했음.
       dp를 활용한 방법도 있어서 풀이해봤음. MAX가 30이기 때문에 dp에 필요한 자료구조의 크기는 작은편.

*느낀점 : 간단한 문제였지만 막히니까 많은 시간이 소모됐음. 풀 줄 알면 쉽고 아니면 정말 어려운 문제의 전형임.
        
*/

// 수학 수식 사용
#include <iostream>
using namespace std;

int main() {
    int cs;
    cin>>cs;
    while(cs--){
        int n,m;
        cin>>n>>m;
        long long res=1;
        for(int i=0;i<n;i++){
            res*=m-i;
            res/=i+1;
        }
        cout<<res<<endl;
    }
}

//DP 사용
#include <iostream>
#define MAX 30

using namespace std;

long long dp[MAX][MAX];

int main(){
    int cs;
    cin>>cs;
    dp[1][1]=1;
    for(int i=0;i<MAX;i++)
        dp[i][0]=1;
    for(int i=2;i<MAX;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
        }
    }
    while(cs--){
        int n,m;
        cin>>n>>m;
        cout<<dp[m][n]<<endl;
    }
}