#include <iostream>
#include <string.h>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.29
*난이도 : G4
*개인 풀이 시간 : 0.5hour
*개인 난이도 : 2/5 
*분류 : Dp, 메모이제이션
*풀이 : 경로의 수를 묻기 때문에 도착지에 도달했을 때 return 1
       가능한 경로가 늘어나는 경우기 때문에 사방에 대해서 가능한 경우의 합을 구함
       weight[i][j]의 의미는 해당 지점에서 도착지까지의 경로의 수.

*느낀점 : 
    
*/

int M,N;
int map[MAX][MAX];
int weight[MAX][MAX];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

bool isInside(int x,int y){
    return x>=0&&x<N&&y>=0&&y<M;
}
int recul(int x,int y){
    if(weight[y][x]!=-1) return weight[y][x];
    if(x==N-1&&y==M-1){
        return weight[y][x]=1;
    }
    int res=0;
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(!isInside(nx,ny)||map[y][x]<=map[ny][nx]) continue;
        res+=recul(nx,ny);
    }
    return weight[y][x]=res;
}

int main(){
    cin>>M>>N;
    memset(weight,-1,sizeof(weight));
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++)
            scanf("%d",&map[i][j]);
    }
    cout<<recul(0,0)<<endl;
}