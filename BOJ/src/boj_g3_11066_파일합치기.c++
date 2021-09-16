#include <iostream>
#include <vector>
#define INF 99999999
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.16

*난이도 : G3
*개인 풀이 시간 : 3hr
*개인 난이도 : 5/5 
*분류 : DP
*풀이 : 
*느낀점 : 괄호추가하기3과 비슷한 문제라 코딩에는 20분이 채 안걸렸지만 각 단계의 누적이라는 개념에서 막혀서 한참 고생했다.
        아직도 완벽히 이해되진 않았다. 
        
        ???: 3개 1개를 합친다 =>  3개를 위해선 2개 1개가 필요하다 
        dp의 값은 i~j까지 합치는데 드는 비용이다. 
        dp[i]가 나중에 쓰일때 dp[i]는 그 하위 비용을 모두 포함한다. 하지만 dp[i]스스로의 비용은 어떠한가?? dp[i+1]에서 dp[i]를 사용하고자 할때 dp[i]는 하위 경우+자기 자신을 선택한 경우 모두를 포함하고 있는가?

*/


void cal(vector<vector<int>> &dp,vector<int> &sum,int k){
    for(int d=1;d<k;d++){
        for(int tx=0;tx+d<k;tx++){
            int ty=tx+d;
            for(int mid=tx;mid<ty;mid++){
           
                //dp[i][j]=i~j를 합쳤을때의 비용이다. 그래서 부분합으로 i~j까지 각 경우를 모두 더하고, 그 하위 연산의 최소를 구한다.
                //이것을 괄호추가하기3과 같이 풀었으면 답은 모든 항의 합만 나올 것이다. 항상 똑같다.
                //괄호추가하기3이 아래와 같이 풀이된 이유는 연산자에 따라 순서가 바뀌었을 때 다른 값이 나왔기 때문이다.
                //이 문제에선 +하기 연산만 있는 수식에 괄호를 씌워서 순서를 다르게 더하는 것과 같다 => 항상 같은 값
                //하지만 여기서는 덧셈의 순서에 따라 영향이 있다. 괄호추가하기3에선 연산자에 의한 차이였다면 여기선 먼저 더해지면 단계를 거듭할 수록 그 값이 몇번이고 더 더해지게 된다.
                //그래서 그런 모든 경우에 대해서 조사하고 최소값을 찾기 위해 dp를 사용했다. 

                // 1,2,3,4 =10  => 더하기만 해선 값이 똑같다.

                // (1,2) (3,4) = 10+3+7=17 => 값이 달라진다 어떻게 더하느냐에 따라 값이 다르다 4개를 더한다면 (1개,3개) (2개,2개)에 경우에 대해 조사해볼 것이다. 그러기 위해선 이전 경우가 메모이제이션으로 저장되어 있음 편할것이다.

                // 1 (2,3,4) => dp(1)과 dp(2~4) dp(2~4)에는 항상 최소값이 들어있다.
                // 1 ((2,3),4)) => 10+1+2+3+5+4+9 =34
                dp[tx][ty]=min(dp[tx][ty],dp[tx][mid]+dp[mid+1][ty]+sum[ty]-(tx-1<0?0:sum[tx-1]));
            }
        }
    }
}

int main(){
    int cs;
    cin>>cs;
    while(cs--){
        int k;
        cin>>k;
        vector<vector<int>> dp(k,vector<int>(k,INF));
        vector<int> sum(k,0);
        vector<int> input(k);
        for(int i=0;i<k;i++){
            cin>>input[i];
            dp[i][i]=0;
        }
        sum[0]=input[0];
        for(int i=1;i<k;i++)
            sum[i]=sum[i-1]+input[i];
        cal(dp,sum,k);
        cout<<dp[0][k-1]<<endl;
    }
}

/*
///부분합을 생각하지 못한 경우///
이 코드에 바로 부분합 개념을 넣는다면 dp 값의 초기화로 인해 합이 중복되었다.
*/

#include <iostream>
#include <vector>
#define INF 99999999
using namespace std;
void cal(vector<vector<int>> &dp, vector<int> &input,vector<int> &sum,int k){
    for(int j=1;j<k;j++){
        for(int i=0;i<k-j;i++){
            for(int k=0;k<j;k++){
                dp[i][i+j]=min(dp[i][i+j],dp[i][i+k]+dp[i+k+1][i+j]+sum[i+j]-sum[i]);
            }
        }
    }
}

int main(){
    int cs;
    cin>>cs;
    while(cs--){
        int k;
        cin>>k;
        vector<vector<int>> dp(k,vector<int>(k,INF));
        vector<int> sum(k,0);
        vector<int> input(k);
        for(int i=0;i<k;i++){
            cin>>input[i];
            //dp값의 초기화
            dp[i][i]=input[i];
        }
        sum[0]=input[0];
        for(int i=1;i<k;i++){
            sum[i]=sum[i-1]+input[i];
        }
        cal(dp,input,sum,k);
        cout<<dp[0][k-1]<<endl;
    }
}

/*
///분기 시점을 따로 기록하고, 답을 찾은 후에 재귀로 내려가며 더한 코드///
이 코드의 맹점은 : dp[i][j]의 값이 줄어들때만 분기점을 기록한다. 만약 dp[i][j]의 값은 같지만 순서가 다른 경우 재귀를 타고 내려가면 다른 결과를 얻게된다..
*/


#include <iostream>
#include <vector>
#define INF 99999999
using namespace std;

void cal(vector<vector<int>> &dp, vector<int> &input,vector<vector<int>> &parent,int k){
    for(int j=1;j<k;j++){
        for(int i=0;i<k-j;i++){
            for(int k=0;k<j;k++){
                if(dp[i][i+k]+dp[i+k+1][i+j]<dp[i][i+j]){
                    dp[i][i+j]=dp[i][i+k]+dp[i+k+1][i+j];
                    parent[i][i+j]=k;
                }
            }
        }
    }
}

int calEachLayer(vector<vector<int>> &dp,vector<vector<int>> &parent,int s,int e,int k){
    if(s==e&&s==k)
        return dp[s][s];
    int sum=0;
    sum+=dp[s][e];
    sum+=calEachLayer(dp,parent,s,k,parent[s][k]);
    sum+=calEachLayer(dp,parent,k+1,e,parent[k+1][e]);
    return sum;
}
int main(){
    int cs;
    cin>>cs;
    while(cs--){
        int k;
        cin>>k;
        vector<vector<int>> dp(k,vector<int>(k,INF));
        vector<vector<int>> parent(k,vector<int>(k));
        vector<int> input(k);
        for(int i=0;i<k;i++){
            cin>>input[i];
            dp[i][i]=input[i];
        }
        cal(dp,input,k);
        cout<<calEachLayer(dp,parent,0,k-1,parent[0][k-1])<<endl;
    }
}