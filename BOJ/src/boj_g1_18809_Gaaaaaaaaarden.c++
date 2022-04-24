#include <iostream>
#include <vector>
#include <queue>
#define MAX 50
#define RED 3
#define GREEN 4
#define BLOOM 5
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.04.13

*난이도 : G1
*개인 풀이 시간 : 1.5hour
*개인 난이도 : 2/5 
*분류 : 브루트포스 , 구현 , 시뮬 , 조합
*풀이 : 
*느낀점 : 
       
*/

struct INFO{
    int x,y,color;
};

int N,M,G,R;
int map[MAX][MAX];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
vector<INFO> red;
vector<INFO> green;
int maxValue;
void recul(int x, int y,int rCnt, int gCnt){
    if(rCnt == R && gCnt == G){
        //{color, depth}
        pair<int,int> visited[N][M];
        queue<INFO> que;
        //통합 que에 넣고 visited 처리함
        for(auto r: red){
            que.push(r);
            visited[r.y][r.x]={RED,0};
        }
        for(auto g: green){
            que.push(g);
            visited[g.y][g.x]={GREEN,0};
        }
        int depth = 0;
        int fCnt = 0;
        while(!que.empty()){
            ++depth;
            int size = que.size();
            for(int i = 0 ; i < size ; i++){
                auto cur = que.front();
                que.pop();
                //만약 내가 이미 que에 들어오고 이후에 퍼진 용액 때문에 꽃이 폈다면 이미 큐에 들어간 용액은 번지지 않아야함
                //이를 위해 내 자리가 꽃 폈으면 바로 continue;
                if(visited[cur.y][cur.x].first == BLOOM) continue;
                for(int dir = 0 ; dir < 4 ; dir++){
                    int nx = cur.x + dx[dir];
                    int ny = cur.y + dy[dir];
                    if(nx >= 0 && nx < M && ny >= 0 && ny < N){
                        pair<int,int>& v = visited[ny][nx];
                        if(map[ny][nx] == 0 || v.first == BLOOM || (v.second < depth && v.first != 0)) continue;
                        //같은 depth로 visited 방문하면 동시에 방문한 꼴, 이땐 색상만 비교하면 됨
                        if(v.second == depth){
                            if(v.first != cur.color){
                                v.first = BLOOM;
                                fCnt++;
                            }
                            //해당 continue 구문이 없어서 오답처리
                            //만약 depth가 같은 경우에서 색이 서로 다른 경우만 꽃이 피는 처리를 하면 끝이었는데
                            //같은 Depth에서 색이 같은 경우 꽃피지도 않고 continue도 없어서 아래의 que.push가 다시 수행됐음 -> 시간 초과 발생
                            continue;
                        }
                        que.push({nx,ny,cur.color});
                        visited[ny][nx] = {cur.color,depth};
                    }
                }
            }
        }
        if(fCnt > maxValue) maxValue = fCnt;
        return;
    }
    for(int i = y ; i < N ; i++, x=0){
        for(int  j = x ; j < M ; j++){
            if(map[i][j] != 2) continue;
            if(gCnt < G){
                //용액을 놓을 수 있는 자리에 대해서 조합 생성
	            green.push_back({j,i, GREEN});
	            recul(j+1, i, rCnt, gCnt+1);
	            green.pop_back();
            }
            if(rCnt < R){
	            red.push_back({j,i, RED});
	            recul(j+1, i, rCnt+1, gCnt);
	            red.pop_back();
        	}
        }
    }
}
int main(){
    cin>>N>>M>>G>>R;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++){
            scanf("%d",&map[i][j]);
        }
    }
    recul(0,0,0,0);
    cout<<maxValue<<endl;
}