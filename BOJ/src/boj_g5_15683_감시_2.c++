#include <iostream>
#include <unordered_set>
#include <vector>
#define MAX 8
#define INF 64
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.02.28

*난이도 : G5
*개인 풀이 시간 : 1.5hour 
*개인 난이도 : 2/5
*분류 : 구현, 시뮬레이션, 삼성문제, dfs, 재귀
*풀이 : 주석 참조

*느낀점 : 너무 어렵게 설계함. 배열 복사에 의한 오버헤드를 줄이기 위해 dp의 개념을 도입해(?) 각 cctv 좌표별 볼 수 있는 좌표를 미리 계산해두고 재사용하려 했으나 
        그 과정의 오버헤드가 배열 복사에 비해 더 컷음.

*/

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

unordered_set<int> watchHash[MAX][4];
vector<pair<int,int>> cctv;
//cctv별 종류를 담은 벡터
vector<int> cctvType;
int map[MAX+1][MAX+1];
int indexMap[MAX+1][MAX+1];
//감시 방향을 표시한 이차원 벡터
vector<vector<int>> cctvMove[]={
    {{}},
    {{0},{1},{2},{3}},
    {{0,1},{2,3}},
    {{0,3},{1,2},{1,3},{0,2}},
    {{0,2,3},{1,2,3},{0,1,3},{0,1,2}}
};

int N,M,minValue,totalIndex;

bool isInside(int x,int y){
    return x>=0&&x<M&&y>=0&&y<N;
}

// cctv 좌표에서 각 방향별로 볼 수 있는 좌표들을 hash에 저장.
//저장할땐 x,y 좌표가 아니라 미리 부여한 인덱스를 넣음
void setHash(){
    int cnt=0;
    for(auto cam:cctv){
        int x=cam.first;
        int y=cam.second;
        for(int dir=0;dir<4;dir++){
            int nx=x+dx[dir];
            int ny=y+dy[dir];
              while(isInside(nx,ny)&&map[ny][nx]!=6){
                if(indexMap[ny][nx]) watchHash[cnt][dir].insert(indexMap[ny][nx]);
                nx+=dx[dir];
                ny+=dy[dir];
            }
        }
        cnt++;
    }
}

//cctv별 방향 정보를 담은 배열
int combi[MAX];
void recul(int index){
    if(index==cctv.size()){
        //cctv별 방향을 모두 정했다면
        int cnt=0;
        //map상에서 내가 테스트해야할 지역의 인덱스를 cctv별 hash 마다 물음
        for(int i=1;i<=totalIndex;i++){
            //만약 cnt가 현재 최소보다 크다면 early stop
            if(cnt>=minValue) return;
            bool isFind=false;
            //cctv 마다 물ㅇ러봄
            for(int j=0;j<index;j++){
                //j는 cctv
                //현재 인덱스에 대해 찾았다면 더 이상 cctv 별로 물어볼 필요가 없음. 앞선 cctv의 감시영역에 포함
                if(isFind||cnt>=minValue) break;
                //cctv별 가능한 방향에 대해서 hash에 물어봄
                for(int dir:cctvMove[cctvType[j]][combi[j]]){
                    //찾으면 이후 cctv에 묻지않고 다음 index 즉 i값을 올림
                    if(watchHash[j][dir].find(i)!=watchHash[j][dir].end()){ 
                        isFind=true;
                        break;
                    }
                }
            }
            if(!isFind) cnt++;
        }
        if(minValue>cnt)minValue=cnt;
        return;
        //기저케이스 끝
    }
    int cctvType=map[cctv[index].second][cctv[index].first];
    for(int i=0;i<cctvMove[cctvType].size();i++){
        combi[index]=i;
        //cctv 방향을 선택하고 다음 인덱스로 넘어감
        recul(index+1);
    }
}

int main(){
    cin>>N>>M;
    minValue=INF;
    vector<pair<int,int>> aroundCctv;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>map[i][j];
            if(map[i][j]==5) aroundCctv.push_back({j,i});
            else if(map[i][j]>=1&&map[i][j]<=4) {
                cctv.push_back({j,i});
                cctvType.push_back(map[i][j]);
            }
        }
    }
    //5번 cctv는 가변적이지 않기 때문에 map에 표현하고 지나감
    for(auto a:aroundCctv){
        int x=a.first;
        int y=a.second;
        for(int dir=0;dir<4;dir++){
            int nx=x+dx[dir];
            int ny=y+dy[dir];
            while(isInside(nx,ny)&&map[ny][nx]!=6){
                if(!map[ny][nx])map[ny][nx]=7;
                nx+=dx[dir];
                ny+=dy[dir];
            }
        }
    }
    //내가 감시해야되는 지역 (전체-(cctv좌표, 벽, 5번에 의한 감시구역))에 대해 인덱스 부여
    //cctv별 각 hashSet에 해당 index가 있으면 cctv의 그 방향에 의해 감시된다는 뜻
      for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
           if(!(map[i][j]>=1&&map[i][j]<=7)) indexMap[i][j]=++totalIndex;
        }
    }
    setHash();
    recul(0);
    cout<<(totalIndex?minValue:0)<<endl;
}