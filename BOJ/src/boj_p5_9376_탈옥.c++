#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#define INF 9999999
#define MAX 105
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.15

*난이도 : p5
*개인 풀이 시간 : 3hour 
*개인 난이도 : 3/5 
*분류 : 0-1 다익스트라(deque 사용), 구현
*풀이 : 
        감옥의 외부에 임의로 '.'을 추가했다. 여기선 모두가 가중치 없이 움직일 수 있다. 이것을 사용해서 둘이 각각 빠져나오는 경우에 대해서도 체크할 수 있었다.
        다익스트라의 풀이를 queue와 deque 자료구조로 풀이했다. (deque가 훨씬 효율적)
        두 경우 모두 방문 여부를 기록하는 bool isVisited를 사용할 필요가 없었다.

*느낀점 : 2명에 대해서 물었지만 3명에 대해서 풀이한 것은 굉장히 놀라운 생각이었다. 
        테스크케이스가 많은 경우 값이 중복되지 않게 잘 정리해야된다. 이 문제의 경우 map의 중복으로 디버깅에 2시간을 허비했다.    
        
*/

// deque를 사용한 풀이 //

struct info{
    int x,y,cnt;
};
pair<int,bool> p1[105][105], p2[105][105], helper[105][105];
char map[105][105];
int row,col;
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

bool isValid(int x,int y){
    return x>=0&&x<=col+1&&y>=0&&y<=row+1;
}

//방문했는지 안했는지 체크 할 필요가 없음
//한번만 방문하기 때문에 visited의 값이 INF인지 아닌지만 체크하면 됨 
void BFS(pair<int,int> point, pair<int,bool> visited[][MAX]){
    deque<info> stack;
    stack.push_front({point.first,point.second,0});
    while(!stack.empty()){
        info cur=stack.front();
        stack.pop_front();
        int x=cur.x;
        int y=cur.y;
        int cnt=cur.cnt;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(isValid(nx,ny)){
                if(map[ny][nx]=='*') continue;
                if(map[ny][nx]=='#'){
                    if(!visited[ny][nx].second){
                        visited[ny][nx].first=cnt+1;
                        //문을 하나 동과해야되는 경우 deque의 뒤에 넣는다. 한 레벨 높은 경우기 때문
                        stack.push_back({nx,ny,cnt+1});
                        visited[ny][nx].second=true;
                    }
                    continue;
                }
                if(!visited[ny][nx].second){
                    visited[ny][nx].first=cnt;
                    //문을 열지 않고 움직일 수 있는 경우 deque의 앞에 삽입한다. 같은 레벨이기 때문
                    stack.push_front({nx,ny,cnt});
                    visited[ny][nx].second=true;
                }
            }
        }
    }
}

void memset(pair<int,bool> a[][MAX]){
    for(int i=0;i<=row+2;i++){
        for(int j=0;j<=col+2;j++){
            a[i][j].first=INF;
            a[i][j].second=false;
        }
    }
}

int findPath(vector<pair<int,int>> prisoner){
    BFS({0,0},helper);
    BFS(prisoner[0],p1);
    BFS(prisoner[1],p2);
    int minSum1=INF;
    //3명이 만나는 경우
    //여기서 중요한 점은 감옥 안에서 만나기도 하지만, 감옥의 주위가 가중치 없이 움직일 수 있는 곳이기 때문에 만약 죄수 각각이 만나지 앞고 감옥 밖으로 나오는 경우가 최소인 경우도 체크할 수 있다.
    //감옥의 4방이 모두 가중치 0이기 때문!
    for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p1[i][j].first+p2[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=2;
            minSum1=min(minSum1,sum);
        }
    }
    int p1Top2=p1[prisoner[1].second][prisoner[1].first].first;
    int minSum2=INF;
     for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p2[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=1;
            minSum2=min(minSum2,sum);
        }
    }
    
    int p2Top1=p2[prisoner[0].second][prisoner[0].first].first;
    int minSum3=INF;
     for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p1[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=1;
            minSum3=min(minSum3,sum);
        }
    }
    //마지막의 Minsum2+minSum3는 할 필요가 없다. 이것은 항상 최소값 보다 같거나 크다. 첫번째 조건으로 각각 빠져나오는 경우를 체크할 수 있다.
    return min({minSum1,minSum2+p1Top2,minSum3+p2Top1,minSum2+minSum3});
}

