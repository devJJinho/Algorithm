#include <iostream>
#include <queue>
#define MAX 100
#define INF 999999999

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.01
*난이도 : G3
*개인 풀이 시간 : 2hr
*개인 난이도 : 2/5 
*분류 : BFS, 시뮬, 구현, 삼성문제
*풀이 : 주석 참조

*느낀점 : 해당 좌표로 트랙(맵 상에서 0)인 경우만 que에 넣었더니 트랙 내에서 사방에 대한 정보가 저장되지 않음. 반대 방향(180도)에 대한 정보가 저장되지 않음

*/

struct info{
    int x,y,dir;
};
int map[MAX+1][MAX+1];
int dp[5][MAX+1][MAX+1];
int point[3][2];
int N,M;
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,1,-1};
const int turn[5][2]={
    {},
    {3,4},
    {3,4},
    {1,2},
    {1,2}
};
bool isInside(int x,int y){
    return x>=1&&x<=M&&y>=1&&y<=N;
}

void bfs(){
    queue<info> que;
    que.push({point[1][0],point[0][0],point[2][0]});
    dp[point[2][0]][point[0][0]][point[1][0]]=0;
    while(!que.empty()){
        auto cur=que.front();
        que.pop();
        int x=cur.x;
        int y=cur.y;
        int curCnt=dp[cur.dir][y][x];
        //bfs 특성상 목표 지점 도달하면 그것이 최소값
        if(x==point[1][1]&&y==point[0][1]&&cur.dir==point[2][1]) return;
        for(int i=0;i<2;i++){
            //좌우로 90도씩 회전해서 다시 que에 삽입
            //해당 방향으로 갈 수 없어도 que에 넣는 이유는 180도 반대 방향으로 가기 위해서임
            int ndir=turn[cur.dir][i];
            int nx=x+dx[ndir];
            int ny=y+dy[ndir];
            if(dp[ndir][y][x]>curCnt+1){
                dp[ndir][y][x]=curCnt+1;
                que.push({x,y,ndir});
            }
        }
        //직진 방향으로 3칸 
        int nx=x+dx[cur.dir];
        int ny=y+dy[cur.dir];
        //현재 방향으로 최대 3칸 움직이며 해당 좌표를 que에 삽입
        for(int i=0;i<3&&isInside(nx,ny)&&map[ny][nx]==0;i++){
            if(dp[cur.dir][ny][nx]>curCnt+1){
                que.push({nx,ny,cur.dir});
                //dp가 isVisited 역할도 겸임.
                dp[cur.dir][ny][nx]=curCnt+1;
            }
            nx+=dx[cur.dir];
            ny+=dy[cur.dir];
        }
    }
}
int main(){
    cin>>N>>M;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++)
            scanf("%d",&map[i][j]);
    }
    for(int i=0;i<2;i++)
        scanf("%d %d %d",&point[0][i],&point[1][i],&point[2][i]);
    //3차원 배열 초기화
    for(int i=0;i<5;i++)
        for(int j=1;j<=N;j++)
            for(int k=1;k<=M;k++)
                dp[i][j][k]=INF;
    bfs();
    cout<<dp[point[2][1]][point[0][1]][point[1][1]]<<endl;
}