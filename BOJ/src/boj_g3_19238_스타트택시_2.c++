#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define MAX 20
#define WALL 1
using namespace std;



struct INFO{
    int x,y,dist;
    bool operator<(const INFO& b)const{
        if(dist != b.dist) return dist > b.dist;
        if(y != b.y) return y > b.y;
        return x > b.x;
    };
};
struct NODE{
    int x,y;
};
int N,M,GAS;
int map[MAX][MAX];
vector<NODE> desti;
NODE taxi;
priority_queue<INFO> pq;
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

bool isInside(int x,int y){
    return x >= 0 && x < N && y >= 0 && y < N;
}

void searchPass(){
    bool visited[N][N];
    memset(visited,0,sizeof(visited));

    queue<NODE> que;
    que.push(taxi);
    int depth=-1;
    visited[taxi.y][taxi.x]=true;
    while(!que.empty()){
        int size=que.size();
        ++depth;
        for(int i = 0 ; i < size ; i++){
            NODE cur=que.front();
            que.pop();
            if(map[cur.y][cur.x] > 1) 
            	pq.push({cur.x,cur.y,depth});
            for(int dir = 0 ; dir < 4 ; dir++){
                int nx = cur.x + dx[dir];
                int ny = cur.y + dy[dir];
                if(!isInside(nx,ny) || map[ny][nx] == WALL || visited[ny][nx]) continue;
                que.push({nx,ny});
                visited[ny][nx] = true;
            }
        }
        if(pq.size()) return;
    }
}

int searchDist(int idx){
    bool visited[N][N];
    memset(visited,0,sizeof(visited));

    queue<NODE> que;
    que.push(taxi);
    int depth=-1;
    visited[taxi.y][taxi.x]=true;
    bool isFind=false;
    while(!que.empty() && !isFind){
        int size=que.size();
        ++depth;
        for(int i = 0 ; i < size ; i++){
            NODE cur=que.front();
            que.pop();
            if(cur.x == desti[idx].x && cur.y == desti[idx].y){
                isFind=true;
                break;
            }
            for(int dir = 0 ; dir < 4 ; dir++){
                int nx = cur.x + dx[dir];
                int ny = cur.y + dy[dir];
                if(!isInside(nx,ny) || map[ny][nx] == WALL || visited[ny][nx]) continue;
                que.push({nx,ny});
                visited[ny][nx] = true;
            }
        }
    }
    return isFind == false ? -1 : depth;
}

bool solution(){
    pq=priority_queue<INFO>();
    searchPass();
    if(pq.size() == 0) return false;
    INFO top=pq.top();
    if(top.dist >= GAS) return false;
    GAS -= top.dist;
    taxi = {top.x,top.y};

    int passIdx=map[top.y][top.x];
    int distance = searchDist(passIdx);
    //도착지까지 못갈때도 체크해야됨 
    if(distance == -1 || distance > GAS) return false;
    GAS += distance;
    taxi = {desti[passIdx].x,desti[passIdx].y};
	map[top.y][top.x] = 0;
    return true;
}

int main(){
    cin>>N>>M>>GAS;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            cin>>map[i][j];
        }
    }
    int y,x;
    cin>>y>>x;
    taxi={x-1,y-1};

    desti.resize(M+3);
    int cnt=2;
    int a,b,c,d;
    for(int i = 0 ; i < M ; i++){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        a--; b--; c--; d--;
        map[a][b] = cnt;
        desti[cnt]={d,c};
        cnt++;
    }
    cnt = 0;
    for( ; cnt < M ; cnt++){
        if(!solution()) break;
    }
    cout<<(cnt == M ? GAS : -1)<<endl;
}