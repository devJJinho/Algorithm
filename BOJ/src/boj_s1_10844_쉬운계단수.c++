#include <iostream>
#define MOD 1000000000
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.03.03

*난이도 : S1
*개인 풀이 시간 : 30min
*개인 난이도 : 3/5 
*분류 : DP, 수학
*풀이 : dp[N][끝자리 숫자]=dp[N-1][끝자리숫자-1]+dp[N-1][끝자리숫자+1]
*느낀점 : 

*/

int dp[2][10]={
    {0,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0}
};
int index[]={-1,1};
int main(){
   int n;
   cin>>n;
   for(int i=1;i<n;i++){
       for(int j=0;j<10;j++){
          int sum=0;
           for(int t=0;t<2;t++){
               if((j+index[t]>=0)&&(j+index[t]<=9)){
                   sum+=dp[(i-1+2)%2][j+index[t]];
               }
           }
          dp[i%2][j]=sum%MOD;
       }
   }
   int sum=0;
   for(int i=0;i<10;i++){
        sum+=dp[(n+1)%2][i];
        sum%=MOD;
   }
   cout<<sum<<endl;
}