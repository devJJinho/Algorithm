#include <iostream>
#include <string.h>
#define MAX 1000000
#define INF 1000001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.10

*난이도 : S1
*개인 풀이 시간 : 10min
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : ㅂ
*느낀점 : 
*/


int pre[MAX+1];
int dp[MAX+1];
// 수를 -1하면서 끝까지 내려가는 경우는 없음. /3 또는 /2를 하기 위해 수의 미세한 조정만 함
// 때문에 문제에서 최선은 2로 나누며 1로 가는 것, 최악은 3으로 나누며 1로 가는 것.
// 1000000을 3으로만 나누며 간다고 하면 log 3 1000000 = 12.xxx , 하지만 2와 3으로 나누는게 섞여있을 것이기 때문에 나누셈의 depth는 최대 13으로 봐도 무방
int answer[13];
int N;

void recul(int n){
    if(dp[n]!=-1) return;
    int min=INF;
    int minIndex=0;
    if(!(n%3)){
        recul(n/3);
        //최소값을 찾고 그때 참조한 수 기록
        if(min>dp[n/3]+1){
            min=dp[n/3]+1;
            minIndex=n/3;
        }
    }
    if(!(n%2)){
        recul(n/2);
        if(min>dp[n/2]+1){
            min=dp[n/2]+1;
            minIndex=n/2;
        }
    }
    recul(n-1);
    if(min>dp[n-1]+1){
        min=dp[n-1]+1;
        minIndex=n-1;
    }
    //n에 대한 최소값과 이때 사용한 하위 노드의 인덱스 기록
    dp[n]=min;
    pre[n]=minIndex;
}

int main(){
    cin>>N;
    memset(dp,-1,sizeof(dp));
    dp[1]=0;
    pre[1]=-1;
    recul(N);
    cout<<dp[N]<<endl;
    int preIndex=N;
    int resIndex=0;
    //pre 배열을 타고 가면 사용한 수 조회 가능
    while(preIndex!=-1){
        answer[resIndex++]=preIndex;
        preIndex=pre[preIndex];
    }
    for(int i=0;i<resIndex;i++)
        cout<<answer[i]<<" ";
}