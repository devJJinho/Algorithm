#include <iostream>
#include <vector>
#define MAX 101
using namespace std;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};
int N;
bool map[MAX][MAX];

void makeCurve(int x, int y, int dir, int g){
    vector<int> path;
    path.push_back(dir);
    map[y][x] = true;
    x += dx[dir];
    y += dy[dir];
    map[y][x] = true;
    while(g--){
        int size = path.size();
        for(int i = size - 1 ; i >= 0 ; i--){
            int ndir = (path[i] + 1) % 4;
            path.push_back(ndir);
            x += dx[ndir];
            y += dy[ndir];
            map[y][x] = true;
        }
    }
}
int main(){
    cin >> N;
    int x, y, dir, g;
    while(N--){
        cin >> x >> y >> dir >> g;
        makeCurve(x, y, dir, g);
    }
    int cnt = 0;
    for(int i = 0 ; i < 100 ; i++){
        for(int j = 0 ; j < 100 ; j++){
            if(map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
                ++cnt;
        }
    }
    cout << cnt << endl;
}