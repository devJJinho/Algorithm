#include <iostream>
#include <string>
#include <queue>
#define MAX 10

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.20

*난이도 : G2
*개인 풀이 시간 : 5hr 
*개인 난이도 : 2/5 
*분류 : BFS 응용
*풀이 : 두 공을 맵 상에서 실제로 움직이진 않고 queue에서 빼서 움직이기만 했다.
*느낀점 : 결과적으로 처음 생각한대로 구현 했을 때  풀리긴 했다. 하지만 너무 복잡하게 푼 나머지 디버깅이 어려웠다.
        공끼리 맵 상에서 겹치는 경우에 대해 난 별도의 함수로 처리했지만,
        다른 사람의 풀이에선 각각 극점으로 이동 한 후 두 공의 좌표가 같으면 더 먼 거리를 이동한 공의 좌표를 하나 빼는 식으로 구현했다.. 
        다시 한번 풀 필요가 있는 문제다.
        하지만 이번 풀이때 연산자 오버라이딩, 포인터 사용한 점은 좋았다.
*/

struct ballInfo{
    int x,y;
};

struct mapInfo{
    ballInfo red;
    ballInfo blue;
    int cnt;
};

queue<mapInfo> ballQue;
char map[MAX+2][MAX+2];
bool visited[10][10][10][10];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

int row,col;

//맵 내부에 있는지 체크, 다른 공이나 구멍은 신경쓰지 않는다.
bool isValid(ballInfo a,int dir){
    if(map[a.y+dy[dir]][a.x+dx[dir]]=='#') {return false;}
    else {return true;}
}
// 다른 공이 못 움직이는 상태면 이번 이동 때 다음 칸에 다른 공이 있는지 체크해야함. 
bool canMove(ballInfo a,ballInfo b,int dir,bool otherBallMove){
    char next=map[a.y+dy[dir]][a.x+dx[dir]];
    if(next=='#') 
        return false;
    else if(!otherBallMove){ 
        //다음 칸에 다른 공이 멈춰있다면, 더 이상 움직일 수 없음.
        if((a.y+dy[dir])==b.y&&(a.x+dx[dir])==b.x) {
            return false;
        }
        else
            return true;
    }
    else 
        return true;
}
//구조체끼리 비교연산
bool operator!=(ballInfo a, ballInfo b){
    return a.x!=b.x||a.y!=b.y;
}

int bfs(){
    while(!ballQue.empty()){
        mapInfo curMap=ballQue.front();
        ballQue.pop();
        ballInfo curRed=curMap.red;
        ballInfo curBlue=curMap.blue;
        int cnt=curMap.cnt;
        if(cnt>=10) return -1;
        for(int i=0;i<4;i++){
            ballInfo nxRed=curRed;
            ballInfo nxBlue=curBlue;
            int *redX=&nxRed.x;
            int *redY=&nxRed.y;
            int *blueX=&nxBlue.x;
            int *blueY=&nxBlue.y;
            bool didBlueFall=false;
            bool didRedFall=false;
            while(true){
                bool isRedValid=isValid(nxRed,i)||didRedFall;
                bool isBlueValid=isValid(nxBlue,i);
                bool canRedMove=canMove(nxRed,nxBlue,i,isBlueValid);
                bool canBlueMove=canMove(nxBlue,nxRed,i,isRedValid);
                //빨간공이 구멍으로 빠진 경우, 빨간공은 고정시키고 파란 공만 움직인다.
                if((canRedMove&&!didRedFall)||canBlueMove){
                    if(canRedMove&&!didRedFall){
                        *redX+=dx[i];
                        *redY+=dy[i];
                        if(map[*redY][*redX]=='O'){
                            didRedFall=true;
                        }
                    }
                    if(canBlueMove){
                        *blueX+=dx[i];
                        *blueY+=dy[i];
                        //파란공이 구멍으로 빠지면 그 경로는 실패다. break;
                        if(map[*blueY][*blueX]=='O'){
                            didBlueFall=true;
                            break;
                        }
                    }
                }
                else break;
            }
            //위 이동에서 빨간공만 구멍으로 빠진 경우 성공, cnt+1을 리턴한다.
            if(!didBlueFall&&didRedFall) return cnt+1;
            //큐에 넣는 조건 : 방문한 적이 없고, 파란공이 빠지지 않았으며, 파란공 또는 빨간공 중 하나라도 움직였을 때
            if(!visited[nxRed.x][nxRed.y][nxBlue.x][nxBlue.y]&&!didBlueFall&&(curRed!=nxRed||curBlue!=nxBlue)){
                ballQue.push({nxRed,nxBlue,cnt+1});
                visited[nxRed.x][nxRed.y][nxBlue.x][nxBlue.y]=true;
            }
        }
    }
    return -1;
}


int main(){
    int i,j;
    ballInfo red;
    ballInfo blue;
    cin>>row>>col;

    for(i=0;i<row;i++){
        string temp;
        cin>>temp;
        for(j=0;j<col;j++){
            map[i][j]=temp[j];
            if(map[i][j]=='B')blue={j,i};
            if(map[i][j]=='R')red={j,i};
        }
    }
    ballQue.push({red,blue,0});
    visited[red.x][red.y][blue.x][blue.y]=true;
    int ret=bfs();
    cout<<ret<<endl;

    return 0;
}