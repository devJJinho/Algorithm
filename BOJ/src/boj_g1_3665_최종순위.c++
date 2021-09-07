#include <iostream>
#include <queue>
#define SWAP(a,b,c) c=a;a=b;b=c;
#define MAX 500

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.05

*난이도 : G1
*개인 풀이 시간 : 5hour 
*개인 난이도 : 3/5 
*분류 : 위상정렬, 진입차수 유지
*풀이 : 프로그래머스에서 순위는 플로이드 와샬로 풀었다. 그 이유는 승리의 관계가 주어지고 문제에서 묻는게 순위를 정할 수 있는 사람(승의 관계로 끝에서 끝에서 파악이 될때)
       하지만 여기선 위상정렬로 풀이한 이유는, 초기 순위를 알려주고, 뒤에 알려주는 것이 선행 관계만을 알려준다. 둘 사이 승리관계라고 단정짓기가 힘들다. 3등과 7등이 바뀌었다고 7등이 3등이 되는 것이 아니다. 
       마지막 관계에서 선행 후행 관계만 그러하다는 것이다. 
       때문에 선행 관계를 유지하면서 모든 n을 정렬할 수 있는지 묻는 것이다.
       위상 정렬은 queue을 사용해서 풀었다. 진입차수가 0인 것을 큐에 넣고, 큐에서 팝한 노드에서 뻗어나가는 간선을 제거하고 다시 진입차수가 0인 노드를 찾아서 큐에 넣는 것을 반복한다.
       만약 queue의 사이즈가 2를 넘어가면 진입점이 여러개이기 때문에 정렬의 결과가 유일하지 않다.
       만약 queue가 비워질때까지 돌고 난 뒤에서 삭제된 간선의 수가 n보다 적다면 그것은 내부에 cycle이 있기 때문이다. => 위상 정렬 불가

       하지만 위상 정렬 없이 해당 문제는 풀이가 가능하다
       초기 순위 5-4-3-2-1을 기준으로 2차원 배열을 만들었기 때문에 선행 후행 관계를 수정하고 다시 2차원 배열에서 순위를 뽑아낸다.
       이 과정은 swap을 통해 구현한다.
       for(int i=0; i<n; i++){
		    for(int j=i+1; j<n; j++){
			    if(g[v[j]][v[i]]) swap(v[i], v[j]); //순위의 첫번째부터 다시 정렬한다. 
		    }
	    }

*느낀점 : 위상정렬에 대해서 알 수 있는 기회였다. 그래프에 대해 더 많은 공부가 필요하다.

*/

int topology(bool map[][MAX+1],int n,vector<int> &res){
    queue<int> q;
    vector<int> indegree(n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j]) indegree[j]++;
        }
    }
    for(int i=1;i<=n;i++)
        if(!indegree[i]) q.push(i);
    while(!q.empty()){
        if(q.size()>1){
            return -1; // ? 
        }
        int cur=q.front();
        res.push_back(cur);
        q.pop();
        for(int i=1;i<=n;i++){
            if(map[cur][i]){
                indegree[i]--;
                map[cur][i]=false;
            }
        }
        for(int i=1;i<=n;i++)
            if(!indegree[i]) q.push(i);
    }
    if(res.size()<n)
        return 0; // impossible
    else 
        return 1;
}

int main(){
    int cs;
    cin>>cs;
    while(cs--){
        bool map[MAX+1][MAX+1]={false};
        int ranking[MAX+1];
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>ranking[i];
        }
        for(int i=1;i<n;i++){
            for(int j=i;j<n;j++)
                map[ranking[i]][ranking[j+1]]=true;
        }
        int num;
        cin>>num;
        bool isPossible=true;
        for(int i=0;i<num;i++){
            int a,b;
            cin>>a>>b;
            int temp;
            SWAP(map[a][b],map[b][a],temp);
        }
        vector<int> res;
        switch(topology(map,n,res)){
            case -1: cout<<"?"<<endl; break;
            case 0: cout<<"IMPOSSIBLE"<<endl; break;
            case 1: 
                for(auto a:res)
                    cout<<a<<" ";
                cout<<endl;
        }
    }
}

//////////////////
//Reference Code//

/*
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int g[555][555];

void solve(){
	memset(g, 0, sizeof g);
	int n; cin >> n; v.resize(n);
	for(auto &i : v) cin >> i;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			g[v[i]][v[j]] = 1;
		}
	}
	int m; cin >> m;
	while(m--){
		int a, b; cin >> a >> b;
		swap(g[a][b], g[b][a]);
	}

	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(g[v[j]][v[i]]) swap(v[i], v[j]);
		}
	}

	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(g[v[j]][v[i]]){
				cout << "IMPOSSIBLE\n"; return;
			}
		}
	}
	for(auto i : v) cout << i << " "; cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}
*/
