#include <iostream>
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.17

*난이도 : S1
*개인 풀이 시간 : 20min
*개인 난이도 : 1/5 
*분류 : 재귀, dfs, 백트래킹, 브루트포스
*풀이 : 사용할 수 있는 연산자가 제한적이기 때문에 현재의 선택이 나중에 영향을 줌 따라서 브루트포스 방식 방문하되 백트래킹을 통해 최적화함.

*느낀점 : 기저케이스의 경우가 맞는지에 대한 고민이 있었음. n개의 수에 대해 n-1개의 연산사를 다 배치했을때 하나의 식이 완성되고 이때 기저케이스에 걸리기 때문에 맞다고 봄.

*/

int n;
int num[MAX+1];
int maxValue=-1000000001;
int minValue=1000000001;
// + - x /
int operandCnt[4];

void recul(int index,int value){
    if(index>=n){
        if(value>maxValue) maxValue=value;
        if(value<minValue) minValue=value;
        return;
    }
    for(int i=0;i<4;i++){
        if(!operandCnt[i]) continue;
        int nValue=0;
        switch(i){
            case 0: nValue=value+num[index]; break;
            case 1: nValue=value-num[index]; break;
            case 2: nValue=value*num[index]; break;
            case 3: nValue=value/num[index]; break;
        }
        --operandCnt[i];
        recul(index+1,nValue);
        ++operandCnt[i];
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>num[i];
    for(int i=0;i<4;i++)
        cin>>operandCnt[i];
    recul(1,num[0]);
    cout<<maxValue<<endl<<minValue<<endl;
}