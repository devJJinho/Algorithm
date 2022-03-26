#include <iostream>
#include <queue>
#include <string.h>
#define MAX 200
#define INF 40001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.25

*난이도 : G4
*개인 풀이 시간 : 1 hour
*개인 난이도 : 2/5 
*분류 : BFS
*풀이 : 
*느낀점 : 
        말의 움직임으로 이동해도 하나의 움직임으로 치기 때문에 bfs가 보장됨. 도착점을 가장 먼저 만나는 경우 최단거리 보장됨
        때문에 bfs를 보장받기 위해 pq를 쓸 필요가 없었음.

        나는 해당 좌표로의 최소값, 그리고 그때의 K 사용 회수를 가지고 visited 여부 판단을 했으나, 다른 풀이의 경우 K 사용 회수만 가지고 visited 여부 판단함.
        즉 해당 좌표에 K를 적게 사용해서 방문했으면 재방문을 허용함.
*/

struct info{
    int x,y,cnt,kCnt;
};
//일반 queue 사용
queue<info> pq;
bool map[MAX+1][MAX+1];
int cMap[MAX+1][MAX+1];
int kMap[MAX+1][MAX+1];

const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
const int lookup[]={-1,1};
int W,H,K;

bool isInside(int x,int y){
    return x>=0&&x<W&&y>=0&&y<H;
}
int main(){
    cin>>K>>W>>H;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            scanf("%d",&map[i][j]);
            cMap[i][j]=kMap[i][j]=INF;
        }
    }
    
    pq.push({0,0,0,0});
    cMap[0][0]=0;
    kMap[0][0]=0;
    int res=-1;
    while(!pq.empty()){
        auto cur=pq.front();
        pq.pop();
        if(cur.x==W-1&&cur.y==H-1) {
            res=cur.cnt;
            break;
        }
        for(int dir=0;dir<4;dir++){
            int nx=cur.x+dx[dir];
            int ny=cur.y+dy[dir];
            if(!isInside(nx,ny)||map[ny][nx]) continue;
            if(cMap[ny][nx]<=cur.cnt+1&&kMap[ny][nx]<=cur.kCnt) continue;
            //여깃서 cMap[ny][nx]를 단축시킨 경우에만 update 되도록 구성했더니 시간 초과 발생함
            cMap[ny][nx]=cur.cnt+1;
            kMap[ny][nx]=cur.kCnt;
            pq.push({nx,ny,cur.cnt+1,cur.kCnt});
        }
        //말의 움직임 구현
        if(cur.kCnt<K){
        	for(int dir=0;dir<4;dir++){
        		int nx=cur.x+2*dx[dir];
            	int ny=cur.y+2*dy[dir];
	            for(int k=0;k<2;k++){
	                int nnx=nx+dx[(dir+lookup[k]+4)%4];
	                int nny=ny+dy[(dir+lookup[k]+4)%4];
	                if(!isInside(nnx,nny)||map[nny][nnx]) continue;
	                if((cMap[nny][nnx])<=cur.cnt+1&&kMap[nny][nnx]<=cur.kCnt+1) continue;
                    cMap[nny][nnx]=cur.cnt+1;
                    kMap[nny][nnx]=cur.kCnt+1;
	                pq.push({nnx,nny,cur.cnt+1,cur.kCnt+1});
	            }
        	}
        }
    }
    cout<<res<<endl;
}

///////////////////////////////////////////////////////////

#include <iostream>
#include <queue>
#include <string.h>
#define MAX 200
#define INF 40001
using namespace std;

struct info{
    int x,y,cnt,kCnt;
    bool operator<(const info& b)const{
        if(cnt!=b.cnt) return cnt>b.cnt;
        return kCnt>b.kCnt;
    }
};
priority_queue<info> pq;
bool map[MAX+1][MAX+1];
int cMap[MAX+1][MAX+1];
int kMap[MAX+1][MAX+1];

const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
const int lookup[]={-1,1};
int W,H,K;

bool isInside(int x,int y){
    return x>=0&&x<W&&y>=0&&y<H;
}
int main(){
    cin>>K>>W>>H;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            scanf("%d",&map[i][j]);
            cMap[i][j]=kMap[i][j]=INF;
        }
    }
    
    pq.push({0,0,0,0});
    cMap[0][0]=0;
    kMap[0][0]=0;
    int res=-1;
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        if(cur.x==W-1&&cur.y==H-1) {
            res=cur.cnt;
            break;
        }
        for(int dir=0;dir<4;dir++){
            int nx=cur.x+dx[dir];
            int ny=cur.y+dy[dir];
            if(!isInside(nx,ny)||map[ny][nx]) continue;
            if(cMap[ny][nx]<=cur.cnt+1&&kMap[ny][nx]<=cur.kCnt) continue;
            cMap[ny][nx]=cur.cnt+1;
            kMap[ny][nx]=cur.kCnt;
            pq.push({nx,ny,cur.cnt+1,cur.kCnt});
        }
        if(cur.kCnt<K){
        	for(int dir=0;dir<4;dir++){
        		int nx=cur.x+2*dx[dir];
            	int ny=cur.y+2*dy[dir];
	            for(int k=0;k<2;k++){
	                int nnx=nx+dx[(dir+lookup[k]+4)%4];
	                int nny=ny+dy[(dir+lookup[k]+4)%4];
	                if(!isInside(nnx,nny)||map[nny][nnx]) continue;
	                if((cMap[nny][nnx])<=cur.cnt+1&&kMap[nny][nnx]<=cur.kCnt+1) continue;
                    cMap[nny][nnx]=cur.cnt+1;
                    kMap[nny][nnx]=cur.kCnt+1;
	                pq.push({nnx,nny,cur.cnt+1,cur.kCnt+1});
	            }
        	}
        }
    }
    cout<<res<<endl;
}