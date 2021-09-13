#include <iostream>
#define MAX 100000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.13

*난이도 : G5
*개인 풀이 시간 : 5hour 
*개인 난이도 : 4/5 
*분류 : DP, 0/1knapsack algorithm
*풀이 : 조건은 물건 a를 넣을수도 있고 안 넣을수도 있다. 판단에 필요한 것은 현재 물건 a를 선택한다면 배낭의 남은 공간에 채울 가치의 최대값.
*느낀점 : 모든 설명은 2차원 배열로 설명하는데, 2차원 배열의 사용이 성능도 안좋다.
        2차원 배열의 기능도 결과적으로 직전 선택과 지금 선택을 비교하기 때문에(지금 i에서 한참 뒤 값을 조회하지 않는다.) 1차원으로 선언해도 무방할 듯 하다.
*/


//1차원 배열로 푼 경우//

int dp[MAX+1]={0};

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        int w,v;
        cin>>w>>v;
        //현재 무게보다 배낭 크기가 작아지는 경우 현재 값이 영향을 끼칠 수 없기 때문에 가능한 범위에서만 for문을 돈다.
        for(int j=k;j>=w;j--){
            //지금 것을 선택한것이 더 큰 값인 경우
            //같은 무게에선 value가 더 큰 것이 이득이다. 그러니 더 좋다면 무조건 현재 물건을 담아서 value를 높힌다.
            if(dp[j]<dp[j-w]+v)
                dp[j]=dp[j-w]+v;
        }
    }
    cout<<dp[k]<<endl;
}

//2차원 배열로 푼 경우//

/*
int dp[100][MAX+1];
//dp[i][j]=v  i번째 물건까지 봤을때 무게 j일때 최대값 v
//점화식 : dp[i][j]=max(i-1까지 봤을때 j의 최대값,i선택 했을때 최대값 dp[i-1][j-w]+v) 
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        int w,v;
        cin>>w>>v;
        for(int j=0;j<=k;j++){
            if(j-w>=0){
                //dp[i-1]인 이유 : 현재까지 최대값은 i-1에 다 있기 때문
                dp[i][j]=max(dp[i-1][j],dp[i][j-w]+v);
            }  
        else    
            dp[i][j]=dp[i-1][j];
        }
    }
    cout<<dp[n-1][k]<<endl;
}
*/