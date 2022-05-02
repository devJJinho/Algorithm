#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define SWAP(a , b , t) ((t) = (a) , (a) = (b) , (b) = (t))
#define MAX 20
#define DEL -2
using namespace std;

/*
블록 그룹은 연결된 블록의 집합.
기준 블록은 무지개 블록이 아닌 블록 중에서 행의 번호가 가장 작은 블록
visited는 무지개에 대해서 초기화 해야함 -> 공유 가능
가장 큰 블록 그룹이 필요함. 블록그룹을 만들고 벡터에 담기.
기준 블록을 찾아야함
pq에는 블록그룹을 다 만들고 그 정보만을 담아서
*/

struct INFO{
    int idx , size , rbSize , x , y;
    bool operator<(const INFO& b)const{
        if(size != b.size) return size < b.size;
        if(rbSize != b.rbSize) return rbSize < b.rbSize;
        if(y != b.y) return y < b.y;
        return x < b.x;
    }
};

struct NODE{
    int x , y;
    bool isRainbow;
    bool operator<(const NODE& b)const{
        if(isRainbow != b.isRainbow) return isRainbow < b.isRainbow;
        if(y != b.y) return y < b.y;
        return x < b.x;
    }
};

int N , M;
const int dx[] = { 0 , 0 , -1 , 1 };
const int dy[] = { -1 , 1 , 0 , 0 };
int map[20][20];
vector<vector<NODE> > blockGroups;
priority_queue<INFO> pq;
int sum;
void rotate(){
    int temp[N][N];
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++)
            temp[i][j] = map[i][j];
    }
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++)
            map[i][j] = temp[j][N - 1 - i];
    }
}

void searchBlock(){
    blockGroups.clear();
    bool visited[N][N];
    int idx = 0;
    memset(visited, 0 , sizeof(visited));
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(map[i][j] >= 1 && map[i][j] <= 5 && !visited[i][j]){
                visited[i][j] = true;
                int color = map[i][j];
                vector<NODE> temp;
                vector<pair<int,int> > rainbow;
                queue<pair<int,int> > que;
                que.push(make_pair(j , i));
                while(!que.empty()){
                    pair<int,int> cur = que.front();
                    que.pop();
                    bool isRainbow = map[cur.second][cur.first] == 0;
                    if(isRainbow){
                        rainbow.push_back(cur);
                    }
                    temp.push_back((struct NODE){cur.first , cur.second , isRainbow});
                    for(int dir = 0 ; dir < 4 ; dir++){
                        int nx = cur.first + dx[dir];
                        int ny = cur.second + dy[dir];
                        if(nx >= 0 && nx < N && ny >= 0 && ny < N){
                            if(map[ny][nx] == 0 || map[ny][nx] == color){
                                if(visited[ny][nx]) continue;
                                que.push(make_pair(nx , ny));
                                visited[ny][nx] = true;
                            }
                        }
                    }
                }
                for(pair<int,int> pt : rainbow){
                    visited[pt.second][pt.first] = false;
                }
                if(temp.size() >= 2){
                    sort(temp.begin() , temp.end());
                    for(auto pt : temp)
                        cout<<pt.isRainbow<<" "<<pt.y<<" "<<pt.x<<endl;
                    cout<<"-----"<<endl;
                    pq.push((struct INFO){idx++ , temp.size() , rainbow.size() , temp[0].x , temp[0].y});
                    blockGroups.push_back(temp);
                }
            }
        }
    }
}

void gravity(){
    int t;
    for(int i = N - 1 ; i > 0 ; i--){
        for(int j = 0 ; j < N ; j++){
            if(map[i][j] != DEL) continue;
            int k;
            for(k = i - 1 ; k >= 0 ; k--){
                if(map[k][j] != DEL) break;
            } 
            if(k >= 0){
                if(map[k][j] == -1) continue;
                SWAP(map[i][j] , map[k][j] , t);
            }
        }
    }
}
void printMap(){
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++)
            cout<<map[i][j]<<" ";
        cout<<endl;
    }
    cout<<"------"<<endl;
}
bool func(){
    pq = priority_queue<INFO>();
    searchBlock();
    if(pq.empty()) return false;
    int size = blockGroups[pq.top().idx].size();
    sum += size * size;
    for(NODE pt : blockGroups[pq.top().idx]){
        map[pt.y][pt.x] = DEL;
    }
    // while(!pq.empty()){
    //     auto cur = pq.top();
    //     pq.pop();
    //     cout<<cur.idx <<" "<<cur.size<<" "<<cur.x<<" "<<cur.y<<endl;
    // }
    // cout<<"==-------0"<<endl;
    // printMap();
    gravity();
    // printMap();
    rotate();
    // printMap();
    gravity();
    // printMap();
    return true;
}

int main(){
    freopen("input.txt" , "r" , stdin);
    cin >> N >> M;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++)
            cin >> map[i][j];
    }
    while(true){
        if(!func()) break;
    }
    cout << sum << endl;
}