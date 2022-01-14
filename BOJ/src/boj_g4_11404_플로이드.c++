#include <iostream>
#define MAX 100
#define MAX_VALUE 100001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.12
*난이도 : G4
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : 플로이드 와샬
*풀이 : 플로이드 와샬 문제에서 트릭 2개 존재
       1. 같은 경로에 대해 여러가지 가중치가 들어옴 (이 중 최소를 유지함)
       2. 시작과 끝이 같은 경우는 없음. (플로이드 와샬 코드 내에 시작과 끝이 같은 경우 넘어가는 코드 삽입)
*느낀점 : 지문을 잘 읽고 코드에 반영해야됨. 위 트릭 2개를 처음부터 파악하지 못함. 디버깅 과정에서 찾아냄.

    
*/

int map[MAX+1][MAX+1];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++)
            map[i][j]=MAX_VALUE;
    }
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        map[a][b]=c;
    }
    for(int m=1;m<=n;m++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int temp=map[i][m]+map[m][j];
                if(map[i][j]>temp) map[i][j]=temp;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<map[i][j]<<" ";
        cout<<endl;
    }
}