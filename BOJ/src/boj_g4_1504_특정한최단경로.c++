#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define MAX 800
#define INF 9999999
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.20

*난이도 : G4
*개인 풀이 시간 : 2hr 
*개인 난이도 : 3/5 
*분류 : 다익스트라 알고리즘
*풀이 : 시작점, 경로 중 하나, 끝 각각 다익스트라를 한 다음 비교를 통해 최소값을 얻어냈다.
*느낀점 : 
        다익스트라의 구동원리에 대해 자세히 이해하지 못해서 구현에 고생을 겪었다.
        다익스트라에 사용할 그래프를 인접리스트 구현한다면 우선순위큐의 cost를 사용할 명분이 생긴다. 
            pop해서 얻은 cost와 현재 값을 비교해서 더 작다면 업데이트 할 수 있기 때문에
            하지만 나는 이번에 배열로 그래프를 표현해서 배열에 접근함으로써 cost는 항상 O(1)로 구할 수 있었다. 
            그럼에도 불구하고 cost를 기준으로 정렬하는 priority_queue를 사용한 이유는 같은 점에 대해서 중복 수행을 막기 위해서다.
            visited 배열을 유지하는 않은 대신 cost(다익스트랄 시작점에서 현재점까지 거리)를 가지고 할 수 있는 것은,
            cost가 입력된 시점의 거리보다 현재의 거리가 짧다면 힙에 push한 뒤로 다른 작업이 해당 점에 대해서 수행됐고 -> 더 작은 cost를 가진 node가 민힙에 들어오고 현재 pop된 노드보다 일찍 수행됐을 것이다.
        Priority_queue의 사용으로 알고리즘 성능을 20% 향상했다.
        v1,v2가 1,n과 같은 경우를 굉장히 복잡하게 생각하고 일일이 코드로 분기했으나 결국은 자기자신에 대한 가중치를 0으로 함으로써 해결했다. => 간단하게 생각하자.
        맵 한가지를 두고 다익스트라를 여러번 돌려도 상관없었다. 다익스트라의 경우 a행 또는 a열만 수정하기 때문에 a가 각각 다르다면 모두 독립적이다. 
        INF의 최대값은 비둘기집의 원리에 의해 {최대 간선수 : 800(정점의 최대값)-1, 간선당 최대값 1000} 곱보다 크기만 하면 된다. 무식하게 크게 잡고 long long 쓸 필요가 없음.
*/

struct info{
    int a,b,dis;
};
vector<info> graph;
int map[MAX+1][MAX+1];
int n,e;

void findPath(int a){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i=1;i<=n;i++)
        if(map[a][i]!=INF) pq.push(make_pair(map[a][i],i));
    while(!pq.empty()){
        int cur=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        //중복 검사
        if(cost>map[a][cur]) continue;
        for(int i=1;i<=n;i++){
            if(map[cur][i]!=INF){
                //map[a][a]==0인 경우 0+map[a][i]<map[a][i]로 변하기 때문에 알고리즘엔 문제가 없다.
                if(map[a][cur]+map[cur][i]<map[a][i]){
                    map[a][i]=map[a][cur]+map[cur][i];
                    map[i][a]=map[a][i];
                    //변할 경우에만 넣는다.
                    pq.push(make_pair(map[a][i],i));
                }
            }
        }
    }
}

int main(){
    int required[2];
    cin>>n>>e;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++)
            map[i][j]=INF;
    }
    for(int i=0;i<e;i++){
        int a,b,c;
        cin>>a>>b>>c;
        map[a][b]=map[b][a]=c;
    }
    cin>>required[0]>>required[1];
    //자기자신까지 경로의 가중치는 0이라도 괜찮다.
    map[required[0]][required[0]]=map[required[1]][required[1]]=0;
    //맵 하나를 두고 다익스트라 3번 수행.
    findPath(required[0]);
    findPath(1);
    findPath(n);

    //두가지 경우에 대해서 체크
    int res=min(map[1][required[0]]+map[n][required[1]],map[1][required[1]]+map[n][required[0]]);
    res+=map[required[0]][required[1]];
    res=res>=INF?-1:res;
    cout<<res<<endl;
}