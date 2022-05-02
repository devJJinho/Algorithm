#include <iostream>
#include <queue>
#define MAX 20
using namespace std;

struct SCENT{
    int sIdx , time;
};

struct SHARK{
    int idx , x , y , dir;
    bool operator<(const SHARK& b)const{
        return idx > b.idx;
    }
};
SCENT scent[MAX][MAX];
int N , M , K;
int ck = 1;
const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};
const int opp[] = {1 , 0 , 3 , 2};
vector<SHARK> sharks;
vector<vector<vector<int> > > sDir;


bool canGo(int x , int y){
    if(x < 0 || x >= N || y < 0 || y >= N) return false;
    if(scent[y][x].time && ck - scent[y][x].time < K) return false;
    return true;
}
bool isInside(int x , int y){
    return x >= 0 && x < N && y >= 0 && y < N;
}
void func(){
    priority_queue<SHARK> pq[N][N];
    for(int i = 0 ; i < sharks.size() ; i++){
        SHARK cur = sharks[i];
        scent[cur.y][cur.x] = {cur.idx , ck};
    }
    for(int i = 0 ; i < sharks.size() ; i++){
        SHARK cur = sharks[i];
        bool isFind = false;
        int preDir = -1;
        for(int dir = 0 ; dir < 4 ; dir++){
            int ndir = sDir[cur.idx][cur.dir][dir];
            int nx = cur.x + dx[ndir];
            int ny = cur.y + dy[ndir];
            if(canGo(nx ,ny)){
                pq[ny][nx].push({cur.idx , nx , ny , ndir});
                isFind = true;
                break;
            }
            if(isInside(nx , ny)){
                if(scent[ny][nx].sIdx == cur.idx && preDir == -1)
                    preDir = ndir;
            }
        }
        if(isFind) continue;
        int nx = cur.x + dx[preDir];
        int ny = cur.y + dy[preDir];
        pq[ny][nx].push({cur.idx , nx , ny , preDir});
    }
    sharks.clear();
    // for(int i = 0 ; i < N ; i++){
    //     for(int j = 0 ; j < N ; j++){
    //         cout<<pq[i][j].size()<< " ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"-----"<<endl;

    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(pq[i][j].size()){
                sharks.push_back(pq[i][j].top());
            }
        }
    }
    ck++;
}
int main(){
    freopen("input.txt" , "r" , stdin);
    cin >> N >> M >> K;
    int a;
    sharks.resize(M);
    int cnt = 1;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            cin >> a;
            if(a){
                a--;
                sharks[a] = {a , j , i , 0};
            }
        }
    }
    for(int i = 0 ; i < M ; i++){
        cin >> a;
        sharks[i].dir = a - 1;
    }
    for(int i = 0 ; i < M ; i++){
        vector<vector<int> > perShark;
        for(int dir = 0 ; dir < 4 ; dir++){
            vector<int> temp;
            for(int ndir = 0 ; ndir < 4 ; ndir++){
                int t;
                cin >> t;
                temp.push_back(t - 1);
            }
            perShark.push_back(temp);
        }
        sDir.push_back(perShark);
    }
    int clkCnt = 0;
    while(true){
        if(sharks.size() == 1) break;
        if(++clkCnt == 1001) break;
        func();
    }
    cout << (clkCnt == 1001 ? -1 : clkCnt) << endl;
}