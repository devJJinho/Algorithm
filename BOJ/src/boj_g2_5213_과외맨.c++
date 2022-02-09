#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.09

*난이도 : G2
*개인 풀이 시간 : 3hour 
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬레이션, BFS, 그래프
*풀이 : 시뮬레이션 조건에 맞춰 구현함.
       index 조회는 함수보다 O(1)에 가능하게 map을 따로 둠 250000*8byte만큼 차지했음.
       indexMap 대신 함수 사용한 경우 메모리 절약 가능했음.
*느낀점 : 
      배열의 크기를 작게 잡아서 디버깅에 어려움을 겪음.
      처음엔 한 타일의 같은 블럭내 타일을 pop한 이후에 방문하는 방식으로 구현하였으나(이 과정에서 deque를 사용함), 한 블럭 내에서 두 타일은 같은 depth이기 때문에 두 개를 동시에 queue에 push 하는 방식으로 수정함
      deque 자체의 overhead가 사라짐에 따라 공간, 시간 복잡도 효율화 가능했음.
        
*/

#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#define MAX 500
using namespace std;

int map[MAX+1][2*MAX+1];
int isVisited[MAX*MAX-MAX/2+1];

const int rdx[]={0,0,1};
const int dy[]={-1,1,0};
const int ldx[]={0,0,-1};

queue<pair<int,int>> que;
stack<int> ans;

int n;

bool isInside(int i,int j){
    return i>=1&&i<=2*n&&j>=1&&j<=n;
}
int findIndex(int i,int j){
    int index=0;
    if(i%2){
        index+=(2*n-1)*(i/2);
        j++;
    }
    else{
        index+=n;
        index+=(2*n-1)*(i-2)/2;
    }
    index+=j/2;
    return index;
}
int bfs(){
    int maxIndex=0;
    que.push({1,1});
    que.push({2,1});
    isVisited[1]=-1;
    while(!que.empty()){
        auto cur=que.front();
        que.pop();
        int curX=cur.first;
        int curY=cur.second;
        int curIndex=findIndex(curY,curX);
        if(curIndex>maxIndex) maxIndex=curIndex;
        int correctX=curY%2==0? curX-2:curX-1;
        const int *dx=correctX%2?rdx:ldx;
        for(int dir=0;dir<3;dir++){
            int nx=curX+dx[dir];
            int ny=curY+dy[dir];
            if(!isInside(nx,ny)) continue;
            int nIndex=findIndex(ny,nx);
            if(isVisited[nIndex]||!map[ny][nx])continue;
            if(map[ny][nx]==map[curY][curX]){
                isVisited[nIndex]=curIndex;
                 if(nIndex==n*n-n/2) {
                    return nIndex;
                }
                int correctX=ny%2==0?nx-2:nx-1;
                int nextX=correctX%2?nx-1:nx+1;
                que.push({nx,ny});
                que.push({nextX,ny});
            }
        }
    }
    return maxIndex;
}

int findPath(int index){
    ans.push(index);
    int pre=isVisited[index];
    int cnt=1;
    while(pre!=-1){
        ans.push(pre);
        pre=isVisited[pre];
        cnt++;
    }
    return cnt;
}   

int main(){
    cin>>n;
    int a,b;
    int rowCnt=1;
    int colCnt=1;
    int colMax=2*n;
    for(int i=1;i<=n*n-n/2;i++){
        isVisited[i]=0;
        if(colCnt>colMax){
            if(++rowCnt%2==0){
                colCnt=2;
                colMax=2*n-1;
            }
            else{
                colCnt=1;
                colMax=2*n;
            }
        }
        scanf("%d %d",&a,&b);
        map[rowCnt][colCnt++]=a;
        map[rowCnt][colCnt++]=b;
    }
    int res=bfs();
    int cnt=findPath(res);
    cout<<cnt<<endl;
    while(!ans.empty()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
    cout<<endl;
}

/////////////////////////////////////////////////////////////////////////////

int map[MAX+1][2*MAX+1];
int indexMap[MAX+1][2*MAX+1];
//타일 index만큼 필요함
//직전 index 보관과 동시에 기방문 여부도 같이 저장
int isVisited[MAX*MAX-MAX/2+1];

int n;

const int rdx[]={0,0,1};
const int dy[]={-1,1,0};
const int ldx[]={0,0,-1};
queue<pair<int,int>> que;
stack<int> ans;
bool isInside(int i,int j){
    return i>=1&&i<=2*n&&j>=1&&j<=n;
}
int bfs(){
    int maxIndex=0;
    que.push({1,1});
    que.push({2,1});
    isVisited[1]=-1;
    while(!que.empty()){
        auto cur=que.front();
        que.pop();
        int curX=cur.first;
        int curY=cur.second;
        int curIndex=indexMap[curY][curX];
        if(curIndex>maxIndex) maxIndex=curIndex;
        //타일의 위치에 따라 블럭에서 조회할 장소가 다름
        int correctX=curY%2==0? curX-2:curX-1;
        const int *dx=correctX%2?rdx:ldx;
        for(int dir=0;dir<3;dir++){
            int nx=curX+dx[dir];
            int ny=curY+dy[dir];
            if(!isInside(nx,ny)) continue;
            int nIndex=indexMap[ny][nx];
            if(isVisited[nIndex]||!map[ny][nx])continue;
            if(map[ny][nx]==map[curY][curX]){
                isVisited[nIndex]=curIndex;
                 if(nIndex==n*n-n/2) {
                    //도달함과 동시에 바로 return, bfs이기 때문에 최소값 보장
                    return nIndex;
                }
                //nx,ny가 방문 가능하다면 그와 같은 블럭에 있는 타일까지 모두 queue에 삽입
                int correctX=ny%2==0?nx-2:nx-1;
                int nextX=correctX%2?nx-1:nx+1;
                que.push({nx,ny});
                que.push({nextX,ny});
            }
        }
    }
    return maxIndex;
}

int findPath(int index){
    ans.push(index);
    int pre=isVisited[index];
    int cnt=1;
    while(pre!=-1){
        ans.push(pre);
        pre=isVisited[pre];
        cnt++;
    }
    return cnt;
}   

int main(){
    cin>>n;
    int a,b;
    int rowCnt=1;
    int colCnt=1;
    int colMax=2*n;
    //모양 그대로 받기 위해 아래와 같이 입력받음
    for(int i=1;i<=n*n-n/2;i++){
        isVisited[i]=0;
        if(colCnt>colMax){
            if(++rowCnt%2==0){
                colCnt=2;
                colMax=2*n-1;
            }
            else{
                colCnt=1;
                colMax=2*n;
            }
        }
        scanf("%d %d",&a,&b);
        map[rowCnt][colCnt]=a;
        map[rowCnt][colCnt+1]=b;
        indexMap[rowCnt][colCnt]=i;
        indexMap[rowCnt][colCnt+1]=i;
        colCnt+=2;
    }
    int res=bfs();
    int cnt=findPath(res);
    cout<<cnt<<endl;
    while(!ans.empty()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
    cout<<endl;
}


//map[i][j]값으로 n번째 타일인지 알아내는 코드 필요
int findIndex(int i,int j){
    int index=0;
    if(i%2){
        index+=(2*n-1)*(i/2);
        j++;
    }
    else{
        index+=n;
        index+=(2*n-1)*(i-2)/2;
    }
    index+=j/2;
    return index;
}
