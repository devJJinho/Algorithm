#include <iostream>
#include <cstring>
#include <vector>
#define MAX 4
#define EMP -1
#define SWAP(a,b,t) ((t) = (a) , (a) = (b) , (b) = (t))
using namespace std;

struct INFO{
    int idx , x , y , dir;
};
struct SHARK{
    int x , y , dir;
};

bool isInside(int x , int y){
    return x >= 0 && x < MAX && y >= 0 && y < MAX;
}
int map[20][4][4];
const int dx[] = {0 , -1 , -1 , -1 , 0 , 1 , 1 , 1};
const int dy[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};

int recul(int idx , SHARK shark , vector<INFO> fishs){   
    for(int i = 1 ; i < 17; i++){
        if(fishs[i].idx == EMP) continue;
        INFO& cur = fishs[i];
        int dir , cnt;
        for(dir = cur.dir , cnt = 0 ; cnt < 8 ; dir = (dir + 1) % 8 , cnt++){
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if(isInside(nx , ny)){
                if(nx == shark.x && ny == shark.y) continue;
                int t;
                int oppIdx = map[idx][ny][nx];
                if(oppIdx == EMP){
                    SWAP(map[idx][cur.y][cur.x] , map[idx][ny][nx] , t);
                    cur.x = nx;
                    cur.y = ny;
                }
                else{
                    SWAP(map[idx][cur.y][cur.x] , map[idx][ny][nx] , t);
                    SWAP(cur.x , fishs[oppIdx].x , t);
                    SWAP(cur.y , fishs[oppIdx].y , t);
                }
                break;
            }
        }
        if(cnt != 8)
            cur.dir = dir;
    }
    int ret = 0;
    int sx = shark.x + dx[shark.dir];
    int sy = shark.y + dy[shark.dir];
    while(isInside(sx , sy)){
        int delIdx = map[idx][sy][sx];
        if(delIdx != EMP){
            memcpy(map[idx + 1] , map[idx] , sizeof(map[idx + 1]));
            map[idx + 1][sy][sx] = EMP;
            int delDir = fishs[delIdx].dir;
            vector<INFO> temp = fishs;
            temp[delIdx].idx = EMP;
            ret = max(ret , delIdx + recul(idx + 1 , {sx , sy , delDir} , temp));
        }
        sx += dx[shark.dir];
        sy += dy[shark.dir];
    }
    return ret;
}

int main(){
    freopen("input.txt" , "r", stdin);
    vector<INFO> fishs;
    fishs.resize(17);
    SHARK shark;
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            int a , b ;
            cin >> a >> b;
            b--;
            map[0][i][j] = a;
            fishs[a] = {a , j , i , b};
        }
    }
    int initIdx = map[0][0][0];
    shark = {0 , 0, fishs[initIdx].dir};
    map[0][0][0] = EMP;
    fishs[initIdx].idx = EMP;
    cout << initIdx + recul(0 , shark , fishs) << endl;
}