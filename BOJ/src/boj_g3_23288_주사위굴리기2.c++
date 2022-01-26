#include <iostream>
#include <queue>
#include <vector>
#define MAX 20
#define INF 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.26

*난이도 : G3
*개인 풀이 시간 : 2.5hr 
*개인 난이도 : 2/5 
*분류 : 구현,BFS
*풀이 : 주사위를 관리하는 객체를 만들어서 관리함.
       주사위가 x로 굴러갈때 참조하는 배열과 주사위가 y방향으로 굴러갈때 참조하는 배열을 따로 두고 하나가 변경되면 다른 쪽의 특정 위치(주사위의 아래와 윗면)에 업데이트 방향으로 설계
*느낀점 : 수도 코드를 설계하며 하니 일어날 수 있는 변수에 대응하기 편했음.
        주사위를 전역에 두고 함수로 관리하는 것 보다 객체로 관리해서 편했음. 하지만 좋은 방법이었는지는 고민이 필요해보임.
*/

//동남서북
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int map[MAX+1][MAX+1];
int indexMap[MAX+1][MAX+1];
int indexCnt[401];
int n,m,k;

class Dice{
    vector<int> dice_x={6,3,1,4};
    vector<int> dice_y={6,5,1,2};
    int xBaseIndex=0;
    int yBaseIndex=0;
public:
    int calIndex(int index,bool dir){
        //방향에 따라서 기준점을 바꿈
        int n=dir?1:-1;
        index=(index+n)%4;
        if(index<0) index+=4;
        return index;
    }
    void moveX(bool dir){
        xBaseIndex=calIndex(xBaseIndex,dir);
        //x가 바뀌면 y에 업데이트
        //주사위의 위, 아래 면을 공유하기 때문
        dice_y[yBaseIndex]=dice_x[xBaseIndex];
        dice_y[(yBaseIndex+2)%4]=dice_x[(xBaseIndex+2)%4];
    }
    void moveY(bool dir){
        yBaseIndex=calIndex(yBaseIndex,dir);
        dice_x[xBaseIndex]=dice_y[yBaseIndex];
        dice_x[(xBaseIndex+2)%4]=dice_y[(yBaseIndex+2)%4];
    }
    int getBottom(){
        //dice_x[xBaseIndex]로 해도 무방
        return dice_y[yBaseIndex];
    }
};

bool isInside(int x,int y){
    return x>0&&x<=m&&y>0&&y<=n;
}
void calCnt(){
    //index 값 부여하기 전엔 INF, INF값은 나올 수 없는 값.
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++)
            indexMap[i][j]=INF;
    }
    int index=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //indexMap!=INF이면 이미 수정됐음 .방문 할 필요 없음.
            if(indexMap[i][j]!=INF) continue;
            queue<pair<int,int>> q;
            int cnt=0;
            q.push({j,i});
            indexMap[i][j]=index;
            while(!q.empty()){
                auto cur=q.front();
                q.pop();
                int x=cur.first;
                int y=cur.second;
                ++cnt;
                //4방향 체크
                for(int dir=0;dir<4;dir++){
                    int nx=x+dx[dir];
                    int ny=y+dy[dir];
                    if(indexMap[ny][nx]!=INF) continue;
                    if(isInside(nx,ny)&&map[ny][nx]==map[y][x]){
                        q.push({nx,ny});
                        //갈 수 있고 같은 값이면 같은 인덱스 부여
                        //BFS이기 때문에 발견하자마자 바로 업데이트 해줌. 이게 isVisited 역할도 하기 때문
                        indexMap[ny][nx]=index;
                    }
                }
            }
            //카운트 한 값을 저장
            indexCnt[index]=cnt;
            index++;
        }
    }
}
//dice 움직이기
int moveDice(){
    int total=0;
    int x=1;
    int y=1;
    int dir=0;
    //주사위 객체 생성
    Dice dice;
    //횡 움직임인지?
    //종 움직임인지?
    while(k--){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        //문제에서 이동 방향으로 이동이 불가한 경우 반대 방향으로 움직이라고 함.
        //동남서북 방향이기 때문에 반대 방향은 +2)%4임
        if(!isInside(nx,ny)){
            dir=(dir+2)%4;
            nx=x+dx[dir];
            ny=y+dy[dir];
        }
        //주사위의 x와 y가 증가하는 방향이 주사위 객체의 index+1 이기 때문에 해당 방향인지 묻는 코드 삽입
        if(dir%2==0)
            dice.moveX(dir==0);
        else
            dice.moveY(dir==1);
        int bottom=dice.getBottom();
        total+=map[ny][nx]*indexCnt[indexMap[ny][nx]];
        if(bottom>map[ny][nx])
            dir=(dir+1)%4;
        else if(bottom<map[ny][nx]){
            dir-=1;
            if(dir<0) dir+=4;
        }
        x=nx;
        y=ny;
    }
    return total;
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int temp;
            cin>>map[i][j];
        }
    }
    //map을 n*m번 순회하며 reference 생성
    //이 과정이 없으면 최대 1000번의 경우에서 매번 BFS,DFS를 수행해야함.
    //같은 과정은 union-find로 수행해도 됨.
    calCnt();
    int res=moveDice();
    cout<<res<<endl;
}