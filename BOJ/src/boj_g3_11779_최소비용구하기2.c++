#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000
#define INF 900000000000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.24
*난이도 : G3
*개인 풀이 시간 : 1hr
*개인 난이도 : 힙, 유향 그래프, 자료구조
*분류 : DP
*풀이 : 유향 그래프에서 가중치가 있음.
       한 정점에서 출발해서 다음 정점으로 도착하는데 그 사이 최단거리로 가야함.
       전체 트리에 대한 MST를 만드는 문제도 아니고 한 정점에서 시작해서 MST를 만들다가 종료점을 만났을때까지 거리도 아님(프림의 알고리즘)
       한 정점에서 시작해서 가능한 간선을 pq, 여기서는 minHeap에 넣고 최소 비용만 뽑아서 다시 간선을 확인하고 pq에 넣는 것을 반복함
       만약 이미 방문한 도시라면 그냥 지나감. pq 상에서 먼저 뽑혀서 해당 도시를 방문했다면 그것은 현재 보다 무조건 최소 비용임.

*느낀점 : pq는 가중치가 있을때 주로 사용하는구나...
        
*/

//history를 위한 점은 1차원이면 충분함. 직전 city index만 필요
int map[MAX+1];
vector<pair<int,int>> edge[MAX+1];

struct info{
    int cityIndex;
    long long costSum;
    int preIndex;
    //min heap을 위한 연산자 오버라이딩
    bool operator<(const info& b)const{
        return costSum>b.costSum;
    }
};

priority_queue<info> pq;
int N,M;
int start,goal;

int main(){
    cin>>N>>M;
    int from,to,cost;
    int totalCost=0;
   
    for(int i=0;i<M;i++){
        scanf("%d %d %d",&from,&to,&cost);
        edge[from].push_back({to,cost});
    }
    cin>>start>>goal;
    //시작점 넣기
    pq.push({start,0,0});
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        int curCity=cur.cityIndex;
        //이미 방문했다면 그냥 진행. pq 특성상 나보다 먼저 도착했다면 그것은 무조건 현재보다 적은 cost로 방문했을것임
        if(map[curCity]) continue;
        //정점을 처음 방문했으면 이때 history update
        map[curCity]=cur.preIndex;
        //bfs와 동일하게 목표에 도달하자마자 끝, 최소값 보장
        if(curCity==goal){
            totalCost=cur.costSum;
            break;
        }
        for(pair<int,int> city:edge[curCity]){
            int nextCity=city.first;
            //이미 방문한 점이라면 pass
            if(!map[nextCity])
                pq.push({nextCity,cur.costSum+city.second,curCity});
        }
    }
    cout<<totalCost<<endl;
    vector<int> res;
    int trackingIndex=goal;
    res.push_back(trackingIndex);
    while(trackingIndex!=start){
        trackingIndex=map[trackingIndex];
        res.push_back(trackingIndex);
    }
    cout<<res.size()<<endl;
    for(int i=res.size()-1;i>=0;i--)
        cout<<res[i]<<" ";
}