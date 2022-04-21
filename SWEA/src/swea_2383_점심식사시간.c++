#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#define INF 99999999
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX 10
using namespace std;
 
 /*
@author  :  Jinho Jeong
@date    :  2022.04.20

*난이도 : D2
*개인 풀이 시간 : 1 + 10/60 Hour
*개인 난이도 : 2/5 
*분류 : 완탐, 구현, 시뮬, 삼성문제, 삼성 역테 문제
*풀이 : 
    
*느낀점 : 완탐 문제라고 파악하지 못했음.

*/


int T , N;
int map[MAX][MAX];
vector< pair<int,int> > people;
vector< pair<int,int> > dist;
vector< pair<int,int> > stairs;
bool isFirst[11];
int minTime;
 
int calTime(vector<int> &ls , int dist){
    queue<int> que;
    int time = 0;
    for(int t : ls){
        /*
        1. 내가 도착 => 나 도착 시간보다 탈출 시간이 이른 사람은 모두 pop 나 도착 시간에 같이 도착한 사람까지 모두 Pop
        2. 만약 que 사이즈가 2이하이면 계단에 들어가기
        3. 그게 아니라면 하나 앞에 한명 나올때까지 기다렸다가 들어가는데 이때 예상 탈출 시간은 t가 아닌 맨 앞 사람 나온 시간
        */
       
       //que에 들어가는 것은 끝나는 시간
       //만약 내가 계단을 내려가기 시작하는 시간보다 작거나 같은 시간이 아직 큐에 있다면 다 pop함.
       //이는 이미 계단에 있는 사람에 의해 내가 내려가는데 어떤 시간적 영향을 받지 않기 때문
        while(!que.empty() && que.front() <= t + 1){
            time = que.front();
            que.pop();
        }
        // Pop이후에 계단에 자리가 남아있으면
        if(que.size() < 3){
            //내가 계단까지 온 시간 + 한타임 이후부터 내려가기 시작 + 계단길이 = 계단 탈출 시점
            que.push(t + 1 + dist);
            continue;
        }
        else{
            //그게 아니라면 que의 맨 앞 사람이 내려올때까지 기다렸다가 que에 삽입된다.
            //이는 que 맨 앞(계단에서 도착점에서 가장 가까운 사람)이 계단을 탈출하고 내가 바로 계단을 내려가는 것이기 때문에
            //탈출 시간 + 계단길이가 내 도착시간
            time = que.front();
            que.pop();
            que.push(time + dist);
        }
    }
    //만약 계단에 사람이 남아있다면 다 빼고 마지막으로 남은 사람이 도착 시점에 총 걸린 시간
    while(!que.empty()){
        time = que.front();
        que.pop();
    }
    return time;
}
void recul(int idx){
    if(idx == dist.size()){
        //만약 모든 사람이 어느 계단을 사용할지 정해졌다면 시간을 계산함
        vector<int> f, s;
        for(int i = 0 ; i < dist.size() ; i++){
            //선택 여부에 따라 벡터에 담기
            if(isFirst[i]){
                f.push_back(dist[i].first);
            }
            else{
                s.push_back(dist[i].second);
            }
        }
        //벡터 정렬(도착 시간 순으로 정렬됨)
        sort(f.begin() , f.end());
        sort(s.begin() , s.end());
        //각각에 대해 걸리는 시간을 계산한다
        int ret = calTime(f , map[stairs[0].second][stairs[0].first]);
        if(ret >= minTime) return;
        //둘 중 오래 걸리는 쪽이 총 걸린 시간임 때문에 max 취해줌
        ret = max(ret , calTime(s , map[stairs[1].second][stairs[1].first]));
        //걸린 시간이 적으면 minTime update
        if(minTime > ret) minTime = ret;
        return;
    }
    recul(idx + 1);
    //첫번째 계단을 사용할 것인지 여부
    isFirst[idx] = true;
    recul(idx + 1);
    //백트래킹 형식으로 진행
    isFirst[idx] = false;
}
 
int main(){
    cin >> T;
    for(int cs = 1 ; cs <= T ; cs++){
        cin >> N;
        people.clear();
        dist.clear();
        stairs.clear();
        memset(isFirst , 0 , sizeof(isFirst));
        minTime = INF;
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ; j < N ; j++){
                scanf("%d" , &map[i][j]);
                if(map[i][j] == 1)
                    people.push_back({j,i});
                else if(map[i][j] > 1){
                    stairs.push_back({j,i});
                }
            }
        }
        //연산 내내 필요한 것은 사람당 2 계산 사이 걸리는 시간이기 때문에 입력과 동시에 바로 양쪽 계단까지 걸리는 시간을(맨하탄 거리) 계산해줌
        for(pair<int,int> p : people){
            int a = ABS(p.first - stairs[0].first) + ABS(p.second - stairs[0].second);
            int b = ABS(p.first - stairs[1].first) + ABS(p.second - stairs[1].second);
            dist.push_back({a,b});
        }
        recul(0);
        cout << "#" << cs << " " << minTime << "\n";
    }
    return 0;
}