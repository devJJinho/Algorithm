#include <iostream>
#include <deque>
#include <cstring>
#define MAX 100
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define INF 9999999
using namespace std;

int N , K;
deque<int> pool[100];
const int dx[] = {0 , 0 , -1 , 1};
const int dy[] = {-1 , 1 , 0 , 0};
int orgaCnt;

pair<int,int> roll(){
    int x = 1 , y = 1 ; 
    while(pool[0].size() - x >= y){
        for(int cnt = 0 ; cnt < x ; cnt++){
            for(int i = 0 ; i < y ; i++){
                int cur = pool[i].front();
                pool[i].pop_front();
                pool[x - cnt].push_back(cur);
            }
        }
        int t = y;
        y = x + 1;
        x = t;
    }
    return { x , y};
}

void cali(int x , int y){
    int temp[MAX][MAX];
    memset(temp , 0 , sizeof(temp));
    for(int i = 0 ; i < y ; i++){
        for(int j = 1 ; j < pool[i].size() ; j++){
            int gap = ABS(pool[i][j] - pool[i][j - 1]);
            gap /= 5;
            if(gap > 0){
                if(pool[i][j] > pool[i][j - 1]){
                    temp[i][j] -= gap;
                    temp[i][j - 1] += gap;
                }
                else{
                    temp[i][j] += gap;
                    temp[i][j - 1] -= gap;
                }
            }
        }
    }
    for(int i = 1 ; i < y ; i++){
        for(int j = 0 ; j < x ; j++){
            int gap = ABS(pool[i][j] - pool[i - 1][j]);
            gap /= 5;
            if(gap > 0){
                if(pool[i][j] > pool[i - 1][j]){
                    temp[i][j] -= gap;
                    temp[i - 1][j] += gap;
                }
                else{
                    temp[i][j] += gap;
                    temp[i - 1][j] -= gap;
                }
            }
        } 
    }
    for(int i = 0 ; i < y ; i++){
        for(int j = 0 ; j < pool[i].size() ; j++){
            pool[i][j] += temp[i][j];
        }
    }
}

void serialize(int x , int y){
    deque<int> temp;
    for(int cnt = 0 ; cnt < x ; cnt++){
        for(int i = 0 ; i < y ; i++){
            int cur = pool[i].front();
            pool[i].pop_front();
            temp.push_back(cur);
        }
    }
    for(int j = 0 ; j < pool[0].size() ; j++)
        temp.push_back(pool[0][j]);
    pool[0] = temp;
}

void stack(){
    int dist = pool[0].size();
    dist /= 4;
    for(int cnt = 0 ; cnt < dist ; cnt++){
        int cur = pool[0].front();
        pool[0].pop_front();
        pool[1].push_front(cur);
    }
    for(int cnt = 0 ; cnt < dist ; cnt++){
        int cur = pool[0].front();
        pool[0].pop_front();
        pool[2].push_back(cur);
    }
    for(int cnt = 0 ; cnt < dist ; cnt++){
        int cur = pool[0].front();
        pool[0].pop_front();
        pool[3].push_front(cur);
    }
}
bool func(){
    int minCnt = INF , maxCnt = 0;
    for(int f : pool[0]){
        minCnt = min(minCnt , f);
        maxCnt = max(maxCnt , f);
    }
    if(maxCnt - minCnt <= K)
        return true;
    orgaCnt++;
    for(int &f : pool[0])
        if(f == minCnt) f++;
    pair<int,int> size = roll();
    cali(size.first , size.second);
    serialize(size.first , size.second);
    stack();
    cali(pool[0].size() , 4);
    serialize(pool[0].size() , 4);

    return false;
}
int main(){
    cin >> N >> K;
    int a;
    for(int i = 0 ; i < N ; i++){
        cin >> a;
        pool[0].push_back(a);
    }
    while(true){
        if(func()) break;
    }
    cout << orgaCnt << endl;
}