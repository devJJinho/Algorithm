#include <iostream>
#include <queue>
#include <vector>
#define MAX 100
#define INF 10001
#define TIME_INF 1000001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.15
*난이도 : G1
*개인 풀이 시간 : 10hour
*개인 난이도 : 5/5 
*분류 : DP, 다익스트라
*풀이 : 다익스트라와 DP로 최소 시간 탐색.
       
*느낀점 : 

    
*/

struct info{
    int airport,fee,time;
    //연산자 오버라이딩, 부호 방향에 따라 minheap, maxheap이 결정됨
    bool operator<(const info &b)const{
        return time>b.time;
    }
};

vector<info> map[MAX+1];
int dp[MAX+1][INF];

void dijkstra(const int &N,const int &M){
    priority_queue<info> pq;
    //{airport,fee,time}
    pq.push({1,0,0});
    dp[1][0]=0;
    while(!pq.empty()){
        info cur=pq.top();
        pq.pop();
        int curAirport=cur.airport;
        int curTime=cur.time;
        int curFee=cur.fee;
        for(info node:map[curAirport]){
            int nextAirport=node.airport;
            int nextFee=curFee+node.fee;
            int nextTime=curTime+node.time;
            if(nextFee>M) continue;
            if(dp[nextAirport][nextFee]<=nextTime) continue;
            for(int fee=nextFee;fee<=M;fee++){
                if(dp[nextAirport][fee]<=nextTime) break;
                dp[nextAirport][fee]=nextTime;
            }
            pq.push({nextAirport,nextFee,nextTime});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin>>tc;
    while(tc--){
        int n,m,k;
        cin>>n>>m>>k;
        // 초기화
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++)
                dp[i][j]=TIME_INF;
            map[i].clear();
        }
        for(int i=0;i<k;i++){
            int u,v,c,d;
            cin>>u>>v>>c>>d;
            map[u].push_back({v,c,d});
        }
        dijkstra(n,m);
        int minCost=TIME_INF;
        for(int cost=1;cost<=m;cost++)
            if(dp[n][cost]<minCost) minCost=dp[n][cost];
        if(minCost==TIME_INF) cout<<"Poor KCM"<<endl;
        else
            cout<<minCost<<endl;
    }
}

