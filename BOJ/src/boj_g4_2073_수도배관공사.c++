#include <iostream>
#include <cstring>
#define MAX 100000
#define INF 999999999
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.04.25

*난이도 : G4
*개인 풀이 시간 : 30/60hour 
*개인 난이도 : 2/5
*분류 : dp
*풀이 : 주석 참조

*느낀점 : 

*/

int dp[MAX + 1];
int D , P;
int main(){
    cin >> D >> P;
    memset(dp , -1 , sizeof(dp));
    int len , capa;
    //가장 처음에 배관을 놓는 경우
    dp[0] = INF;
    while(P--){
        cin >> len >> capa;
        for(int i  = D - len ; i >= 0 ; i--){
            //뒤에서부터 내려오면서
            //앞에서부터 올라가면 한 배관을 여러번 쓴 결과를 얻기 떄문에 위에서부터 내려옴.
            //dp[i]가 -1이 아니면 해당 위치에 끝난 파이프가 있다는 뜻
            if(dp[i] != -1){
                //파이프를 i 부터 i+len까지 연장한다
                if(dp[i + len] == -1){
                    //만약 연장되는 장소가 처음 방문하는 곳이면 파이프의 최소값으로 갱신
                    dp[i + len] = min(dp[i] , capa);
                }
                else{
                    //만약 해당 자리에 있다면 연장된 파이프의 최소값과 원래 있는 값 비교해서 큰 값을
                    dp[i + len] = max(dp[i + len] , min(dp[i] , capa));
                }
            }
        }
    }
    cout << dp[D] << endl;
}