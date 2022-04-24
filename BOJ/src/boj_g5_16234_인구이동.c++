#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX 50
using namespace std;

int N, L, R;
int map[MAX][MAX];
const int dx[] = {0,0,-1,1};
const int dy[] = {-1,1,0,0};
bool visited[MAX][MAX];
vector<pair<int,int>> list;
int cnt , sum;

void dfs(int x, int y){
    visited[y][x] = true;
    list.push_back({x,y});
    cnt++;
    sum += map[y][x];
    for(int dir = 0 ; dir < 4; dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[ny][nx]){
            int gap = ABS(map[y][x] - map[ny][nx]);
            if(gap >= L && gap <= R){
                dfs(nx,ny);
            }
        }
    }
}
bool spread(){
    bool isSpread = false;
    memset(visited , 0 , sizeof(visited));
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(visited[i][j]) continue;
            list.clear();
            sum = cnt = 0;
            dfs(j,i);
            if(cnt == 1) continue;
            for(auto nation : list){
                map[nation.second][nation.first] = sum / cnt;
                isSpread = true;
            }
        }
    }
    return isSpread;
}
int main(){
    cin >> N >> L >> R;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            scanf("%d" , &map[i][j]);
        }
    }
    int cnt = 0 ;
    while(true){
        if(spread())
            ++cnt;
        else break;
    }
    cout << cnt << endl;
}