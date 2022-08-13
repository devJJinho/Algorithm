#include <iostream>
#include <queue>
#include <string.h>
#include <unordered_set>
#include <cmath>
#define MAX 20
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.08.12

*난이도 : G5
*개인 풀이 시간 : 40min 
*개인 난이도 : 2/5
*분류 : 구현, 시뮬, 삼성 기출
*풀이 : 우선 순위를 만족하는 하나를 찾기 위해 pq 사용
       개인이 선호하는 4개 중 하나가 만족하는지 찾기위해 hash 사용
       
*느낀점 : 
*/

struct INFO{
    int cnt , empty , row , col;
    bool operator<(const INFO &b)const{
        if(cnt != b.cnt) return cnt < b.cnt;
        if(empty != b.empty) return empty < b.empty;
        if(row != b.row) return row > b.row;
        return col > b.col;
    }
};
const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};

int N;
int map[MAX][MAX];
unordered_set<int> preferHash[401];

bool isInside(int x, int y){
    return x >= 0 && x < N && y >= 0 && y < N;
}

int cal(){
    int total = 0;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            int subTotal = 0;
            int stuNum = map[i][j];
            for(int dir = 0 ; dir < 4 ; dir++){
                int nx = j + dx[dir];
                int ny = i + dy[dir];
                if(!isInside(nx , ny)) continue;
                if(preferHash[stuNum].find(map[ny][nx]) != preferHash[stuNum].end())
                    ++subTotal;
            }
            if(subTotal < 2){
                total += subTotal;
                continue;
            }
            total += pow(10 , subTotal - 1);            
        }
    }
    return total;
}

int main(){
    memset(map , sizeof(map) , 0);
    cin >> N;
    for(int t = 0 ; t < N * N ; t++){
        priority_queue<INFO> pq;
        int stuNum;
        cin >> stuNum;
        for(int i = 0 ; i < 4 ; i++){
            int toward;
            cin >> toward;
            preferHash[stuNum].insert(toward);
        }
        for(int y = 0 ; y < N ; y++){
            for(int x = 0 ; x < N ; x++){
                if(map[y][x] != 0) continue;
                int pre_cnt = 0, emp_cnt = 0;
                for(int dir = 0 ; dir < 4 ; dir++){
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if(!isInside(nx, ny)) continue;
                    if(map[ny][nx] == 0){
                        ++emp_cnt;
                        continue;
                    }
                    if(preferHash[stuNum].find(map[ny][nx]) != preferHash[stuNum].end()) 
                        ++pre_cnt;
                }
                pq.push({pre_cnt , emp_cnt , y , x});
            }
        }
        INFO temp = pq.top();
        map[temp.row][temp.col] = stuNum;
    }
    int ret = cal();
    cout << ret;
    return 0;
}