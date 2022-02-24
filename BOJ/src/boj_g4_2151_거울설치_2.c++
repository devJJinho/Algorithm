#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define MAX 50
#define INF 9999999

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.23

*난이도 : G4
*개인 풀이 시간 : 1hr
*개인 난이도 : 2/5 
*분류 : BFS, 백트래킹
*풀이 : 한 좌표의 각 방향에서 최소 거울 값이 들어올때 queue에 넣음.
       1. 처음 풀이는 stack의 자료구조에 현재까지 사용한 거울 수도 같이 넣었으나, 
       queue에 넣을 때 visited 역할을 하는 check도 같이 업데이트 하기 때문에 다음 좌표(nx,ny)만 넣는거도 괜찮음. 
       queue에 넣은 nx,ny가 아직 pop은 되어 그 주변으로 탐색은 하지 못했지만, queue에 들어가는 시점에 check[ny][nx]는 업데이트 됐고 그 보다 작은 값을 가진 경로나 나오지 않는 이상 중복되게 queue에 들어가는 일은 없음
       또 BFS이기 때문에 cnt(이 문제에선 거울의 개수)가 하나씩 들어나는 순으로 진행되며 현재 내가 nx,ny의 최소값을 갱신하며 들어간다면 나보다 거울을 적게 쓰고 이 점에 도달한 경우가 없다는 뜻.

*느낀점 : 단순 BFS에서 조건을 추가한 경우에 대해 고민하다가 이전에 풀이한 문제를 다시 풀었음.
        문제에서 거울의 수 하나만 물었기 때문에 거기에 대한 배열만 유지하며 진행함.
*/


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define MAX 50
#define INF 9999999

using namespace std;

struct info{
    int x,y,dir;
};

// 1,3 : 동서
// 2,4 : 남북
//동남서북

// 허수, 동, 남, 서, 북
const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};

vector<pair<int,int>> door;
queue<info> mirQ;

char map[MAX+2][MAX+2];
int check[MAX+2][MAX+2][5];
int main(){
    int size;
    cin>>size;
    for(int i=0;i<size;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<size;j++){
            map[i][j]=temp[j];
            if(map[i][j]=='#')
                door.push_back(make_pair(j,i));
            check[i][j][1]=check[i][j][2]=check[i][j][3]=check[i][j][4]=INF;
        }
    }
    
    int startX=door[0].first;
    int startY=door[0].second;
    map[startY][startX]='*';

    for(int dir=1;dir<=4;dir++){
        mirQ.push({startX,startY,dir});
        check[startY][startX][dir]=0;
    }
    bool isFind=false;
    while(!mirQ.empty()&&!isFind){    
        info cur=mirQ.front();
        mirQ.pop();
        int curDir=cur.dir;
        int x=cur.x;
        int y=cur.y;
        int postX=x;
        int postY=y;
        int curCnt=check[y][x][curDir];
        while(postX>=0&&postY>=0&&postX<size&&postY<size){
            postX+=dx[curDir];
            postY+=dy[curDir];
            if(!(postX>=00&&postY>=0&&postX<size&&postY<size)) break;
            //나보다 더 적은 거울수로 내가 가는 방향에 방문한 적이 있다면 진행 필요 X
            //이 조건은 기본적으로 curDir 방향으로 직진하는 경우에 해당 아래에서 거울 설치 후 수직 방향으로 꺾어 이동할때의 if문은 꺾인 방향으로 체크
            if(check[postY][postX][curDir]<=curCnt) break;
            if(check[postY][postX][curDir]>curCnt) check[postY][postX][curDir]=curCnt;
            char temp=map[postY][postX];
            if(temp=='#'){
                isFind=true;
                break;
            }
            if(temp=='*') break;
            else if(temp=='!'){
                if(curDir%2==0){
                    if(check[postY][postX][1]>curCnt+1){
                        mirQ.push({postX,postY,1});
                        check[postY][postX][1]=curCnt+1;
                    }
                    if(check[postY][postX][3]>curCnt+1){
                        mirQ.push({postX,postY,3});
                        check[postY][postX][3]=curCnt+1;
                    }
                }
                else{
                      if(check[postY][postX][2]>curCnt+1){
                        mirQ.push({postX,postY,2});
                        check[postY][postX][2]=curCnt+1;
                    }
                    if(check[postY][postX][4]>curCnt+1){
                        mirQ.push({postX,postY,4});
                        check[postY][postX][4]=curCnt+1;
                    }
                }
            }
        }
    }
    int y=door[1].second;
    int x=door[1].first;
    int minValue=check[y][x][1];
    for(int i=2;i<=4;i++)
        if(minValue>check[y][x][i]) minValue=check[y][x][i];
    cout<<minValue<<endl;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

