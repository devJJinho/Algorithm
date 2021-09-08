#include <iostream>
#define MAX 100000
using namespace std;

/*
*난이도 : S2
*개인 풀이 시간 : 20min
*개인 난이도 : 2/5 
*분류 : DP
*풀이 : dp[i][j]= 스티커[i][j]를 선택했을때 최대값
       dp[i][j]=max(바로 아래 대각선, 한칸 띄운 칸 중 최대값)
       최악의 경우 100000*2 번의 cin을 해야한다. cin 성능이 너무 안좋았다.

*느낀점 : dp 점화식에서 dp[i]를 위해서 dp[i-1], dp[i-2]만 필요하기 때문에 dp 길이를 3으로 둘고 모듈러로 돌아봤다.
        => 메모리상 이점은 있으나 인덱스 계산을 위한 오버해드가 확실히 존재했음.
        더 빠른 cin은 인라인 함수까지 건들여야할거 같은데 현재로선 굳이 필요성은 모르겠다.
*/

int main(){
    int num;
    cin>>num;
    while(num--){
        int n;
        cin>>n;
        int dp[MAX+1][2];
        int map[MAX+1][2];
        for(int i=0;i<2;i++){ 
            for(int j=0;j<n;j++){
                cin>>map[j][i];
            }
        }
        dp[0][0]=map[0][0];
        dp[0][1]=map[0][1];
        for(int i=1;i<n;i++){
            int twoDown=i-2<0?0:max(dp[i-2][0],dp[i-2][1]);
            dp[i][0]=max(dp[i-1][1],twoDown)+map[i][0];
            dp[i][1]=max(dp[i-1][0],twoDown)+map[i][1];
        }
        cout<<max(dp[n-1][0],dp[n-1][1])<<endl;
    }
    return 0;
}


/*

dp 배열 3개만 유지하기;

int main(){
    int num;
    cin>>num;
    while(num--){
        int n;
        cin>>n;
        int dp[3][2];
        int map[MAX+1][2];
        for(int i=0;i<2;i++){ 
            for(int j=0;j<n;j++){
                cin>>map[j][i];
            }
        }
        dp[0][0]=map[0][0];
        dp[0][1]=map[0][1];
        for(int i=1;i<n;i++){
            int index=i%3;
            int twoDown=i-2<0?0:max(dp[(i-2+3)%3][0],dp[(i-2+3)%3][1]);
            dp[index][0]=max(dp[(index-1+3)%3][1],twoDown)+map[i][0];
            dp[index][1]=max(dp[(index-1+3)%3][0],twoDown)+map[i][1];
        }
        cout<<max(dp[(n-1+3)%3][0],dp[(n-1+3)%3][1])<<endl;
    }
    return 0;
}

*/