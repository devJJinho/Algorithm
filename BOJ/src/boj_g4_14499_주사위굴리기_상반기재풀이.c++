#include <iostream>
#include <deque>
#define MAX 20
using namespace std;

class CUBE{
    deque<int> row;
    deque<int> col;
public:
    CUBE(){
        row = {0,0,0,0};
        col = {0,0,0,0};
    }
    void move(int dir){
        switch(dir){
            case 0 : right(); break;
            case 1 : left(); break;
            case 2 : up(); break;
            default : down();
        }
    }
    void up(){
        int cur = col.back();
        col.pop_back();
        col.push_front(cur);
        row[0] = col[0];
        row[2] = col[2];
    }
    void down(){
        int cur = col.front();
        col.pop_front();
        col.push_back(cur);
        row[0] = col[0];
        row[2] = col[2];
    }
    void left(){
        int cur = row.front();
        row.pop_front();
        row.push_back(cur);
        col[0] = row[0];
        col[2] = row[2];
    }
    void right(){
        int cur = row.back();
        row.pop_back();
        row.push_front(cur);
        col[0] = row[0];
        col[2] = row[2];
    }
    int getTop(){
        return row[2];
    }
    int getBottom(){
        return row[0];
    }
    void writeBottom(int a){
        row[0] = col[0] = a;
    }
};

const int dx[] = {1 , -1 , 0 , 0};
const int dy[] = {0 , 0 , -1 , 1};
int N , M;
int map[MAX][MAX];
bool isInside(int x , int y){
    return x >= 0 && x < M && y >= 0 && y < N;
}
int main(){
    freopen("input.txt" , "r" , stdin);
    CUBE cube;
    cin >> N >> M;
    int x , y , k , dir;
    cin >> y >> x >> k;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++)
            scanf("%d" , &map[i][j]);
    }
    while(k--){
        cin >> dir;
        dir--;
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(!isInside(nx , ny)) continue;
        x = nx;
        y = ny;
        cube.move(dir);
        if(map[y][x] == 0){
            map[y][x] = cube.getBottom(); 
        }
        else{
            cube.writeBottom(map[y][x]);
            map[y][x] = 0;
        }
        cout << cube.getTop() << "\n";
    }
}