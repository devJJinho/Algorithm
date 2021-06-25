#include <iostream>
#include <queue>
#include <vector>
#include <string>
#define MAX 1002
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.06.25

*난이도 : G4
*개인 풀이 시간 : 4hr 
*개인 난이도 : 2/5 
*분류 : BFS(최단거리) 변형
*풀이 : 벽을 부셨는지 안부셨는지까지 queue에 넣고 돌린다. 안 부셨으면 근처 벽을 하나 부셔서 큐에 넣을 수 있음.
*느낀점 : 입력 받은 x,y 좌표가 (1,1)에서 시작할때 내부적으로는 배열 [0][0]에 넣을지 [1][1]에 넣을 지 고민이 많이 필요해보인다.
        
*/

int row,col;
int map[MAX][MAX];
int isVisited[MAX][MAX][2]={0};
//상하좌우
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

struct info{
    bool isBreaked;
    int x,y;
};

bool isValid(int x, int y){
    return x<=col&&x>=1&&y<=row&&y>=1;
}

queue<info> nodeQueue;

int main(){
    int i,j;
    cin>>row>>col;
    for(i=1;i<=row;i++){
        string a;
        cin>>a;
        for(j=1;j<=col;j++){
            map[i][j]=a[j-1]-'0';
        }
    }
    
    nodeQueue.push({false,1,1});
    isVisited[1][1][0]=1;

    while(!nodeQueue.empty()){
        info curInfo=nodeQueue.front();
        nodeQueue.pop();
        int x=curInfo.x;
        int y=curInfo.y;
        bool isBreaked=curInfo.isBreaked;
        
        for(i=0;i<4;i++){
            int nextX=x+dx[i];
            int nextY=y+dy[i];
            if(nextX==col&&nextY==row){
                cout<<isVisited[y][x][isBreaked]+1<<endl;
                return 0;
            }
            if(isValid(nextX,nextY)){
                if(map[nextY][nextX]==0&&!isVisited[nextY][nextX][isBreaked]){
                    nodeQueue.push({isBreaked,nextX,nextY});
                    isVisited[nextY][nextX][isBreaked]=isVisited[y][x][isBreaked]+1;
                }
                
                if(!isBreaked&&map[nextY][nextX]==1&&!isVisited[nextY][nextX][1]){
                    nodeQueue.push({true,nextX,nextY});
                    isVisited[nextY][nextX][1]=isVisited[y][x][isBreaked]+1;
                }
            }
        }
    }
    cout<<"-1"<<endl;
    return 0;
}