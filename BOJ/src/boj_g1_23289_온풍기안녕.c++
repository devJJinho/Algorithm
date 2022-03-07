#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))
#define ABS(a) ((a)<0?-(a):(a))
#define MAX 20
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.07

*난이도 : G1
*개인 풀이 시간 : 1+40/60 hour
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬레이션, bfs, 삼성
*풀이 : 벽 처리가 관건이었음.
       
*느낀점 : 
       문제 조건 중에서 귀퉁이에 1이상 인 것은 -1한다를 읽지 못해 디버깅에 시간을 쏟음.
       
*/

//동서북남
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,-1,1};
const int vertiLookup[2][2]={
    {3,4},
    {1,2}
};
struct info{
    int x,y,dir;
};

struct warmth{
    int x,y,depth;
};
vector<info> heaters;
vector<pair<int,int>> checkPoint;
//0은 오른쪽
//1은 위쪽
bool wall[2][MAX+1][MAX+1];
int map[MAX+1][MAX+1];
int tempMap[MAX+1][MAX+1];
int R,C,K;
int tempStamp[MAX+1][MAX+1];
bool isStempDefined;

bool canGo(int x,int y, int dir){
    bool isX=!(dir/3);
    int nx=x+dx[dir];
    int ny=y+dy[dir];
    if(!(nx>=0&&nx<C&&ny>=0&&ny<R)) return false;
    //횡방향 비교면 wall배열에서 횡방향을 봄
    if(isX){
        //벽의 조건대로 더 큰쪽으로 내 위치에서 조회
        //작은쪽이라면 작은쪽에서 조회함
        if(nx>x) return !wall[1][y][x];
        else return !wall[1][ny][nx];
    }
    else{
        if(ny<y) return !wall[0][y][x];
        else return !wall[0][ny][nx];
    }
}

void spreadHeat(){
    if(!isStempDefined){
        for(auto heater:heaters){
            queue<warmth> que;
            bool isVisited[R][C];
            memset(isVisited,0,sizeof(isVisited));
            int startX=heater.x+dx[heater.dir];
            int startY=heater.y+dy[heater.dir];
            que.push({startX,startY,5});
            while(!que.empty()){
                auto cur=que.front();
                que.pop();
                tempStamp[cur.y][cur.x]+=cur.depth;
                //열기가 1이면 더 이상 확산되지 않음
                if(cur.depth==1) continue;
                vector<warmth> lookupList;
                //지금으로부터 수직 방향으로 1씩 움직일 수 있는지 체크
                lookupList.push_back(cur);
                for(int verti=0;verti<2;verti++){
                    int vDir=vertiLookup[heater.dir/3][verti];
                    if(canGo(cur.x,cur.y,vDir)){
                        lookupList.push_back({cur.x+dx[vDir],cur.y+dy[vDir],cur.depth});
                    }
                }
                //최대 3개(현재, 위, 아래)에 대해서 히터의 방향으로 1씩 움직일 수 있는지 체크
                for(auto next:lookupList){
                    int nx=next.x+dx[heater.dir];
                    int ny=next.y+dy[heater.dir];
                    if(canGo(next.x,next.y,heater.dir)&&!isVisited[ny][nx]){
                        //갈 수 있으면 queue에 넣기
                        que.push({nx,ny,cur.depth-1});
                        isVisited[ny][nx]=true;
                    }
                }
            }
        }
        isStempDefined=true;
    }
    //한번 만들어진 이후에는 그것을 반복해서 사용
    if(isStempDefined){
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                tempMap[i][j]+=tempStamp[i][j];
            }
        }
    }
}

void caliTemp(){
    int caliMap[R][C];
    memset(caliMap,0,sizeof(caliMap));
    int temp;
    //횡방향 비교
    for(int i=0;i<R;i++){
        for(int j=1;j<C;j++){
            if(wall[1][i][j-1]) continue;
            int highT=j;
            int lowT=j-1;
            if(tempMap[i][lowT]==tempMap[i][highT]) continue;
            if(tempMap[i][lowT]>tempMap[i][highT]) SWAP(highT,lowT,temp);
            int value=ABS(tempMap[i][highT]-tempMap[i][lowT])/4;
            caliMap[i][highT]-=value;
            caliMap[i][lowT]+=value;
        }
    }
    //종방향 비교
    for(int i=R-1;i>0;i--){
        for(int j=0;j<C;j++){
            if(wall[0][i][j]) continue;
            int highT=i;
            int lowT=i-1;
            if(tempMap[highT][j]==tempMap[lowT][j]) continue;
            if(tempMap[lowT][j]>tempMap[highT][j]) SWAP(highT,lowT,temp);
            int value=ABS(tempMap[highT][j]-tempMap[lowT][j])/4;
            caliMap[highT][j]-=value;
            caliMap[lowT][j]+=value;
        }
    }
    //동시에 온도가 퍼짐
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            tempMap[i][j]+=caliMap[i][j];
        }
    }
    
    //귀퉁이에서 1이상이면 -1하기
    for(int i=0;i<R;i++){
        int gap=(i==0||i==R-1)?1:C-1;
        for(int j=0;j<C;j+=gap){
            if(tempMap[i][j]>=1) --tempMap[i][j];
        }
    }
}

bool checkRoom(){
    for(auto point:checkPoint){
        if(tempMap[point.second][point.first]<K) return false;
    }
    return true;
}

int main(){
    cin>>R>>C>>K;
    int wallNum;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            scanf("%d",&map[i][j]);
            if(map[i][j]>=1&&map[i][j]<=4)
                heaters.push_back({j,i,map[i][j]});
            if(map[i][j]==5)
                checkPoint.push_back({j,i});
        }
    }
    cin>>wallNum;
    while(wallNum--){
        int y,x,type;
        cin>>y>>x>>type;
        wall[type][y-1][x-1]=true;
    }
    int cnt=0;
    while(true){
        if(++cnt==101) break;
        spreadHeat();
        caliTemp();
        if(checkRoom()) break;
    }
    cout<<cnt<<endl;
}