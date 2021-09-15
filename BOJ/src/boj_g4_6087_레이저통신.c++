#include <iostream>
#include <deque>
#include <vector>

#define INF 999999999
#define MAX 100
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.15

*난이도 : g4
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 0-1 다익스트라(deque 사용), 구현
*풀이 : 
        거울 설치에 따른 가중치는 1또는 0이기 때문에 BFS를 활용한 0-1 다익스트라 알고리즘으로 풀었다.
        방문 순서가 최소가중치 순서를 따르기 때문에 한번 방문한 곳을 다시 방문 할 필요가 없다.
        visited 배열을 [y][x][4]로 두고 한 점에 4방향에서 들어오는 값을 저장했다. 때문에 거울이 어떤 방향인지 신경쓸 필요가 없었다. 
        사실 bfs 중에 목표 지점을 만나면 바로 return 해도 무방하다. 최저 순이기 때문.

*느낀점 : 
        입력값이 항상 row -> col 순이진 않다. 주의해야햔다. 
        
*/

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
char map[MAX][MAX];
int count[MAX][MAX][4];
int row,col;

struct info{
    int x,y,cnt,dir;
};

bool isValid(int x, int y){
    return x>=0&&x<col&&y>=0&&y<row;
}

void BFS(pair<int,int> point){
    deque<info> dq;
    //출발지에서 각 방향으로 출발하는 것은 가중치 0(거울 없이) 가능하기 때문에 넣어준다.
    dq.push_front({point.first,point.second,0,0});
    dq.push_front({point.first,point.second,0,1});
    dq.push_front({point.first,point.second,0,2});
    dq.push_front({point.first,point.second,0,3});
    while(!dq.empty()){
        info cur=dq.front();
        dq.pop_front();
        int x=cur.x;
        int y=cur.y;
        int cnt=cur.cnt;
        int dir=cur.dir;
        //각 좌표에 대해 한번만 실행되기 때문에 여기서 visited 배열을 초기화한다.
        count[y][x][dir]=cnt;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(isValid(nx,ny)){
                //벽이면 진행하지 못한다.
                if(map[ny][nx]=='*') continue;
                //방문한 곳이면 다시 방문하지 않는다. deque 사용으로 최소 가중치로 이미 방문했기 때문
                if(count[ny][nx][i]!=INF) continue;
                //같은 방향에 대해선 가중치 증가 없이 추가해준다.
                if(i==dir){
                    dq.push_front({nx,ny,cnt,dir});
                    continue;
                }
                //다른 방향이라면 가중치를 하나 증가하고 각 방향별로 넣어준다.
                dq.push_back({nx,ny,cnt+1,i});
            }
        }
    }
}

int main(){
    cin>>col>>row;
    vector<pair<int,int>> points;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>map[i][j];
            if(map[i][j]=='C')
                points.push_back({j,i});
            count[i][j][0]=count[i][j][1]=count[i][j][2]=count[i][j][3]=INF;
        }
    }
    BFS(points[0]);
    int gx=points[1].first;
    int gy=points[1].second;
    int min=INF;
    for(int i=0;i<4;i++)
        if(count[gy][gx][i]<min) min=count[gy][gx][i];
    cout<<min<<endl;
    return 0;
}



// 바로 return 코드 //

/*

#include <iostream>
#include <deque>
#include <vector>

#define INF 999999999
#define MAX 100
using namespace std;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
char map[MAX][MAX];
int count[MAX][MAX][4];
int row,col;

struct info{
    int x,y,cnt,dir;
};

bool isValid(int x, int y){
    return x>=0&&x<col&&y>=0&&y<row;
}

int BFS(pair<int,int> point1,pair<int,int> point2){
    int gx=point2.first;
    int gy=point2.second;
    deque<info> dq;
    dq.push_front({point1.first,point1.second,0,0});
    dq.push_front({point1.first,point1.second,0,1});
    dq.push_front({point1.first,point1.second,0,2});
    dq.push_front({point1.first,point1.second,0,3});
    while(!dq.empty()){
        info cur=dq.front();
        dq.pop_front();
        int x=cur.x;
        int y=cur.y;
        int cnt=cur.cnt;
        int dir=cur.dir;
        count[y][x][dir]=cnt;
        if(x==gx&&y==gy) return cnt;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(isValid(nx,ny)){
                if(map[ny][nx]=='*') continue;
                if(count[ny][nx][i]!=INF) continue;
                if(i==dir){
                    dq.push_front({nx,ny,cnt,dir});
                    continue;
                }
                dq.push_back({nx,ny,cnt+1,i});
            }
        }
    }
}

int main(){
    cin>>col>>row;
    vector<pair<int,int>> points;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>map[i][j];
            if(map[i][j]=='C')
                points.push_back({j,i});
            count[i][j][0]=count[i][j][1]=count[i][j][2]=count[i][j][3]=INF;
        }
    }
    cout<<BFS(points[0],points[1])<<endl;
    return 0;
}

*/