struct info{
    int x,y,dir,cnt;

};
// 1,3 : 동서
// 2,4 : 남북
// 동남서북

// 허수, 동, 남, 서, 북
const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};

vector<pair<int,int>> door;
queue<info> mirQ;

char map[MAX+2][MAX+2];
int check[MAX+2][MAX+2][5];
int main(){
    int size;
    cin>>size;
    for(int i=0;i<size;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<size;j++){
            map[i][j]=temp[j];
            if(map[i][j]=='#')
                door.push_back(make_pair(j,i));
            check[i][j][1]=check[i][j][2]=check[i][j][3]=check[i][j][4]=INF;
        }
    }
    
    int startX=door[0].first;
    int startY=door[0].second;
    map[startY][startX]='*';

    for(int dir=1;dir<=4;dir++){
        mirQ.push({startX,startY,dir,0});
        check[startY][startX][dir]=0;
    }
    bool isFind=false;
    while(!mirQ.empty()&&!isFind){    
        info cur=mirQ.front();
        mirQ.pop();
        int curDir=cur.dir;
        int postX=cur.x;
        int postY=cur.y;
        while(postX>=0&&postY>=0&&postX<size&&postY<size){
            postX+=dx[curDir];
            postY+=dy[curDir];
            if(!(postX>=00&&postY>=0&&postX<size&&postY<size)) break;
            if(check[postY][postX][curDir]<=cur.cnt) break;
            if(check[postY][postX][curDir]>cur.cnt) check[postY][postX][curDir]=cur.cnt;
            char temp=map[postY][postX];
            if(temp=='#'){
                isFind=true;
                break;
            }
            if(temp=='*') break;
            else if(temp=='!'){
                if(curDir%2==0){
                    if(check[postY][postX][1]>cur.cnt+1){
                        mirQ.push({postX,postY,1,cur.cnt+1});
                        //bfs를 위해 queue에 넣으면서 바로 visited(역할)에 기록
                        //이보다 더 많은 거울 수를 가진 경우의 수는 더이상 반영되지 않음
                        //각 점에 대해 최소 거울 수를 구하면 그게 전체 답이 됨
                        check[postY][postX][1]=cur.cnt+1;
                    }
                    if(check[postY][postX][3]>cur.cnt+1){
                        mirQ.push({postX,postY,3,cur.cnt+1});
                        check[postY][postX][3]=cur.cnt+1;
                    }
                }
                else{
                      if(check[postY][postX][2]>cur.cnt+1){
                        mirQ.push({postX,postY,2,cur.cnt+1});
                        check[postY][postX][2]=cur.cnt+1;
                    }
                    if(check[postY][postX][4]>cur.cnt+1){
                        mirQ.push({postX,postY,4,cur.cnt+1});
                        check[postY][postX][4]=cur.cnt+1;
                    }
                }
            }
        }
    }
    int y=door[1].second;
    int x=door[1].first;
    int minValue=check[y][x][1];
    for(int i=2;i<=4;i++)
        if(minValue>check[y][x][i]) minValue=check[y][x][i];
    cout<<minValue<<endl;
    return 0;
}