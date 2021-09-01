#include <iostream>
#define MAX 301
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.01

*난이도 : Silver3
*개인 풀이 시간 : 30min 
*개인 난이도 : 1/5 
*분류 : dp
*풀이 : 2차원 dp를 선언했다. 
       dp[i][0]=한칸씩 이동해서 i에 도착했을때 최대값
       dp[i][1]=두칸씩 이동해서 i에 도착했을때 최대값
       dp[i][0]=dp[i-1][1]+map[i]; //3칸 연속은 안되기 때문에 직전칸은 무조건 2칸 이동해서 도착한 칸이어야 한다.
       dp[i][1]=max(dp[i-2][0],dp[i-2][1])+map[i]; 2칸 이동이기 때문에 2칸 전의 칸에서 최대값+현재값, 두칸 이동은 직전이 한칸이동이든 두칸이동이든 상관없다.
*느낀점 : 점화식 도출은 비교적 수월하였으나, 초기값 설정이 어려웠다.

*/

int map[MAX]={0};
int dp[MAX][2];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>map[i];
    }
    dp[0][0]=dp[0][1]=map[0];
   for(int i=1;i<n;i++){
       dp[i][0]=dp[i-1][1]+map[i];
       //2칸이동의 0을 벗어난 값은 0이다.
       dp[i][1]=max(i-2>=0?dp[i-2][1]:0,i-2>=0?dp[i-2][0]:0)+map[i];
   }
   cout<<max(dp[n-1][0],dp[n-1][1])<<endl;
}