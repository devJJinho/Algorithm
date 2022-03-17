#include <iostream>
#include <string.h>
#include <queue>
#define MAX 64
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.17

*난이도 : G4
*개인 풀이 시간 : 50/60 hour 
*개인 난이도 : 2/5 
*분류 : 시뮬, 구현, 삼성문제
*풀이 : 주석 참조

*느낀점 :

*/

int map[MAX][MAX];
int N,Q;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

void rotate(int a){
    int tempMap[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            tempMap[i][j]=map[i][j];
    }
    int range=1<<a;
    for(int i=0;i<N/(1<<a);i++){
        for(int j=0;j<N/(1<<a);j++){
            int x=j*1<<a;
            int y=i*1<<a;
            for(int t=0;t<range;t++){
                for(int k=0;k<range;k++){
                    map[y+t][x+k]=tempMap[y+range-1-k][x+t];
                }
            }
        }
    }
}
bool isInside(int x, int y){
    return x>=0&&x<N&&y>=0&&y<N;
}
void cali(){
    int tempMap[N][N];
    memset(tempMap,0,sizeof(tempMap));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int cnt=0;
            for(int dir=0;dir<4;dir++){
                int nx=j+dx[dir];
                int ny=i+dy[dir];
                if(!isInside(nx,ny)) continue;
                if(map[ny][nx]>0) ++cnt;
            }
            if(cnt<3) --tempMap[i][j];
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            map[i][j]+=tempMap[i][j];
    }
}

int getSum(){
    int sum=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            if(map[i][j]>0) sum+=map[i][j];
    }
    return sum;
}

int getChunk(){
    bool isVisited[N][N];
    int maxCnt=0;
    memset(isVisited,0,sizeof(isVisited));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(isVisited[i][j]) continue;
            if(map[i][j]<=0){
                isVisited[i][j]=true;
                continue;
            }
            queue<pair<int,int>> que;
            int cnt=0;
            que.push({j,i});
            isVisited[i][j]=true;
            while(!que.empty()){
                auto cur=que.front();
                que.pop();
                ++cnt;
                for(int dir=0;dir<4;dir++){
                    int nx=cur.first+dx[dir];
                    int ny=cur.second+dy[dir];
                    if(!isInside(nx,ny)||isVisited[ny][nx]||map[ny][nx]<=0) continue;
                    que.push({nx,ny});
                    isVisited[ny][nx]=true;
                }
            }
            maxCnt=max(maxCnt,cnt);
        }
    }
    return maxCnt;
}
int main(){
    cin>>N>>Q;
    N=1<<N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&map[i][j]);
        }
    }
    while(Q--){
        int a;
        scanf("%d",&a);
        rotate(a);
        cali();
    }
    cout<<getSum()<<endl;
    cout<<getChunk()<<endl;
}