int main(){
    int n;
    cin>>n;
    while(n--){
        cin>>row>>col;
        memset(p1);
        memset(p2);
        memset(helper);
        for(int i=0;i<=row+1;i++){
            for(int j=0;j<=col+1;j++)
                map[i][j]='.';
        }
        vector<pair<int,int>> prisoner;
        for(int i=1;i<=row;i++){
            for(int j=1;j<=col;j++){
                cin>>map[i][j];
                if(map[i][j]=='$') prisoner.push_back({j,i});
            }
        }
        cout<<findPath(prisoner)<<endl;
    }
    return 0;
}


// queue를 사용해서 풀이하는 경우 //

//bool visited배열을 유지할 필요가 없다. int visited의 값을 INF로 잡고 
//값을 줄일 수 있을때만 줄이고 queue에 넣으면 된다.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 9999999
#define MAX 105
using namespace std;

struct info{
    int x,y,cnt;
};
pair<int,bool> p1[105][105], p2[105][105], helper[105][105];
char map[105][105];
int row,col;
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

bool isValid(int x,int y){
    return x>=0&&x<=col+1&&y>=0&&y<=row+1;
}

void DFS(pair<int,int> point, pair<int,bool> visited[][MAX]){
    queue<info> stack;
    stack.push({point.first,point.second,0});
    while(!stack.empty()){
        info cur=stack.front();
        stack.pop();
        int x=cur.x;
        int y=cur.y;
        int cnt=cur.cnt;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(isValid(nx,ny)){
                if(map[ny][nx]=='*') continue;
                if(map[ny][nx]=='#'){
                    //두 경우 모두 비교할 필요가 없다. 뒷 조건만 있으면 된다.
                    if(!visited[ny][nx].second||visited[ny][nx].first>cnt+1){
                        visited[ny][nx].first=cnt+1;
                        stack.push({nx,ny,cnt+1});
                        visited[ny][nx].second=true;
                    }
                    continue;
                }
                if(!visited[ny][nx].second||visited[ny][nx].first>cnt){
                    visited[ny][nx].first=cnt;
                    stack.push({nx,ny,cnt});
                    visited[ny][nx].second=true;
                }
            }
        }
    }
}

void memset(pair<int,bool> a[][MAX]){
    for(int i=0;i<=row+2;i++){
        for(int j=0;j<=col+2;j++){
            a[i][j].first=INF;
            a[i][j].second=false;
        }
    }
}

int findPath(vector<pair<int,int>> prisoner){
    DFS({0,0},helper);
    DFS(prisoner[0],p1);
    DFS(prisoner[1],p2);
    int minSum1=INF;
    for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p1[i][j].first+p2[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=2;
            minSum1=min(minSum1,sum);
        }
    }
    int p1Top2=p1[prisoner[1].second][prisoner[1].first].first;
    int minSum2=INF;
     for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p2[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=1;
            minSum2=min(minSum2,sum);
        }
    }
    
    int p2Top1=p2[prisoner[0].second][prisoner[0].first].first;
    int minSum3=INF;
     for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            int sum=p1[i][j].first+helper[i][j].first;
            if(map[i][j]=='#') sum-=1;
            minSum3=min(minSum3,sum);
        }
    }
    return min({minSum1,minSum2+p1Top2,minSum3+p2Top1,minSum2+minSum3});
}

int main(){
    int n;
    cin>>n;
    while(n--){
        cin>>row>>col;
        memset(p1);
        memset(p2);
        memset(helper);
         for(int i=0;i<=row+1;i++){
            for(int j=0;j<=col+1;j++)
                map[i][j]='.';
        }
        vector<pair<int,int>> prisoner;
        for(int i=1;i<=row;i++){
            for(int j=1;j<=col;j++){
                cin>>map[i][j];
                if(map[i][j]=='$') prisoner.push_back({j,i});
            }
        }
        cout<<findPath(prisoner)<<endl;
    }
    return 0;
}