#include <iostream>
#include <queue>
#include <vector>
#include <string>
#define MAX 1002
using namespace std;

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