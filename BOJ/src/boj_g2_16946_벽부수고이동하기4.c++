#include <iostream>
#include <string>
#include <queue>
#include <vector>
#define MAX 1001
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.18
*난이도 : G2
*개인 풀이 시간 : 3hour
*개인 난이도 : 3/5 
*분류 : Union-Find, 구현
*풀이 : 초기 구현 : 1000*1000 각각에 대해서 BFS 수행함 => 시간복잡도 O(N^2*M^2) 때문에 시간 초과 발생.
       개선 : 1000*1000에 대해서 매번 bfs를 수행할 순 없음. 맵을 한번 훝으면서 연결된 그룹을 찾도록 함.
             (0,0)부터 연결된 곳을 찾도록 함. 한번의 bfs로 방문할 수 있는 그룹이면 같은 index를 부여하고 이의 크기를 1차원 배열 cntList에 저장.
             중복체크는 IndexMap에서 1이상의 index가 있는지로(초기값은 0, isVisited 배열 필요X)
             출력할 땐, 같은 index는 연결되어 있기 때문에 개수에 상관없이 한번만 더해지도록 처리. 4방향에 대해 조사.

*느낀점 : 처음 구현할때 난이도는 쉬웠지만 문제 난이도가 GOLD2라 이렇게 쉬워도 되나?라는 의문이 있었다. 결국 처음 풀이 이후 시간 초과를 얻었고 중복 탐색을 제거하는 코드에 대해서 고민하게 됐다.
        코테 환경에선 난이도가 없기 때문에 문제를 보고 제한 사항을 파악하는 능력이 필요하다.

    
*/


const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

int map[MAX][MAX];
int indexMap[MAX][MAX];
//cntList는 index의 개수만큼 필요 이론상 MAX^2 보다 적은 수가 있음. 때문에 크기를 MAX^2로 잡음
int cntList[1000000];
int n,m;
int index;

bool isInside(int x,int y){
    return x>=0&&x<m&&y>=0&&y<n;
}

void findPath(){
    int index=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            indexMap[i][j]=0;
        }
        cntList[i]=0;
    }
   for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]||indexMap[i][j]) continue;
            //하나의 묶음에 대해서 Index번호를 부여하는 코드
            queue<pair<int,int>> q;
            vector<pair<int,int>> group;
            q.push({j,i});
            indexMap[i][j]=index;
            int cnt=1;
            while(!q.empty()){
                pair<int,int> nowNode=q.front();
                q.pop();
                for(int dir=0;dir<4;dir++){
                    int nextX=nowNode.first+dx[dir];
                    int nextY=nowNode.second+dy[dir];
                    if(!isInside(nextX,nextY)) continue;
                    if(map[nextY][nextX]==0&&!indexMap[nextY][nextX]){
                        q.push({nextX,nextY});
                        indexMap[nextY][nextX]=index;
                        cnt++;
                    }      
                }    
            }
            //해당 index의 크기를 1차원 배열에 입력하는 코드
            cntList[index]=cnt%10;
            index++;
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<m;j++)
            map[i][j]=temp[j]-'0';
    }
    findPath();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]==0){
                cout<<0;
                continue;
            }
            //4방향에 대한 정보 저장
            int value[4]={0,0,0,0};
            int index=0;
            int sum=1;
            for(int dir=0;dir<4;dir++){
                int nx=j+dx[dir];
                int ny=i+dy[dir];
                if(!isInside(nx,ny)) continue;
                bool hasSameValue=false;
                for(int i=0;i<index;i++)
                    if(value[i]==indexMap[ny][nx]) {
                        hasSameValue=true;
                        break;
                    }
                //중보되지 않은 index면 전체합에 추가
                if(!hasSameValue){
                    value[index]=indexMap[ny][nx];
                    sum+=cntList[indexMap[ny][nx]];
                    index++;
                }
            }
            cout<<sum%10;
        }
        cout<<endl;
    }
}


