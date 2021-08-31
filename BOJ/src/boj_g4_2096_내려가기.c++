#include <iostream>
#include <algorithm>
#define MAX 100000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.31

*난이도 : G4
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : dp, dp중에서도 메모리 절약형 dp
*풀이 : 덧셈이란 것은 앞의 값들이 최대의 값을 추구해 왔다면, 현재 나의 선택에서 최대만 선태하면 최대를 유지할 수 있다.
       dp[i][0]=max(dp[i-1][0],dp[i-1][1]), dp[i][1]=max(3개), dp[i][2]=max(dp[i-1][1],dp[i-1][2])
       직전의 dp값만 있으면 되기 때문에 메모리를 한줄을 두고 덮어쓰며 진행한다.

*느낀점 : dp 점화식을 유도하고 이해하는데 어려움이 있다.. 많이 풀어봐야겠다.
       
*/

int main(){
    int n;
    int a,b,c;
    cin>>n;
    
    int maxDp[3]={0,0,0};
    int minDp[3]={0,0,0};
    for(int i=0;i<n;i++){
        cin>>a>>b>>c;
        maxDp[0]=max(maxDp[0],maxDp[1]);
        maxDp[2]=max(maxDp[1],maxDp[2]);
        maxDp[1]=max(maxDp[0],maxDp[2])+b;
        maxDp[0]+=a;
        maxDp[2]+=c;
        
        minDp[0]=min(minDp[0],minDp[1]);
        minDp[2]=min(minDp[1],minDp[2]);
        minDp[1]=min(minDp[0],minDp[2])+b;
        minDp[0]+=a;
        minDp[2]+=c;
    }
    cout<<max({maxDp[0],maxDp[1],maxDp[2]})<<" "<<min({minDp[0],minDp[1],minDp[2]})<<endl;
    return 0;
}