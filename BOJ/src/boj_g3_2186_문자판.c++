#include <iostream>
#include <queue>
#include <string.h>
#define MAX 100 
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.25

*난이도 : G3
*개인 풀이 시간 : 1hr
*개인 난이도 : 2/5 
*분류 : DP, DFS, 재귀
*풀이 : 3차원 Dp를 썼다. 
       2차원 dp를 사용한거 때문에 디버깅에 오랜 시간이 걸렸다.
       같은 점이더라도 word의 index에 따라 다른 값을 가지고 있기 때문이다. => 결국은 배열값의 오염 때문에 생기는 일
*느낀점 : bfs인것은 생객했으나 dp를 사용할 생각은 못했다.

*/

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
char map[MAX+1][MAX+1];
int dp[MAX+1][MAX+1][80];
int n,m,k;
string ts;
struct info{
    int x,y,cnt;
};
bool isValid(int x,int y){
    return x>=0&&x<m&&y>=0&&y<n;
}

int BFS(int x,int y,int index){
    if(index==ts.length()) return 1;
    if(dp[y][x][index]!=-1) return dp[y][x][index];
    int ct=0;
    for(int i=0;i<4;i++){
        int nx=x;
        int ny=y;
        for(int j=1;j<=k;j++){
            nx+=dx[i];
            ny+=dy[i];
            if(!isValid(nx,ny)) break;
            if(ts[index]==map[ny][nx])
                ct+=BFS(nx,ny,index+1);
        } 
    }
    dp[y][x][index]=ct;
    return ct;
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
         cin>>map[i];
    }
    cin>>ts;
    int cnt=0;
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]==ts[0]){
                int res=BFS(j,i,1);
                cnt+=res;
                dp[i][j][0]=res;
            }
        }
    }
    cout<<cnt<<endl;
    return 0;
}