#include <iostream>
#include <string.h>
#define MAX 100
#define MOD 10000
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.04.02
*난이도 : G4
*개인 풀이 시간 : 1min 
*개인 난이도 : 3/5 
*분류 : DP
*풀이 : 주석 참조
*느낀점 : DP 배열에서 필요한건 문제에서 묻는 것을 답하기 위해 필요한 인자들!
        
*/

//     날짜 / 파스타 종류 / 해당 파스타 종류가 가능했는지
int dp[MAX][3][2];
int defined[MAX];
int N,K;

//day 날에는 pasta를 먹어. 직전에 pasta를 먹었으면 true야
int recul(int day, int pasta, bool isSame){
    int& ret=dp[day][pasta][isSame];
    //이미 방문했으면 return    
    if(ret != -1) return ret;
    //이미 정해진 파스타 종류와 다르면 더 이상 진행 불가능 => 가능한 경로 0개
    if(defined[day] != -1){
        if(defined[day] != pasta) return ret = 0;
    }
    //기저조건: 끝에 도달하면 경로 하나 생성
	if(day == N-1) {
        return ret=1;
    }
    ret=0;
    //3개의 파스타 종류 각각에 대해 재귀 진행
    //만약 isSame이 True면 pasta가 이미 2번 연속되었단 말이기 때문에 이번 재귀에선 pasta로 진행 X
    for(int i = 0 ; i < 3 ; i++){
        if(isSame && pasta == i) {
        	continue;
        }
        ret += recul(day+1,i,pasta == i);
    }

    ret%=MOD;
    return ret;
}
int main(){
    cin>>N>>K;
    memset(defined,-1,sizeof(defined));
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<K;i++){
        int a,b;
        cin>>a>>b;
        defined[a-1]=b-1;
    }
    int ret=0;
    for(int i = 0 ; i < 3 ; i++){
        ret += recul(0,i,false);
    }
    ret%=MOD;
    cout<<ret<<endl;
}