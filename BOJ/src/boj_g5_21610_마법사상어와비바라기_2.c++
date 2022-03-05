#include <iostream>
#include <vector>
#include <queue>
#define MAX 50
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2021.08.25

*난이도 : G5
*개인 풀이 시간 : 1.5
*개인 난이도 : 2/5 
*분류 : 구현, 자료구조 사용 (Set)
*풀이 : 
*느낀점 : 
        
*/

struct info{
    int x,y;
};

int map[MAX+1][MAX+1];
int N,M;
vector<pair<int,int>> instruc;
queue<info> clouds;
const int dx[]={0,-1,-1,0,1,1,1,0,-1};
const int dy[]={0,0,-1,-1,-1,0,1,1,1};

//대각선에 물이 들어있는 양동이가 있는지 체크
int calDiagValue(int x,int y){
    int diagonal[4]={2,4,6,8};
    int cnt=0;
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[diagonal[dir]];
        int ny=y+dy[diagonal[dir]];
        if(nx>=0&&nx<N&&ny>=0&&ny<N){
            if(map[ny][nx]) cnt++;
        }
    }
    return cnt;
}

void moveClouds(int dir,int cnt){
    bool hasClouds[MAX+1][MAX+1];
    vector<info> movedClouds;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            hasClouds[i][j]=false;
    //또는 Memset(hasClouds,0,sizeof(hasClouds))
    while(!clouds.empty()){
        info curPoint=clouds.front();
        clouds.pop();
        int nx=curPoint.x;
        int ny=curPoint.y;
        for(int t=0;t<cnt;t++){
            nx=(nx+dx[dir])%N;
            if(nx<0)nx+=N;
            ny=(ny+dy[dir])%N;
            if(ny<0)ny+=N;
        }
        //물복사(대각선 방향에 있는 물통만큼 증가)를 위해 비 온 곳 벡터에 담기
        movedClouds.push_back({nx,ny});
        hasClouds[ny][nx]=true;
        map[ny][nx]+=1;
    }
    //물복사 마법 시전
    for(info cl:movedClouds){
        int x=cl.x;
        int y=cl.y;
        int res=calDiagValue(x,y);
        map[y][x]+=res;
    }
    //새로 생긴 구름 담기
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(hasClouds[i][j]) continue;
            if(map[i][j]>=2){
                clouds.push({j,i});
                map[i][j]-=2;
            }
        }
    }
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            cin>>map[i][j];
    }
    int dir,cnt;
    for(int i=0;i<M;i++){
        cin>>dir>>cnt;
        instruc.push_back({dir,cnt});
    }
    clouds.push({0,N-2});
    clouds.push({1,N-2});
    clouds.push({0,N-1});
    clouds.push({1,N-1});
    
    for(auto inst:instruc){
        moveClouds(inst.first,inst.second);
    }
    
    int sum=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            sum+=map[i][j];
        }
    }
    cout<<sum<<endl;
}