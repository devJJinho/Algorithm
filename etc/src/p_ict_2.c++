#include <iostream>
#include <queue>
#include <vector>
#define MAX 50
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.01.22

*난이도 : b1
*개인 풀이 시간 : 1.5min 
*개인 난이도 : 2/5 
*분류 : BFS, 단순 계산
*풀이 : 당연히 BFS인줄 알고 풀이했으나, map에서 움직일 때 제약이 없기 때문에 단순 index 계산일 수도 있음. 
       bfs으로 풀이하면 n*n에 대해서 bfs를 수행하기 때문에 비효울적.

*느낀점 : 
        다시 풀이 할 예정
        
*/

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
int map[MAX][MAX];
bool isVisited[MAX][MAX];

struct info{
    int x,y,depth;
};

int findMinPath(int n){
    int searchIndex=1;
    int x=0;
    int y=0;
    int totalCnt=0;
    while(searchIndex<=n*n){
        queue<info> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                isVisited[i][j]=false;
        }
        bool isFind=false;
        q.push({x,y,0});
        while(!q.empty()&&!isFind){
            info curNode=q.front();
            q.pop();
            isVisited[curNode.y][curNode.x]=true;
            for(int dir=0;dir<4&&!isFind;dir++){
                int nx=(curNode.x+dx[dir])%n;
                if(nx<0) nx+=n;
                int ny=(curNode.y+dy[dir])%n;
                if(ny<0) ny+=n;
                if(isVisited[ny][nx]) continue;
                if(map[ny][nx]==searchIndex){
                    totalCnt+=curNode.depth+1;
                    totalCnt++;
                    searchIndex++;
                    isFind=true;
                    x=nx,y=ny;
                    break;
                }
                q.push({nx,ny,curNode.depth+1});
            }
        }
    }
    return totalCnt;
}

int main(){
    // vector<vector<int>> list={{3,5,6},{9,2,7},{4,1,8}};
    // vector<vector<int>> list={{2,3},{4,1}};
    vector<vector<int>> list={{11,9,8,12},{2,15,4,14},{1,10,16,3},{13,7,5,6}};
    int n=list.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map[i][j]=list[i][j];
        }
    }
    cout<<findMinPath(n);
}