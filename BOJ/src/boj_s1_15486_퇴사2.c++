#include <iostream>
#define MAX 55

/*
*난이도 : S1
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : DP[i]=p의 정의 : i번째 날에 최대 금액 P를 가질 수 있다.
       점화식 : DP[i+상담날짜]=Max(DP[i+상담날짜],DP[i]+요금)
       최대값이 워낙 크고 입력값도 너무 커서 시간이 많이 걸렸다.
       cin의 성능을 좋게 하기 위해서 버퍼를 조작하는 코드3개를 입력했다.
       그리고 dp의 경우 t의 최대값이 50이기 뗴문에 보수적으로 55길이로 잡고 모듈러 연산을 사용해서 인덱싱 했다. => 메모리 절약
       마지막에 map배열도 없애고, t,p를 입력 받자마자 dp 계산하는 코드로 변경했다.

*느낀점 : dp를 돌려쓰는건 어느정도 익숙해진거 같다 음수의 연산에 대해서도 안정함을 느낀다.
        걱정되는건 cin의 성능이 극악이라 버퍼 조작을 코테환경에서도 해야될지 의문이다.

*/

//////////////////////////////////////////////////////////////
//MAP 배열 없이 받자마자 바로 DP, DP배열 55개 (메모리 : 2020KB 224ms)/
//////////////////////////////////////////////////////////////

using namespace std;

int dp[MAX];

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    int n;
    cin>>n;
   
    for(int i=1;i<=n;i++){
        int t,p;
        cin>>t>>p;
        int index=i%MAX;
        int nday=(i+t)%MAX;
        int minusOne=(index-1+MAX)%MAX;
        if(i-1>0) dp[index]=max(dp[index],dp[minusOne]);
        if(i+t<=n+1)
            dp[nday]=max(dp[nday],dp[index]+p);
    }
    cout<<max(dp[n%MAX],dp[(n+1)%MAX])<<endl;
    return 0;
}


///////////////////////////////////////////
//DP배열 55개로 줄이기 (메모리 : 13740KB 232ms)/
///////////////////////////////////////////

/*

#include <iostream>
#define MAX 55

using namespace std;

int map[1500002][2];
int dp[MAX];

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>map[i][0]>>map[i][1];
    }
    for(int i=1;i<=n;i++){
        int index=i%MAX;
        int nday=(i+map[i][0])%MAX;
        int minusOne=(index-1+MAX)%MAX;
        if(i-1>0) dp[index]=max(dp[index],dp[minusOne]);
        if(i+map[i][0]<=n+1)
            dp[nday]=max(dp[nday],dp[index]+map[i][1]);
    }
    cout<<max(dp[n%MAX],dp[(n+1)%MAX])<<endl;
    return 0;
}
*/


///////////////////////////////////////////
/////DP배열 MAX값 (메모리 : 19600KB 800ms)////
///////////////////////////////////////////

/*

#include <iostream>
#define MAX 55

using namespace std;

int map[1500002][2];
int dp[MAX];

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>map[i][0]>>map[i][1];
    }
    for(int i=1;i<=n;i++){
        int index=i%MAX;
        int nday=(i+map[i][0])%MAX;
        int minusOne=(index-1+MAX)%MAX;
        if(i-1>0) dp[index]=max(dp[index],dp[minusOne]);
        if(i+map[i][0]<=n+1)
            dp[nday]=max(dp[nday],dp[index]+map[i][1]);
    }
    cout<<max(dp[n%MAX],dp[(n+1)%MAX])<<endl;
    return 0;
}
*/