#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define MAX 4
using namespace std;

/*
4*4
1. 복제 마법 수행 , 효과 5번에서 발현 , 현재 상태를 복사할 필요 있음
2. 물고기 이동은 상어가 있는 칸, 물고기 냄새가 있는 칸, 격자 범위 밖으로 못감 / 갈 수 있는 방향으로 찾아갈때까지 45도 반시계 회전
3. 상어는 연속해서 3칸, 진행 방향에 물고기가 있음 잡아먹고 물고기는 냄새를 남김 / 경로의 선택은 잡은 물고기 수가 많고 경로가 사전상으로 앞서는 경우
4. 두번 전 연습에서 생긴 물고기 냄새가 격자에서 사라짐
5. 복제마법 완료
*/

struct INFO{
    int x , y, dir;
};
struct PATH{
    int fCnt;
    string p;
    bool operator<(const PATH& b)const{
        if(fCnt != b.fCnt) return fCnt < b.fCnt;
        return p > b.p;
    }
};
const int dx[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
const int dy[] = {0 , -1 , -1 , -1 , 0 , 1 , 1 , 1};
const int sdx[] = {0 , 0 , -1 , 0 , 1};
const int sdy[] = {0 , -1 , 0 , 1 , 0};
int M , S;
int curTime = 0;
int scent[MAX][MAX];
bool sVisited[MAX][MAX];
priority_queue<PATH> pq;
vector<INFO> fishs;
vector<INFO> map[MAX][MAX];
pair<int,int> shark;

bool isInside(int x, int y){
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

vector<int> pathTrack;
void sharkMove(int depth , int x , int y , int cnt){
    if(depth == 3){
        string temp = "";
        for(int a : pathTrack)
            temp += to_string(a);
        pq.push((struct PATH){cnt , temp});
        return;
    }
    for(int dir = 1 ; dir <= 4 ; dir++){
        int nx = x + sdx[dir];
        int ny = y + sdy[dir];
        bool isFirst = true;
        if(!isInside(nx , ny)) continue;
        pathTrack.push_back(dir);
        if(sVisited[ny][nx]) isFirst = false;
        if(isFirst){
            sVisited[ny][nx] = true;
            sharkMove(depth + 1 , nx , ny , cnt + map[ny][nx].size());
            sVisited[ny][nx] = false;
        }
        else
            sharkMove(depth + 1 , nx , ny , cnt);
        pathTrack.pop_back();
    }
    sVisited[y][x] = false;
}

void func(){
    for(int i = 0 ; i < MAX ; i++){
        for(int j = 0 ; j < MAX ; j++)
            map[i][j].clear();
    }
    for(INFO fi : fishs){
        int dir = fi.dir;
        int x = fi.x;
        int y = fi.y;
        int cnt;
        for(cnt = 0 ; cnt < 8 ; cnt++ , dir = (dir + 7) % 8){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if(!isInside(nx , ny)) continue;
            if(nx == shark.first && ny == shark.second) continue;
            if(scent[ny][nx] != -1 && curTime - scent[ny][nx] <= 2) continue;
            break;
        }
        if(cnt == 8){
            //갈 수 있는 곳 없음
            map[y][x].push_back(fi);
            continue;
        }
        x += dx[dir];
        y += dy[dir];
        map[y][x].push_back((struct INFO){x , y , dir});
    }
    pq = priority_queue<PATH>();
    sharkMove(0 , shark.first , shark.second , 0);
    PATH top = pq.top();    
    for(int i = 0 ; i < 3 ; i++){
        shark.first += sdx[(top.p[i] - '0')];
        shark.second += sdy[(top.p[i] - '0')];
        if(map[shark.second][shark.first].size()){
            map[shark.second][shark.first].clear();
            scent[shark.second][shark.first] = curTime;
        }
    }
    curTime++;
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            if(map[i][j].size()){
                for(INFO a : map[i][j])
                    fishs.push_back(a);
            }
        }
    }
}

int main(){
    freopen("input.txt" , "r" , stdin);
    memset(scent , -1 , sizeof(scent));
    cin >> M >> S;
    int y , x , dir;
    for(int i = 0 ; i < M ; i++){
        scanf("%d %d %d", &y , &x , &dir);
        fishs.push_back((struct INFO){x - 1 , y - 1, dir - 1});
    }
    cin >> y >> x;
    shark = make_pair(x - 1 , y - 1);
    while(S--){
        func();
    }
    cout << fishs.size() << endl;
    return 0;
}