#include <iostream>
#include <string.h>
#define MAX 1000
#define MOD 1000000003
using namespace std;

int N,K;
int dp[MAX+3][MAX+3];

/*
@author  :  Jinho Jeong
@date    :  2022.04.03
*난이도 : G4
*개인 풀이 시간 : 1hr 
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : 탑-다운 방식으로 풀이함
*느낀점 : 
        
*/

//자신을 선택하고 다음으로 넘기기 때문에 이에 대한 체크는 다음에서 이루어짐
int recul(int idx,int cnt, bool selectFirst){
    int& ret=dp[idx][cnt];
    if(ret != -1) return ret;
    //cnt가 완성됐으면 return 1;
    if(cnt == K) return ret = 1;
    //만약 첫번째가 선택되었고 idx가 N보다 크거나 같으면 사실상 여기가 마지막. 재귀가 더 진행될 수 없음, 이 때 cnt가 완성되었으면 위 줄에서 return 되었을 것.
    //그게 아니라면 불가능의 의미로 Return 0;
    if(selectFirst && idx >= N) return ret = 0;
    //같은 의미로 N+1보다 큰 Idx에서 cnt가 완성되지 않았으면 return 0;
    if(idx >= N+1) return ret = 0;

    ret=0;
    
    ret += recul(idx+1,cnt,selectFirst);
    ret%=MOD;
    ret += recul(idx+2,cnt+1,selectFirst);
    ret%=MOD;

    return ret;
}
int main(){
    cin>>N>>K;
    memset(dp,-1,sizeof(dp));
    long long int ret=0;
    //첫번째 선택하고 재귀
    ret+=recul(3,1,true);
    memset(dp,-1,sizeof(dp));
    //dp 초기화하고 첫번쨰 선택하지 않고 dp
    ret+=recul(2,0,false);
    ret%=MOD;
    cout<<ret<<endl;
}