#include <iostream>
#define MAX 101
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.10.05

*난이도 : G3
*개인 풀이 시간 : 1hr
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : 처음엔 {dp[메모리]=최소 비용}의 점화식을 가지고 풀이했다. 하지만 M이상의 모든 메모리 중에서 최소 비용을 찾아야되기 때문에 dp배열의 크기가 100(n)*10,000,000(최대값) 이기 때문에 비현실적이다.
       특히나 for문 안에서 역으로 내려올때 가능한 최대값에서부터 내려와야하기 때문에 시간초과의 경우도 생긴다.

       때문에 {dp[비용]=가능한 최대 메모리}의 점화식을 가지고 풀이했다. 매 단계마다 가능한 최대값 100(n)*100(Cmax)에서 역으로 내려오면 되기 때문에 연산도 줄어들었다.

*느낀점 : dp 문제라는 것은 알았으나 비용을 dp축으로 할 생각은 하지 못했다.
*/

int mem[MAX];
int price[MAX];
int dp[10001];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>mem[i];
    }
    for(int i=0;i<n;i++){
        cin>>price[i];
        //밑에서부터 내려가면 수정한 값이 한번 더 쓰이기 때문에 한개의 앱을 여러번 사용한 결과를 낳는다. 때문에 위에서부터 내려온다.
        //이것은 dp를 1차원 배열로 사용해서 그러한 것이고 이차원 배열을 사용하는 경우 새로운 배열에 쓰기 때문에 방향은 상관이 없다.
        for(int j=10000;j>=price[i];j--){
        	dp[j]=max(dp[j],dp[j-price[i]]+mem[i]);
        }
    }
   
   for(int i=0;i<=10000;i++){
	   if(dp[i]>=m){
		   	cout<<dp[i]<<endl;
		   	break;
	   }
   }
   return 0;
}

//{dp[메모리]=최소 비용} 풀이 //

#include <iostream>
#include <cstring>
#define INF 9999999
using namespace std;
int mem[101];
int price[101];
int dp[10000001];
int main(){
    int n,m;
    int sum=0;
    cin>>n>>m;
    memset(dp,INF,sizeof(dp));
    for(int i=0;i<n;i++){
        cin>>mem[i];
        sum+=mem[i];
    }
    for(int i=0;i<n;i++){
        cin>>price[i];
    }
    dp[0]=0;
    for(int i=0;i<n;i++){
        //가능한 최대값 sum에서부터 내려와야함
        for(int j=sum;j>=mem[i];j--){
            if(dp[j]>dp[j-mem[i]]+price[i]) {
            	dp[j]=dp[j-mem[i]]+price[i];
            }
        }
    }
    int res=INF;
    for(int i=m;i<=sum;i++){
        if(dp[i]<res) res=dp[i];
    }
    cout<<res<<endl;
}