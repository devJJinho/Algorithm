#include <iostream>
#include <string>
#include <string.h>
#define MAX 1000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.10

*난이도 : G2
*개인 풀이 시간 : 30min 
*개인 난이도 : 2/5 
*분류 : Union-find, Dfs, 재귀
*풀이 : 주석 참조. 

*느낀점 : 사이클에 대한 이해가 더 필요함, 꼭 환 구조를 이뤄야 할 필요는 없음.
        
*/

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
//방문 여부
bool isVisited[MAX][MAX];
//현재 탐색 경로에서 사이클 체크를 위한 배열
//isVisited와 구분하는 이유는 내가 이미 만들어진 경로에 흡수되는지 아니면 dfs 중인 경로에서 사이클이 형성 됐는지 체크를 위해서
//재귀가 아닌 stack을 활용한 Dfs에서 구현이 까다로움
bool hasCycle[MAX][MAX];
char map[MAX][MAX];
int N,M;

int getDir(char dir){
    switch(dir){
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        default : return 3;
    }
}
int recul(int x,int y){
    //x,y에 대해 isVisited와 hasCycle 체크가 동시에 이루어지기 때문에 hasCycle부터 물어봐야함
    if(hasCycle[y][x]) return 1;
    if(isVisited[y][x]) return 0;
    isVisited[y][x]=hasCycle[y][x]=true;
    int dir=getDir(map[y][x]);
    int nx=x+dx[dir];
    int ny=y+dy[dir];
    int res=recul(nx,ny);
    //원상복구
    hasCycle[y][x]=false;
    return res;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for(int i=0;i<N;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<M;j++)
            map[i][j]=temp[j];
    }
    int cnt=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cnt+=recul(j,i);
        }
    }
    cout<<cnt<<endl;
}


///////////////////////////////////////////////////
//dfs를 위한 1000*1000 배열 선언과 초기화의 overhead가 큼
//제한시간 1초 기준 시간초과

#include <iostream>
#include <string>
#include <stack>
#include <string.h>
#define MAX 1000
using namespace std;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
bool isVisited[MAX][MAX];
char map[MAX][MAX];
int N,M;

int getDir(char dir){
    switch(dir){
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        default : return 3;
    }
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<M;j++)
            map[i][j]=temp[j];
    }
    int cnt=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isVisited[i][j])continue;
            //시간초과 발생
            bool visited[N][M];
            memset(visited,0,sizeof(visited));
            stack<pair<int,int>> que;
            que.push({j,i});
            while(!que.empty()){
                auto cur=que.top();
                que.pop();
                isVisited[cur.second][cur.first]=visited[cur.second][cur.first]=true;
                int dir=getDir(map[cur.second][cur.first]);
                int nx=cur.first+dx[dir];
                int ny=cur.second+dy[dir];
                if(visited[ny][nx]) {
                    ++cnt;
                    break;
                }
                if(isVisited[ny][nx]) break;
                que.push({nx,ny});
            }
          
        }
    }
    cout<<cnt<<endl;
}


///////////////////////////////////////////////
//아래 코드는 dfs 코드, 작동 안됨

#include <iostream>
#include <string>
#include <stack>
#define MAX 1000
using namespace std;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
bool isVisited[MAX][MAX];
char map[MAX][MAX];
int N,M;

bool isInside(int x, int y){
    return x>=0&&x<M&&y>=0&&y<N;
}

int getDir(char dir){
    switch(dir){
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        default : return 3;
    }
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<M;j++)
            map[i][j]=temp[j];
    }
    int cnt=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isVisited[i][j])continue;
            //dfs한다고 바로 그룹이 생기는건 아님//
            //본인 경로와 만났을때 그때 경로가 생기는 것
            ++cnt; //잘못됨
            stack<pair<int,int>> que;
            que.push({j,i});
            while(!que.empty()){
                auto cur=que.top();
                que.pop();
                isVisited[cur.second][cur.first]=true;
                int dir=getDir(map[cur.second][cur.first]);
                int nx=cur.first+dx[dir];
                int ny=cur.second+dy[dir];
                if(!isInside(nx,ny)||isVisited[ny][nx]) continue;
                que.push({nx,ny});
            }
          
        }
    }
    cout<<cnt<<endl;
}

/////////////////////////////////////////////


#include <iostream>
#include <string>
#include <queue>
#define MAX 1000
using namespace std;

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

int parent[MAX*MAX+1];
char map[MAX][MAX];
int N,M;

bool isInside(int x, int y){
    return x>=0&&x<M&&y>=0&&y<N;
}

int getDir(char dir){
    switch(dir){
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        default : return 3;
    }
}

int findParent(int n){
    if(parent[n]==n) return n;
    return parent[n]=findParent(parent[n]);
}

bool unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a==b) return false;
    if(a>b) parent[a]=b;
    else parent[b]=a;
    return true;
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<M;j++)
            map[i][j]=temp[j];
    }
   
    for(int i=0;i<N*M;i++)
        parent[i]=i;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int index=i*M+j;
            if(parent[index]!=index) continue;
            queue<pair<int,int>> que;
            que.push({j,i});
            while(!que.empty()){
                auto cur=que.front();
                que.pop();
                int dir=getDir(map[cur.second][cur.first]);
                int nx=cur.first+dx[dir];
                int ny=cur.second+dy[dir];
                if(!isInside(nx,ny)) continue;
                bool res=unionParent(index,ny*M+nx);
                if(res) que.push({nx,ny});
            }
          
        }
    }
    int cnt=0;
    for(int i=0;i<M*N;i++)
        if(parent[i]==i) ++cnt;
    cout<<cnt<<endl;
}