#include <iostream>
#include <queue>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.15

*난이도 : G5
*개인 풀이 시간 : 0.5hour
*개인 난이도 : 2/5 
*분류 : DFS, 구현, 시뮬
*풀이 : 
*느낀점 : 마지막 도형을 제외하고는 Dfs로 풀이 가능했음.
*/

int N,M;
int map[MAX][MAX];
int maxValue;
bool isVisited[MAX][MAX];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
const int lookupDir[2][2]={
    {2,3},
    {0,1}
};
bool isInside(int x,int y){
    return x>=0&&x<M&&y>=0&&y<N;
}
void dfs(int x,int y,int depth,int sum,int preDir){
    if(depth==4){
        if(maxValue<sum) maxValue=sum;
        return;
    }
    if(depth==1){
        //ㅗ모양을 체크하기 위해
        int vertiMax=0;
        int ndir=0;
        for(;ndir<2;ndir++){
            //직전 방향과 수직인 방향으로 두방향 모두 존재할때 직전+현재+수직방향으로 두군데의 합으로 최대값 비교함
            int nx=x+dx[lookupDir[preDir/2][ndir]];
            int ny=y+dy[lookupDir[preDir/2][ndir]];
            if(!isInside(nx,ny)) {
                break;
            }
            vertiMax+=map[ny][nx];
        }
        if(ndir==2) {
            dfs(x,y,depth+3,sum+map[y][x]+vertiMax,ndir);
        }
    }
    //그 외에는 depth 4짜리 Dfs 진행
    isVisited[y][x]=true;
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(!isInside(nx,ny)||isVisited[ny][nx]) continue;
        dfs(nx,ny,depth+1,sum+map[y][x],dir);
    }
    isVisited[y][x]=false;
    //재귀로 하는 것이 visited 배열 초기화가 수월함
}
int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++)
            cin>>map[i][j];
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            //재귀에서 visited를 False시키기 때문에 여기서 매번 visited 배열 전체에 대해 visited false 할 필요는 없음
           dfs(j,i,0,0,0);
        }
    }
    cout<<maxValue<<endl;
}