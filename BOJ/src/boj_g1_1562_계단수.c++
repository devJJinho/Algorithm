#include <iostream>
#define MOD 1000000000
using namespace std;
//0부터 9까지의 조건을 dp 내에 녹여낼지? 아니면 재귀에서 녹여낼지?

/*
*난이도 : G1
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5 
*분류 : DP, 재귀
*풀이 : 백준 2098 외판원 순회와 비슷했다. 다른점이라면 dp배열에서 한차원이 더 필요했다.
       0~9까지 얼마나 사용했는지를 재귀에 녹이려고 했지만, dp가 현재 상태를 모른다면 어떤 값을 리턴할지, 어떤 부분에서 메모제이션을 써서 재귀를 중간할지 구분이 힘들다.
       그래서 0~9까지 사용의 상태를 나타내기 위해 비트마스크를 사용하고 dp에도 한 축으로 사용했다.
       그 다음 문제는 바로 인덱스이다. 인덱스를 알고 모르고는 큰 차이가 있었다. 
       인덱스가 없는 dp에서 dp[0~9중 방문한 수][현재 수]이다. index 상으로 끝나기 직전에 이 상황을 마주한 것과 초반에 마주한 것은 달라야할 것이다.
       dp의 목적은 중복 계산을 막기 위해서이다.
       만약 6번째 인덱스에서 5,6,7을 남겨두고 현재 수가 3이라면 계단을 만들 수 없다고 dp에 저장해두면 다음 접근때 여기서 재귀를 진행을 막을 수 있을 것이다. 
       그래서 인덱스도 고려하기 위해 dp를 3차원으로 만들었다.

*느낀점 : dp의 구조는 문제에서 묻는 것에 따라 달라짐을 깨달았다. 앞으로도 이런 사고 패턴을 유지해야겠다.
*/

int n;
int dp[1<<10+1][100][10]={0};

int recul(int stat,int index,int cur){
    if(index==n-1){
        if(stat==(1<<10)-1) return 1;
        else return 0;
    }
    if(dp[stat][index][cur]) return dp[stat][index][cur];
    int sum=0;
    if(cur-1>=0)
        sum+=recul(stat|1<<(cur-1),index+1,cur-1);
    if(cur+1<=9)
        sum+=recul(stat|1<<(cur+1),index+1,cur+1);
    sum%=MOD;
    dp[stat][index][cur]=sum;
    return dp[stat][index][cur];
}
int main(){
    cin>>n;
    int sum=0;
    for(int i=1;i<=9;i++){
        sum+=recul(1<<i,0,i);
        sum%=MOD;
    }
    cout<<sum<<endl;
}