#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define INF 9999999
#define MAX 101
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  21/09/20

*난이도 : G1
*개인 풀이 시간 : 2hour
*개인 난이도 : 2/5 
*분류 : 구현, BFS, 증명
*풀이 : 최단거리를 물었기 때문에 둘 중 하나를 최단거리로 연결하고 나머지를 연결하려고 했을때 최단거리가 나온다. 이것을 각각 해보면 된다.
       그 외 다른 경우는 생각하지 않아도 되는 것이 만약 
     %

       *  *


        %

        위와 같이 연결되어 있다고 하자 %사이를 연결하는 최단거리 중 하나가 **사이를 통과함으로써 **사이 연결이 불가능하게 만들더라도 
        그 반대 케이스, **사이를 연결하고 %%사이를 연결할 때는 작동되므로 모든 경우에 대해서 체크 가능하다
        디버깅하는데 오랜 걸린 이유 : N x M 그리드라고 하는 경우 좌표를 0<=x<=M 으로 봐야한다. 0부터 시작해서 M까지 연결됨.
*느낀점 : 좌표 설정하는데 오래 걸렸다. 
        그래도 전체적인 알고리즘을 내가 먼저 떠올릴 수 있었다. 

*/

int cntA[MAX][MAX];
int cntB[MAX][MAX];
bool map[MAX][MAX];

struct info{
    int x,y,cnt;
};
int m,n;
int const dx[]={0,0,-1,1};
int const dy[]={-1,1,0,0};

vector<pair<int,int>> A(2);
vector<pair<int,int>> B(2);

bool isValid(int x,int y){
    //좌표가 아니라 그리드가 N*M이라고 하면 그것은 n+1칸, m+1칸을 선언해야한다
    return x>=0&&x<=m&&y>=0&&y<=n;
}
void BFS(vector<pair<int,int>> &points,int cnt[][MAX]){
    queue<info> que;
    que.push({points[0].first,points[0].second,0});
    cnt[points[0].second][points[0].first]=0;
    while(!que.empty()){
        info cur=que.front();
        que.pop();
        if(cur.x==points[1].first&&cur.y==points[1].second) return;
        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if(isValid(nx,ny)){
                //map에 체크되어 있으면 못감
                if(map[ny][nx]) continue;
                if(cnt[ny][nx]>cur.cnt+1){
                    cnt[ny][nx]=cur.cnt+1;
                    que.push({nx,ny,cur.cnt+1});
                }
            }
        }
    }
}
//BFS 결과를 주면 최단경로 중 하나를 return한다.
vector<pair<int,int>> findPath(pair<int,int> end,int cnt[][MAX]){
     vector<pair<int,int>> path;
     int value=cnt[end.second][end.first];
     path.push_back(end);
     while(value){
        for(int i=0;i<4;i++){
            int nx=end.first+dx[i];
            int ny=end.second+dy[i];
            if(isValid(nx,ny)){
                if(cnt[ny][nx]==value-1){
                    end={nx,ny};
                    value-=1;
                    path.push_back(end);
                    continue;
                }
            }
        }
     }
     return path;
}

void setMap(vector<pair<int,int>> &point,bool value){
    map[point[0].second][point[0].first]=map[point[0].second][point[0].first]=value;
    map[point[1].second][point[1].first]=map[point[1].second][point[1].first]=value;
}

int findMinPath(){
    memset(map,false,sizeof(map));
    memset(cntA,INF,sizeof(cntA));
    memset(cntB,INF,sizeof(cntB));
    //B점 방문하지 않고 최단거리 경로 찾기
    setMap(B,true);
    BFS(A,cntA);
    setMap(B,false);
    vector<pair<int,int>> path=findPath(A[1],cntA);
    //A최단거리 중 하나를 못가게 하고 B 최단거리 찾기
    for(auto pt:path){
        map[pt.second][pt.first]=true;
    }
    setMap(A,true);
    BFS(B,cntB);
    int res=cntA[A[1].second][A[1].first]+cntB[B[1].second][B[1].first];
    memset(map,false,sizeof(map));
    memset(cntA,INF,sizeof(cntA));
    memset(cntB,INF,sizeof(cntB));
    setMap(A,true);
    BFS(B,cntB);
    setMap(A,false);
    path=findPath(B[1],cntB);
    for(auto pt:path){
        map[pt.second][pt.first]=true;
    }
    setMap(B,true);
    BFS(A,cntA);
    res=min(res,cntA[A[1].second][A[1].first]+cntB[B[1].second][B[1].first]);
    //최소값 return
    return res;
}

int main(){
    cin>>n>>m;
    vector<pair<int,int>> temp(4);
    for(int i=0;i<4;i++){
        int y,x;
        cin>>y>>x;
        temp[i]={x,y};
    }
    A[0]=temp[0];
    A[1]=temp[1];
    B[0]=temp[2];
    B[1]=temp[3];
    //입력
    int res=findMinPath();
    if(res>=INF) cout<<"IMPOSSIBLE";
    else cout<<res;
    return 0;
}
