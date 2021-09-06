#include <iostream>
#include <string>
#define MAX 5000
#define MOD 1000000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.02

*난이도 : S1
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : 경우의 수이기 때문에 1차원 배열 dp에서 분기가 되는 이전 경우의 수를 더해가며 값을 찾는다.
*느낀점 : 특수 경우(이 문제에선 0에 대한 처리, input이 없을때 처리)에 대한 처리르 더 섬세하게 할 필요가 있다.
*/

int dp[MAX+5]={0};
int map[MAX+5];
int len;
int find(){
    if(map[1]==0||len==0) return 0;
    dp[0]=dp[1]=1;
    for(int i=2;i<=len;i++){
        int value=map[i-1]*10+map[i];
        //0을 만난 경우 무조건 두자리로 만들어야한다.
        //26초과이면 알파벳과 대응되지 않기 때문에 불가능
        if(map[i]==0){
            if(value>26||value<1) return 0;
            //가능하면 dp[i]와 dp[i-1]이 묶이기 때문에 dp[i]의 값은 dp[i-2]
            dp[i]=dp[i-2];
        }
        else{
            //이전 경우의 수를 가져오고
            dp[i]=dp[i-1];
            //두자리고 가능하다면 그 경우의 수도 더해준다.
            if(map[i-1]&&(value<=26&&value>=1)) {
                dp[i]+=dp[i-2];
            }
        }
        dp[i]%=MOD;
    }
    return dp[len];
}

int main(){
    string a;
    cin>>a;
    len=a.length();
    for(int i=0;i<len;i++)
        map[i+1]=a[i]-'0';
    cout<<find()<<endl;
    return 0;
}