#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n,m,p;
int power[10];
int cnt[10];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
bool map[1001][1001];
char mp[1001][1001];
queue<pair<int,int>> castle[10];

/*
@author  :  Jinho Jeong
@date    :  2021.07.30

*난이도 : G2
*개인 풀이 시간 : 5hour 
*개인 난이도 : 4/5 
*분류 : BFS, 구현
*풀이 : 동시에 늘린다=> 전체 범위를 한칸씩 늘린다.

*느낀점 : 문제의 함정과 더불어 제대로 이해를 하지 못한 탓에 풀이에 많은 시간이 걸렸다.
        처음 이해한 문제는 상하좌우 직선으로 Si만큼 움직일 수 있다는 것이다. 그래서 우선순위 큐에 갈 수 있는 칸을 모두 넣고 가까운 순부터 영토를 확장했다.
        하지만 여기서 말하는 확장은 중간에 경로도 꺽어도 좋으니 Si칸 이내의 모든 영토라는 것이다.
        그리고 동시확장의 개념은 한점만 잡고 Si칸 확장해버리면 다른 칸이 확장할때 방해받을 수도 있기 때문에 전체 칸을 한칸씩 Si번 확장하는 것이다.
        그리고 직전 확장에서 확장된 칸에서만 새로이 확장이 이루어지므로 그것만 queue에 보관했다. => 처음에 이 방식을 vector의 치환으로 구현하였으나 시간초과가 일어났다.
        
*/

bool isValid(int x,int y){
    return x>=0&&x<m&&y>=0&&y<n;
}

bool bfs(int x,int y,queue<pair<int,int>> &temp,int cs){
    bool isPushed=false;
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(isValid(nx,ny)&&!map[ny][nx]){
            map[ny][nx]=true;
            isPushed=true;
            temp.push({nx,ny});
            cnt[cs]++;
        }
    }
    return isPushed;
}

void expend(){
    bool isChanged=true;
    while(isChanged){
        isChanged=false;
        for(int cs=1;cs<=p;cs++){
            //아래 코드로 인해 시간이 많이 단축된다.
            if(!castle[cs].size()) continue;
            //영토를 하나씩 늘린다.
            for(int k=1;k<=power[cs];k++){
                //아래 코드로 인해 시간이 많이 단축된다.
                if(!castle[cs].size()) break;
                int size=castle[cs].size();
                for(int i=0;i<size;i++){
                    pair<int,int> cur=castle[cs].front();
                    //현재 지점은 pop한다.
                    //환장한 점만 따로 관리한다. 전체를 보관하지 않는다.
                    //현재 한칸도 못 늘린 경우 다음에 한칸을 늘릴수가 없다.
                    castle[cs].pop();
                    if(bfs(cur.first,cur.second,castle[cs],cs))
                        isChanged=true;
                }
            }
        }
    }
}

int main(){
    cin>>n>>m>>p;
    for(int i=1;i<=p;i++){
        cin>>power[i];
    }
    for(int i=0;i<n;i++)
        cin>>mp[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char temp=mp[i][j];
            if(temp!='.'){
                map[i][j]=true;
                if(temp=='#') continue;
                castle[temp-'0'].push({j,i}); 
                cnt[temp-'0']++;
            }
        }
    }
    expend();
    for(int i=1;i<=p;i++)
        cout<<cnt[i]<<" ";
    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n,m,p;
int power[10];
int cnt[10];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
bool map[1001][1001];
struct info{
    int x,y,k;
    //연산자 오버로딩
    bool operator<(info b)const{
        return this->k>b.k;
    }
};
vector<vector<pair<int,int>>> castle(10);

bool isValid(int x,int y){
    return x>=0&&x<m&&y>=0&&y<n;
}

bool bfs(int x,int y,int k,vector<pair<int,int>> &temp,int cs){
    bool isPushed=false;
    queue<info> que;
    que.push({x,y,0});
    while(!que.empty()){
        info cur=que.front();
        que.pop();
        for(int dir=0;dir<4;dir++){
            int nx=cur.x+dx[dir];
            int ny=cur.y+dy[dir];
            if(isValid(nx,ny)&&!map[ny][nx]){
                map[ny][nx]=true;
                isPushed=true;
                temp.push_back({nx,ny});
                cnt[cs]++;
                if(cur.k!=k) que.push({nx,ny,k+1});
            }
        }
    }
    return isPushed;
}

void expend(){
    bool isChanged=true;
    while(isChanged){
        isChanged=false;
        for(int cs=1;cs<=p;cs++){
            //벡터의 복사 방식은 너무 느리다.
            vector<pair<int,int>> temp;
            for(int k=1;k<=power[cs];k++){
                for(auto cur:castle[cs]){
                    if(bfs(cur.first,cur.second,1,temp,cs)) temp.push_back({cur.first,cur.second});
                }
                castle[cs]=temp;
            }
        }
    }
}

int main(){
    cin>>n>>m>>p;
    for(int i=1;i<=p;i++){
        cin>>power[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char temp;
            cin>>temp;
            if(temp!='.'){
                map[i][j]=true;
                if(temp=='#') continue;
                castle[temp-'0'].push_back({j,i}); 
                cnt[temp-'0']++;
            }
        }
    }
    expend();
    for(int i=1;i<=p;i++){
        cout<<cnt[i]<<" ";
    }
    return 0;
}