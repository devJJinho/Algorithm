#include <iostream>
#define MAX 10000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.26

*난이도 : S1
*개인 풀이 시간 : 1hour
*개인 난이도 : 3/5 
*분류 : dp, dp 중에서도 덮어쓰는 dp
*풀이 : 배열 한줄만 유지하는 dp를 사용해서 풀이함.
*느낀점 : dp[i]는 i를 만드는 경우의 수를 의미한다.
        처음에 dp[7]=dp[6]+dp[1]
                    +dp[5]+dp[2]
                    +dp[4]+dp[3]
        의 합이라 생각했으나 정의를 다시 돌아보면 dp[i]는 i까지 만드는 경우이다.
        때문에 dp[i+1]은 dp[i]에서 코인을 써서 dp[i+1]을 만들 수 있냐는 것 단위가 1코인 있으면 가능하다.
        포문의 순서에 따라 
        1) k만큼 돌면서 각각 코인을 순회하며 현재 값에서 코인 만큼 뺀곳에 있는 값이 있으면 +1;
        2) 코인만큼 돌면서 코인 값보다 큰 값을 순회하며 (현재위치-코인값)만큼을 더해준다.

        순수 dp로 한다면 int dp[100][10001] {dp(i,k) i번째 코인을 사용하여 k를 만들 수 있는 경우}로 하겠지만
        전체부분에서 바로 직전만 필요하기 때문에 1차월 배열에서 겹쳐쓰는 것으로 충분하다.

        1차원 dp와 2차원 dp의 점화식이 약간 다르다. 잘 이해하고 넘어갈 필요가 있다.
*/

int dp[MAX+2]={0};

int main(){
int coin[100];
int n,k;
cin>>n>>k;
for(int i=0;i<n;i++){
    cin>>coin[i];
}
dp[0]=1;
for(int j=0;j<n;j++){
    for(int i=coin[j];i<=k;i++){
        dp[i]=dp[i]+dp[i-coin[j]];
    }
}
cout<<dp[k]<<endl;
}

/*

//// dp[i][k]= dp[i-1][k]   (if k<c[i])  =>  k보다 큰 코인값을 k를 만들수 없기 때문에
////           dp[i][k-c[i]]+dp[i-1][k] (if k>=c[i])  =>  dp[i]를 굳이 사용 안해도 dp[i-1]에서 k만끔 올 수 있기 때문에 더하고, 코인만큼 올 수 있는 만큼을 더한다.
////
//// 지금 원하는게 K값을 내는데 특정 i를 썼는지 안썼는지 찾는게 아니다
//// 경우의 수 모든 조합에 대해서 대입해보고 k를 찾는게 아니다 
//// 정확히 말하면 코인 1개(모든 코인이 가능함)을 추가하면서 특정 값 k가 몇번 나오는지 체크하는 것


int dp[100][MAX+2]={0};

int main(){
int coin[100];
int n,k;
cin>>n>>k;
for(int i=0;i<n;i++){
    cin>>coin[i];
}
dp[0]=1;
for(int j=0;j<n;j++){
    for(int i=coin[j];i<=k;i++){
        dp[i]=dp[i]+dp[i-coin[j]];
    }
}
cout<<dp[k]<<endl;
}

*/