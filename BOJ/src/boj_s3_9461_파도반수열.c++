#include <iostream>
#define MAX 101
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2021.09.02

*난이도 : S3
*개인 풀이 시간 : 10min
*개인 난이도 : 2/5 
*분류 : DP, 수학
*풀이 : 간단한 점화식이다. dp[i]=dp[i-1]+dp[i-5];
       다만 피보나치 수열과 같이 값이 기하급수적으로 증가하기 때문에 정답 배열은 long 또는 long long으로 선언되어야한다.
*느낀점 : dp 점화식은 많이 풀어보는 수 밖에 없겠다.

*/

long long dp[MAX]={0,1,1,1,2,2,3,4,5,7,9,};
int main(){
    int n;
    cin>>n;
    while(n--){
        int p;
        cin>>p;
        for(int i=11;i<=p;i++){
            dp[i]=dp[i-1]+dp[i-5];
        }
        cout<<dp[p]<<endl;
    }
    