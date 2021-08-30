#include <iostream> 
#include <vector>
#include <queue>
#define MAX 12
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.30

*난이도 : G2
*개인 풀이 시간 : 4hour 
*개인 난이도 : 3/5 
*분류 : 구현, 자료구조 사용 (vector)
*풀이 : 체스판의 색에 따라 처리하는 함수를 따로 만들었음. 
       말의 상태는 horses[말 번호]={{좌표}, 방향}을 유지하고, 현재 말의 상태는 stat[][]에 유지했다.
       각 turn 마다 horses[1~k]를 돌고, stat배열을 참고해 현재 말 보다 위에 있는 말을 구하고, 
       현재 말의 움직임을 위의 말과 stat 배열에 모두 반영했다. 즉 한 움직임 마다 horses, stat배열 모두 업데이트했다.
*느낀점 : 
        Gold2 문제는 규모다 크다보니 디버깅에서 많은 시간이 걸린다. 더 많은 경우의 수를 포괄하는 알고리즘이 필요하다. 
        그렇지 않으면 너무 많은 분기와, 조건식을 사용해야함.
        많이 풀어보면 더 효율적인 구조와 디버깅 시간을 단축할 수 있을거라 본다. 
*/

struct info{
    int x,y;
};
int map[MAX+1][MAX+1];
deque<int> stat[MAX+1][MAX+1];
vector<pair<info,int>> horses(11);
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,-1,1};
int n,k;

bool isValid(int x,int y){
    return x>=1&&x<=n&&y>=1&&y<=n;
}
void handleWhite(vector<int> &upper,int x,int y,int nx,int ny){
    //pop한 순서의 역순을 만들기 위해, reverse에 우선 담고 reverse를 순방향으로 돌면서 push
    vector<int> reverse;
    for(auto horse:upper){
        horses[horse].first.x=nx;
        horses[horse].first.y=ny;
        int temp=stat[y][x].back();
        stat[y][x].pop_back();
        reverse.push_back(temp);
    }
    while(!reverse.empty()){
        stat[ny][nx].push_back(reverse.back());
        reverse.pop_back();
    }
}
void handleRed(vector<int> &upper,int x,int y,int nx,int ny){
    //pop한 순서 그대로 push하면 역순 만듬
    for(auto horse:upper){
        horses[horse].first.x=nx;
        horses[horse].first.y=ny;
        int temp=stat[y][x].back();
        stat[y][x].pop_back();
        stat[ny][nx].push_back(temp);
    }
}
void handleBlue(vector<int> &upper,int x,int y,int dir){
    int ndir;
    switch(dir){
        case 1: ndir=2; break;
        case 2: ndir=1; break;
        case 3: ndir=4; break;
        case 4: ndir=3; break;
    }
    int nx=x+dx[ndir];
    int ny=y+dy[ndir];
    horses[upper[0]].second=ndir;
    if(isValid(nx,ny)&&map[ny][nx]!=2){
        if(map[ny][nx]==0)handleWhite(upper,x,y,nx,ny);
        else if(map[ny][nx]==1)handleRed(upper,x,y,nx,ny);
    }
}
//나보다 위에 있는 말을 upper에 담는다. (나를 포함함)
void findUpper(vector<int> &upper,int x,int y,int i){
    bool isFind=false;
    for(auto a:stat[y][x]){
        if(a==i)isFind=true;
        if(isFind) upper.push_back(a);
    }
}
int findClue(){
    int cnt=0;
    while(++cnt){
        if(cnt==1000) return -1;
        for(int i=1;i<=k;i++){
            int curX=(horses[i]).first.x;
            int curY=(horses[i]).first.y;
            int curDir=(horses[i]).second;
            vector<int> upper;
            findUpper(upper,curX,curY,i);
            int nx=curX+dx[curDir];
            int ny=curY+dy[curDir];
            if(!isValid(nx,ny)) handleBlue(upper,curX,curY,curDir);
            else if(map[ny][nx]==2) handleBlue(upper,curX,curY,curDir);
            else if(map[ny][nx]==0){
                handleWhite(upper,curX,curY,nx,ny);
            }
            else if(map[ny][nx]==1){
                handleRed(upper,curX,curY,nx,ny);
            }
            if(stat[horses[i].first.y][horses[i].first.x].size()>=4) return cnt;
        }
    }
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
        }
    }
    for(int i=1;i<=k;i++){
        int x,y,dir;
        cin>>y>>x>>dir;
        horses[i]={{x,y},dir};
        stat[y][x].push_back(i);
    }
    cout<<findClue()<<endl;
    return 0;
}
