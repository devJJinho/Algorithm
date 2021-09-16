#include <iostream>
#include <vector>
#include <algorithm>
#define INF 9999999
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.16

*난이도 : G1
*개인 풀이 시간 : 3hour 
*개인 난이도 : 3/5 
*분류 : DP, 스트링
*풀이 : 괄호를 무제한으로 추가 가능하고 중첩 가능하다는 것은 연산자 우선 순위를 무시한다는 것이다. 
       dp[i][j] : i에서 j까지 계산했을때 최소값 또는 최대값으로 두고 계산을 했다.
       중요한 점은 뺄샘의 경우 음수가 나올 수 있고 최대값이나 최소값은 음수의 최소값에서부터 나올수도 있기 때문에 dpMAX와 dpMIN 각각이 필요했다.
       그리고 음수가 나올수도 있었기 때문에 배열 초기화를 할 때 0이 아닌 음수 최소값으로 초기화를 했어야했다.
*느낀점 : 
       배열의 초기화를 잘못해서 디버깅에 3시간이 들었다.
       가능한 답의 범위를 생각하고 풀이에 영향을 미치지 않는 값을 선택해야 한다.
*/

int formula[20];
vector<vector<int>> dpMAX(20,vector<int>(20,-1*INF));
vector<vector<int>> dpMIN(20,vector<int>(20,INF));
int cal(int a,int b, char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        default : return a*b;
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        char temp;
        cin>>temp;
        formula[i]=(i%2==0)?(temp-'0'):temp;
    }
    for(int i=0;i<n;i+=2){
        dpMAX[i][i]=dpMIN[i][i]=formula[i];
    }
    for(int j=2;j<n;j+=2){
        for(int i=0;i<n-j;i+=2){
            for(int k=1;k<j;k+=2){
                char op=formula[i+k];
                vector<int> temp(4);
                temp[0]=cal(dpMAX[i][i+k-1],dpMAX[i+k+1][i+j],op);
                temp[1]=cal(dpMAX[i][i+k-1],dpMIN[i+k+1][i+j],op);
                temp[2]=cal(dpMIN[i][i+k-1],dpMAX[i+k+1][i+j],op);
                temp[3]=cal(dpMIN[i][i+k-1],dpMIN[i+k+1][i+j],op);
                sort(temp.begin(),temp.end());
                dpMIN[i][j+i]=min(dpMIN[i][j+i],temp[0]);
                dpMAX[i][j+i]=max(dpMAX[i][j+i],temp[3]);
            }
        }
    }
    cout<<dpMAX[0][n-1]<<endl;
}