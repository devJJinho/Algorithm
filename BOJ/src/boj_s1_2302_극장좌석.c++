#include <iostream>
#define MAX 40
using namespace std;

/*
*난이도 : S1
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : 한 좌석은 위 아래로 움직일 수 있는데, 한 점에서 두가지를 다 확인하게 되면 중복되게 된다, 위 좌석에서 아래랑 바꾸는 경우랑 같기 때문.
       때문에 한 점에선 아래 방향으로만 비교를 한다. 그리고 경우의 수의 합을 구할 때는 2칸 아래의 값과 더하게 된다. 
       이 이유는 한 좌석과 바로 아래 좌석은 같이 바뀌기 때문에 같은 경우이다. 현재 좌석의 값이 정해지면 바로 아래 좌석의 값도 정해짐.=> 경우의 수를 생성하지 않는다.
       1. dp[i]=dp[i-1]에서 현재 좌석의 값을 그대로 반영하는 경우의 수를 가져온다.
          *****XO  dp[i-1]에는 끝 좌석을 XO로 고정하고 앞의 *****을 정렬한 경우의 수가 들어있음
       2. dp[i]+=dp[i-2]는 끝에가 OX로 변경된 경우 가능한 경우의 수를 더한다. 
          *****OX  OX는 고정이기 때문에 dp[i-2]의 값을 가져옴

*느낀점 : dp로 경우의 수를 계산할 때, 일반적인 상황이라면 dp[i]=dp[i-1] 과 같이 이전 값을 그대로 가져오고
        분기가 생긴다면 그땐 논리상 맞는 값을 dp[i]+={이전 dp값} 더하는 식이다.

*/

struct info{
    int x=0;
    bool isVip=false;
};
info map[MAX+1];
int main(){
     int n,m;
     cin>>n>>m;
     for(int i=0;i<m;i++){
         int vip;
         cin>>vip;
         map[vip].isVip=true;
     }
     map[0].x=map[1].x=1;
     for(int i=2;i<=n;i++){
         map[i].x=map[i-1].x;
         if(!map[i-1].isVip&&!map[i].isVip){
             map[i].x+=map[i-2].x;
         }
     }
     cout<<map[n].x<<endl;
}