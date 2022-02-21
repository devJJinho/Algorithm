#include <iostream>
#include <unordered_set>
#define ABS(a) ((a)<0?-(a):(a))
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.17

*난이도 : g3    
*개인 풀이 시간 : 1+1/6houra
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬
*풀이 : 행,열 대한 함수를 따로 두지 않고 열도 행으로 변환 후 하나의 함수로 체크.

*느낀점 : 열을 행으로 바꾸는 아이디어가 나오기까지 많은 시간이 걸림 그 외에는 투포인터를 사용하는 구현으로 느껴졌음

*/

int n,l;
int map[2*MAX+1][MAX+1];

bool checkRoad(int index){
    int pre=map[index][0];
    bool hasSlope[MAX+1];
    for(int i=0;i<n;i++) hasSlope[i]=false;
    for(int col=1;col<n;col++){
        if(ABS(map[index][col]-pre)>1) return false;
        if(map[index][col]==pre-1){
            int nx=col-1;
            for(int cnt=0;cnt<l;cnt++){
                nx+=1;
                if(nx>=n) return false;
                if(map[index][nx]!=pre-1||hasSlope[nx]) return false;
                hasSlope[nx]=true;
            }
        }
        else if(map[index][col]==pre+1){
            int nx=col;
            for(int cnt=0;cnt<l;cnt++){
                nx-=1;
                if(nx<0) return false;
                if(map[index][nx]!=pre||hasSlope[nx]) return false;
                hasSlope[nx]=true;
            }
        }
        pre=map[index][col];
    }
    return true;
}

int main(){
    cin>>n>>l;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&map[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map[n+i][j]=map[j][i];
        }
    }
    int cnt=0;
    for(int i=0;i<2*n;i++){
        if(checkRoad(i)) cnt++;
    }
    cout<<cnt<<endl;
}