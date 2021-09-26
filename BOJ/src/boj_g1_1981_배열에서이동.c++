#include <iostream>
#include <queue>
#include <string.h>
#define INF 99999999
#define MAX 101
using namespace std;

/*
*난이도 : G1
*개인 풀이 시간 : 2hour
*개인 난이도 : 3/5 
*분류 : 브루트포스(but 이분 탐색을 통해 최적화시킴), 이분탐색, bfs
*풀이 : dp를 사용하기에는 [현재 x좌표][현재 y좌표][최소][최대] 값이 필요하다. 최대배열 크기는 [100][100][200][200]이다. => 불가능
       dp를 통한 브루트포스의 최적화가 불가능함에 따라 이분탐색으로 브루트포스의 연산량을 줄이는 방법을 택했다. 
       전체 맵의 최대,최소값을 찾은 뒤, 가능한 최대,최소의 차는 0~(최대-최소)임을 알아냈다. 그리고 이것을 low,high로 두고 이분 탐색을 했다.
       이분 탐색 중 mid값 만큼의 최대,최소 차를 가지고 (1,1)~(n,n)갈 수 있는지 체크하고 가능하면 차이를 줄이는 방법을 택했다.
       diff만큼을 테스트하기 위해 i=배열 최소값에서, 배열 최대값까지 돌며 경로상 모든 점이 i<=map[y][x]<=i+diff 인지 체크했다.

*느낀점 : 생각하지도 못한 접근 방식이다. dp사용이 힘들고 묻는게 비교적 간단한 경우 역으로 답의 범위를 줄이면서 이분 탐색 할 수 도 있음을 배웠다.
*/

int map[MAX][MAX];
int dp[MAX][MAX][400];
bool isVisited[MAX][MAX];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
int n,mi,ma;
bool isValid(int x,int y){
    return x>=1&&x<=n&&y>=1&&y<=n;
}
int cnt=0;

bool bfs(int threshold){
    //i는 최소값부터 최대값까지 진행된다. 최소값이 i이상, 최대값은 i+threshold값 이내의 값으로만 갔을 때 (n,n)으로 갈 수 있는지 체크한다. 
    for(int i=mi;i<=ma;i++){
        if(map[1][1]<i||map[1][1]>i+threshold) continue;
        memset(isVisited,false,sizeof(isVisited));
        queue<pair<int,int>> que;
        que.push({1,1});
        //갈 수 있으면 return true;
        isVisited[1][1]=true;
        while(!que.empty()){
            pair<int,int> cur=que.front();
            que.pop();
            if(cur.first==n&&cur.second==n) return true;
            for(int dir=0;dir<4;dir++){
                int nx=cur.first+dx[dir];
                int ny=cur.second+dy[dir];
                if(isValid(nx,ny)&&!isVisited[ny][nx]){
                    if(map[ny][nx]<i||map[ny][nx]>i+threshold) continue;
                    que.push({nx,ny});
                    isVisited[ny][nx]=true;
                    
                }
            }
        }
    }
    //threshold값만큼의 차이로 갈 수 없으면 return false;
    return false;
}

int biSearch(){
    //이분 탐색으로 탐색
    int low=0;
    int high=ma-mi;
    int mid;
    int res;
    //high==low일때 종료된다.
    while(high>=low){
        mid=(low+high)/2;
        //같은 경우에 res에 담는다.
        if(bfs(mid)){
            res=mid;
            high=mid-1;
        }
        else
            low=mid+1;
    }
    return res;
}

int main(){
    cin>>n;
    mi=INF;
    ma=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
            //최대 최소 찾기
            if(map[i][j]>ma) ma=map[i][j];
            if(map[i][j]<mi) mi=map[i][j];
        }
    }
    cout<<biSearch()<<endl;
    return 0;
}