#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define INF 9999999
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.17

*난이도 : G2
*개인 풀이 시간 : 2hour 
*개인 난이도 : 3/5 
*분류 : BFS, DP, 비트마스크
*풀이 : 원점(로봇이 있는 위치)와 먼지 위치 각각에서 BFS를 해서 경로값을 구한 뒤에 모든 순열에 대해서 조합해보면서 최소값을 찾았다. 순열 대입은 비트마스크를 이용했다. 
       그리고 dp를 사용해서 중복 계산을 막았다.
*느낀점 : 
       dp배열을 dp[1<<10][20][20] => 좌표의 최대값
       으로 지정한 사람도 있지만 나는 먼지마다 Index를 부여하고 인덱스만 넣는 dp로 만들어서 메모리를 절약했다.
        
*/


char map[22][22];
//원점과 각 먼지값의 경로값을 담는 배열
int cnt[22][22][11];
//먼지에 인덱스를 부여해서 메모리를 절약함
int dp[1<<11][10];
vector<pair<int,int>> dirt;
int w,h,k;
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

struct info{
    int x,y,cnt;
};
bool isValid(int x,int y){
    return x>=0&&x<w&&y>=0&&y<h;
}
void BFS(pair<int,int> point,int index){
    queue<info> que;
    que.push({point.first,point.second,0});
    cnt[point.second][point.first][index]=0;
    while(!que.empty()){
        info cur=que.front();
        que.pop();
        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if(isValid(nx,ny)){
                if(map[ny][nx]=='x') continue;
                //visited 배열 사용하지 않는다. 경로값을 줄일 수 있을때만 업데이트하고 push한다.
                if(cnt[ny][nx][index]>cur.cnt+1){
                    cnt[ny][nx][index]=cur.cnt+1;
                    que.push({nx,ny,cur.cnt+1});
                }
            }
        }
    }
}
//재귀와 dp에 depth 정보가 필요 없는 이유 : 
//depth와 상관 없이 현재 지점에서 아직 방문하지 않은 곳 stat이 있다면 값은 항상 같다.
int findPath(int stat,int cur){
    //마지막에 도달하면 끝이다. 경로값 추가할 것이 없기 때문에 0을 반환한다.
    //외판원 순회의 경우 마지막에서 원점으로 돌아와야 하기 때문에 여기서 원점까지의 거리를 반환한다.
    if(stat==(1<<k)-1) return 0;
    //dp에 저장된 값이 있으면 그것을 반환한다.
    if(dp[stat][cur]) return dp[stat][cur];
    int min=INF;
    for(int i=0;i<k;i++){
       int nextX=dirt[i].first;
       int nextY=dirt[i].second;
       //비트마스크를 통해 아직 방문하지 않은 정점을 찾고 각 정점바다 재귀를 보낸 다음 최소값을 얻는다.
       if(stat&(1<<i)||cnt[nextY][nextX][cur]==INF) continue;
       int res=cnt[nextY][nextX][cur];
       res+=findPath(stat|(1<<i),i);
       min=std::min(min,res);
   }
   //현재 지점에서 끝까지 보고 최소값을 얻었기 때문에 dp저장한다. 같은 cur값과 stat값에선 항상 최소값 Min을 가진다.
   dp[stat][cur]=min;
   //최소값을 반환한다.
   return dp[stat][cur];
}

int main(){
    while(true){
        pair<int,int> robot;
        cin>>w>>h;
        if(!w) break;
        dirt.clear();
        dirt.push_back({0,0});
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                for(int k=0;k<11;k++)
                    cnt[i][j][k]=INF;
                cin>>map[i][j];
                if(map[i][j]=='*') dirt.push_back({j,i});
                if(map[i][j]=='o') robot={j,i};
            }
        }
        k=(int)dirt.size();
        memset(dp,0,sizeof(dp));
        dirt[0]=robot;
        for(int i=0;i<k;i++)
            BFS(dirt[i],i);
        int res=findPath(1,0);
        //INF가 반환된다 : 가능한 길이 없다. => -1을 출력한다.
        cout<<(res>=INF?-1:res)<<endl;
    }
    return 0;
}