#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.03

*난이도 : Level 3
*개인 풀이 시간 : 30min 
*개인 난이도 : 2/5 
*분류 : 그래프 / 최단거리 찾기 / BFS 사용 / 약간의 dp
*풀이 : 간선에 가중치가 없기 때문에 다익스트라 알고리즘 보다 간단하게 구현했다.
       그래프가 간선 리스트로 주어지기 때문에 map을 만드는 과정이 필요했다.
       양방향 그래프이기 때문에 한번에 from->to, to->from 두 방식 모두 입력해주고, bool visited[]로 중복을 방지하는게 주요했다.
*느낀점 : 
        백터 선언에 사이즈와 초기값을 성정하는 방법을 배움
        적절한 자료구조 사용으로 그래프를 표현하는 법이 중요함.
        그래프는 dp, 탐색이 모두 쓰이는 듯 하다.
        간선의 가중치가 같은 경우 bfs를 사용하면 최단거리의 비교가 불필요하다.
*/

bool cmp(int a,int b){
    return a>b;
}

int solution(int n, vector<vector<int>> edge) {
    //벡터 선언시 사이즈와 초기값 설정하기
    vector<int> distance(n+1,0);
    vector<vector<int>> map(n+1);
    vector<bool> visited(n+1,false);
    queue<int> q;

    for(vector<int> point:edge){
        int from=point[0];
        int to=point[1];
        //양방향 그래프 구현
        map[from].push_back(to);
        map[to].push_back(from);
    }
    q.push(1);
    visited[1]=true;

    while(!q.empty()){
        int curPoint=q.front();
        q.pop();

        for(int i=0;i<map[curPoint].size();i++){
            int nextPoint=map[curPoint][i];
            if(!visited[nextPoint]){
                visited[nextPoint]=true;
                q.push(nextPoint);
                //간선의 가중치가 같고 bfs이기 때문에 값 비교 후 갱신이 필요 없다. 최단거리 보장이기 때문!!
                //distance 설정 후 visited 체크 때문에 다시 돌아올 일이 없음
                distance[nextPoint]=distance[curPoint]+1;
            }
        }
    }
    int answer = 0;
    sort(distance.begin(),distance.end(),cmp);
    for(int a:distance){
        if(a==distance[0])answer++;
        else break;
    }
    return answer;
}