#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#define MAX 10001
#define INF 99999999
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.26

*난이도 : G4
*개인 풀이 시간 : 2hr
*개인 난이도 : 3/5 
*분류 : 다익스트라, priority_queue, 인접행렬
*풀이 : 인전한 pc중 하나라도 감염되면 다음 컴퓨터도 감염된다.
       시작 컴퓨터가 있기 때문에 시작 컴퓨터에서 나머지 컴퓨터까지의 최소시간을 다익스트라로 구하면 된다.
       1차원 cnt의 초기값은 INF이다. INF는 연결된 정점이 없다는 뜻.
       cnt[i]는 i번째까지 감염되는데 걸린 총 시간이다.
       다익스트라를 수행하고 cnt에서 INF이 아닌 값의 수(감염된 컴퓨터), 그 중 최대값 (모든 컴퓨터가 감염되는데 걸린 시간)을 찾아서 반환한다.
*느낀점 : 문제를 잘 못 읽어서 엉뚱한 풀이법으로 삽질했다.
        제발 문제를 잘 읽자.
*/


void dijkstra(vector<vector<pair<int,int>>> &depend,vector<int> &cnt,int c){
    //pq{time,next node}
    //min heap 선언 정렬기준의 pair의 첫번째 '시간'이다. 
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,c});
    while(!pq.empty()){
        int curTime=pq.top().first;
        int curNode=pq.top().second;
        pq.pop();
        //visited 배열은 필요하지 않다. curTime이 기존 시간보다 줄인다면, 시간을 업데이트하고 인접 노드를 pq에 넣는다. 
        if(cnt[curNode]>curTime){
            cnt[curNode]=curTime;
            for(auto next:depend[curNode]){
                //시간의 기준은 지금까지의 시간+다음 시간;
                pq.push({next.second+curTime,next.first});
            }
        }
    }
}

pair<int,int> count(vector<vector<pair<int,int>>> &depend,vector<int> &cnt,int n){
    int max=0;
    int ct=0;
    for(int i=1;i<=n;i++){
        if(cnt[i]!=INF) {
            ++ct;
            //cnt[i]는 c에서 감염되어서 i번째까지 감염되는데 걸리는 총 시간
            //때문에 cnt 중에서 최대값이 전체를 포괄하는 시간이다. 
            if(cnt[i]>max) max=cnt[i];
        }
    }
    return {ct,max};
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int cs;
    cin>>cs;
    while(cs--){
        int n,d,c;
        cin>>n>>d>>c;
        vector<vector<pair<int,int>>> depend(MAX);
        //cnt[]이 일차원인 이유 : 다익스트라 알고리즘의 경우 한 정점에서 나머지 정점까지의 거리이기 때문에 일차원만 있으면 된다.
        vector<int> cnt(MAX,INF);
        for(int i=0;i<d;i++){
            int a,b,s;
            cin>>a>>b>>s;
            depend[b].push_back({a,s});
        }
        dijkstra(depend,cnt,c);
        pair<int,int> res=count(depend,cnt,n);
        cout<<res.first<<" "<<res.second<<endl;
    }
    return 0;
}


/*
기본 아이디어 : 만약 a가 의존하는 2개의 pc가 감염되면 a도 결국 감염된다 => 위상정렬로 의존성을 체크하고 감염되면 의존성을 삭제한다. 
             의존성이 0이 되면 해당 pc를 minheap(시간 기준)에 삽입한다.
             minheap의 top(최소값)순으로 꺼내서 시간을 더하고 의존성을 삭제한다 => 또 의존성이 하나가 된 항목을 heap에 넣는다.

             하지만 이 문제의 경우 의존성 중 한 컴퓨터라도 감염되면 감염되기 때문에 이정도로 복잡한 문제는 아니었다. 
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#define MAX 10000
using namespace std;

int cnt[MAX];

int order(vector<vector<int>> &depend,int c){
    priority_queue()
}

int main(){
    int cs;
    cin>>cs;
    while(cs--){
        int n,d,c;
        memset(cnt,-1,sizeof(cnt));
        for(int i=0;i<d;i++){
            int a,b,s;
            cin>>a>>b>>s;
            depend[b].push_back(a);
            cnt[a]=cnt[a]==-1?1:cnt[a]+1;

        }
        

    }
}