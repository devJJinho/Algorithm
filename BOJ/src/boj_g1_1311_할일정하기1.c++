#include <iostream>
#include <string.h>
#define MAX 20
#define INF 99999999
using namespace std; 

/*
@author  :  Jinho Jeong
@date    :  2022.03.16  

*난이도 : G1
*개인 풀이 시간 : 1.5hour 
*개인 난이도 : 3/5 
*분류 : DP
*풀이 :  
*느낀점 :

*/

int dp[1<<MAX];
int cost[MAX][MAX];
int N;

int recul(int stat,int index){
    if(index==N) return 0;
    int &ret=dp[stat];
    if(~ret) return ret;
    ret=INF;
    for(int i=0;i<N;i++){
        if(stat&1<<i) continue;
        ret=min(ret,recul(stat|1<<i,index+1)+cost[index][i]);
    }
    return dp[stat]=ret;
}
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&cost[i][j]);
        }
    }
    memset(dp,-1,sizeof(dp));
    recul(0,0);
    cout<<dp[0]<<endl;
}