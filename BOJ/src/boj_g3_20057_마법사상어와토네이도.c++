#include <iostream>
#include <vector>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.18

*난이도 : G3
*개인 풀이 시간 : 55/60 hour 
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬, 삼성문제
*풀이 : 방사형의 배열을 회전시킨다는게 쉽지 않아보여서 진행 방향을 기준으로 어떻게 움직여야할지 알려주는 구조체로 방향을 잡음
*느낀점 : 
*/

const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};

struct DIR{
    int dIndex,cnt;
    double per;
};

vector<vector<DIR>> lookup={
    {{1,1,0.01},{-1,1,0.01}}, //진행 방향으로 0번
    {{1,1,0.07},{1,2,0.02},{-1,1,0.07},{-1,2,0.02}}, //진행 방향으로 1번 이동 후
    {{1,1,0.1},{-1,1,0.1}},
    {{1,0,0.05}}
};
int N;
int map[MAX][MAX];
int sandSum;

bool isInside(int x,int y){
    return x>=0&&x<N&&y>=0&&y<N;
};
void spread(int x,int y,int dir){
    int &total=map[y+dy[dir]][x+dx[dir]];
    int cTotal=map[y+dy[dir]][x+dx[dir]]; //여기서 복사해놓지 않으면 매 연산에서 total이 줄어들기 때문에 이후의 퍼센트 계산이 정확하지 않게됨.
    for(int cnt=0;cnt<4;cnt++){
        int nx=x+dx[dir]*cnt; //진행방향으로 cnt만큼 이동
        int ny=y+dy[dir]*cnt;
        vector<DIR> &dirArray=lookup[cnt];
        for(DIR cur:dirArray){
            //vector을 참고해서 현재 진행 방향 기준 90도씩 꺾고 또 cnt만큼 해당 방향으로 이동
            int nnx=nx+dx[(dir+cur.dIndex+4)%4]*cur.cnt;
            int nny=ny+dy[(dir+cur.dIndex+4)%4]*cur.cnt;
            //해당 방향의 퍼센트 만큼의 모래 계산
            int nSand=cTotal*cur.per;
            //다음 칸이 내부면 거기로 이동, 외부면 전역에 덧셈
            if(isInside(nnx,nny)) map[nny][nnx]+=nSand;
            else sandSum+=nSand;
            //현재 위치에서 감소
            total-=nSand;
        }
    }
    //알파를 처리하기 위한 코드
    //현재 위치에서 진행 방향으로 두 칸 뒤로 옮겨야함. 해당 칸이 내부면 거기로 이동하기
    //내부가 아니라면 외부에 더하기
    if(isInside(x+dx[dir]*2,y+dy[dir]*2))
        map[y+dy[dir]*2][x+dx[dir]*2]+=total;
    else sandSum+=total;
    //남은 양이 전부 이동했기 때문에 원래 위치에선 모두 비우기
    total=0;
}
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            scanf("%d",&map[i][j]);
    }
    int x=N/2;
    int y=N/2;
    int dir=0;
    int gap=0;
    int cnt=N*N;
    while(cnt){
        //수평 방향으로 이동할 때 움직임이 증가함.
        //즉 시작하자마자 gap은 0에서 1이 되면서 움직임
        if(dir%2==0) ++gap;
        for(int j=0;j<gap;j++){
            int nx=x+dx[dir];
            int ny=y+dy[dir];
            //현재 위치 기준으로 다음칸에 모래가 있으면
            if(map[ny][nx]) {
                spread(x,y,dir);
            }
            //모래 움직인 후 이동
            x=nx;
            y=ny;
            if(--cnt==0) break;
        }
        //Gap만큼 움직이고 방향 전환
        dir=(dir+1)%4;
    }
    cout<<sandSum<<endl;
}