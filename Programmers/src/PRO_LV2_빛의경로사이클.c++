#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.22

*난이도 : Level2
*개인 풀이 시간 : 40/60 Hour
*개인 난이도 : 2/5 
*분류 : 구현, 그래프 탐색, 사이클 체크
*풀이 : 

*느낀점 : 풀이 생각까지 많은 시간이 걸림
*/

const int dx[] = {0,1,0,-1};
const int dy[] = {-1,0,1,0};
bool visited[4][500][500];
int N , M;

void findCycle(int x, int y, int dir, vector<int>& ans, vector<string>& grid){
    //만약 방문한 적이 있으면 진행하지 않음. 같은 결과 나오기 때문
    if(visited[dir][y][x]) return;
    //사이클(방문한 곳에 다시 방문) 하기까지 얼마나 걸렸는지 카운트함
    int cnt = 0;
    while(!visited[dir][y][x]){
        ++cnt;
        //방문체크
        visited[dir][y][x] = true;
        //x,y 진행
        x = (x + dx[dir] + M) % M;
        y = (y + dy[dir] + N) % N;
        //방향 변환
        if(grid[y][x] == 'L') dir = (dir + 3) % 4;
        else if(grid[y][x] == 'R') dir = (dir + 1) % 4;
    }
    //결과 push
    ans.push_back(cnt);
}

vector<int> solution(vector<string> grid) {
    vector<int> answer;
    N = grid.size();
    M = grid[0].length();
    memset(visited , 0 , sizeof(visited));
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++){
            for(int dir = 0 ; dir < 4 ; dir++){
                //완탐 형식으로 진행
                findCycle(j , i , dir , answer , grid);
            }
        }
    }
    //정렬 후 return
    sort(answer.begin() , answer.end());
    return answer;
}