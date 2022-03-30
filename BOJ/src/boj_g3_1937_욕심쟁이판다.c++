#include <iostream>
#include <string.h>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.30
*난이도 : G3
*개인 풀이 시간 : 0.5hour
*개인 난이도 : 2/5
*분류 : DP
*풀이 : 1520문제와 비슷하지만, 이 문제는 경로의 수가 아니라 최대 이동가능 거리이기 때문에 점화식이 다름

*느낀점 :

*/

int N;
int map[MAX][MAX];
long long weight[MAX][MAX];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

long long recul(int x,int y){
    //이미 방문했으면 계산해둔 값 Return
    if(weight[y][x]!=-1) return weight[y][x];
    long long res=0;
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        //이동 가능한 곳이면 재귀 진행
        //res에서 max를 찾는 이유, 현재 좌표에서 4방에 대해서 더 멀리 갈 수 있는 값을 찾는다
        if(nx>=0&&nx<N&&ny>=0&&ny<N&&map[ny][nx]>map[y][x]){
            res=max(res,recul(nx,ny));
        }
    }
    //+1을 해서 반환하는 이유는, 누군가 나를 호출했다면 그 지점에서 이동 가능한 거리는 최소 (나)를 포함해야됨
    //호출당한 내가 비록 더 진행은 못해서 Res=0이지만, 나까지 왔다는게 depth가 하나 증가되는 것이기 때문에 +1,
    //만약 나에서 더 이동 가능하면 그 depth+(나)
    return weight[y][x]=1+res;
}
int main(){
    cin>>N;
    memset(weight,-1,sizeof(weight));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            scanf("%d",&map[i][j]);
    }
    long long res=0;
    //시작점을 주지 않았기 때문에 전체에 대해서 시작한다.
    //Memoization을 통해서 바로 return 될 수도, 재귀 진행될 수 도 있음
    //특정 지점이 더 낮은 대나무로 둘어쌓여있어 탐색이 진행되지 않을 수도 있기 때문에 전체에 대해서 하는 것.
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res=max(res,recul(j,i));
        }
    }
    cout<<res<<endl;
}