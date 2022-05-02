#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define MAX 10
using namespace std;

struct INFO{
    int idxA , idxB , dist;
    bool operator<(const INFO& b)const{
        return dist > b.dist;
    }
};

const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};

bool map[MAX][MAX];
int idxMap[MAX][MAX];
int N , M;
vector<vector<pair<int,int> > > islands;
int parent[MAX * MAX];
priority_queue<INFO> pq;

int findParent(int a){
    if(parent[a] == a) return a;
    return parent[a] = findParent(parent[a]);
}

bool unionParent(int a , int b){
    a = findParent(a);
    b = findParent(b);
    if(a == b) return false;
    if(a > b) parent[a] = b;
    else parent[b] = a;
    return true;
}

bool isInside(int x, int y){
    return x >= 0 && x < M && y >= 0 && y < N;
}

void findIsland(){
    bool visited[N][M];
    memset(visited, 0 , sizeof(visited));
    int idx = 0;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++){
            if(!map[i][j] || visited[i][j]) continue;
            vector<pair<int,int> > temp;
            visited[i][j] = true;
            queue<pair<int , int> > que;
            que.push({j , i});
            while(!que.empty()){
                auto cur = que.front();
                temp.push_back(cur);
                idxMap[cur.second][cur.first] = idx;
                que.pop();
                for(int dir = 0 ; dir < 4 ; dir++){
                    int nx = cur.first + dx[dir];
                    int ny = cur.second + dy[dir];
                    if(!isInside(nx , ny) || visited[ny][nx] || map[ny][nx] == false) continue;
                    que.push({nx , ny});
                    visited[ny][nx] = true;
                }
            }
            islands.push_back(temp);
            idx++;
        }
    }
}

void findBridge(){
    bool visited[N][M];
    memset(visited , 0 , sizeof(visited));
    for(vector<pair<int , int> > island : islands){
        for(pair<int , int> il : island){
            int from = idxMap[il.second][il.first];
            for(int dir = 0 ; dir < 4 ; dir++){
                int nx = il.first + dx[dir];
                int ny = il.second + dy[dir];
                if(!isInside(nx , ny) || map[ny][nx] == 1) continue;
                int len = 0;
                while(isInside(nx , ny)){
                    if(map[ny][nx] == 1) break;
                    len++;
                    nx += dx[dir];
                    ny += dy[dir];
                }
                if(!isInside(nx , ny) || len < 2) continue;
                if(visited[ny][nx]) continue;
                pq.push({from , idxMap[ny][nx] , len});
            }
            visited[il.second][il.first] = true;
        }
       
    }
}

int chooseBridge(){
    int iSize = islands.size();
    int cnt = iSize - 1;
    int sum = 0;
    while(cnt && !pq.empty()){
        auto cur = pq.top();
        pq.pop();
        if(unionParent(cur.idxA , cur.idxB)){
            sum += cur.dist;
            cnt--;
        }
    }
    return cnt ? -1 : sum;
}
int main(){
    cin >> N >> M;
    int a;
    for(int i = 0 ; i < N ; i++)
        for(int j = 0 ; j < M ; j++){
            cin >> a;
            map[i][j] = (bool)a;
        }
    for(int i = 0 ; i < 100 ; i++)
        parent[i] = i;
    findIsland();
    findBridge();
    cout << chooseBridge() << endl;
}