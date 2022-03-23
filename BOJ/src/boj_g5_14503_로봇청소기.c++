#include <iostream>
#include <vector>
#define MAX 50
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.22

*난이도 : G5
*개인 풀이 시간 : 2hour
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬, 삼성문제
*풀이 : 로봇 하나가 실제로 움직이기 때문에 따로 queue나 Stack은 사용하지 않고, 로봇 좌표를 움직임으로써 표현함
*느낀점 : 
       
*/

struct info{
    int x,y,dir;
};
const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
bool map[MAX][MAX];
bool clean[MAX][MAX];
int N,M;
info robot;

int main(){
    cin>>N>>M;
    int a,b,c;
    cin>>a>>b>>c;
    robot={b,a,c};
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++)
            cin>>map[i][j];
    }
    int count=0;
    bool hasEnd=false;
    while(!hasEnd){
        int &x=robot.x;
        int &y=robot.y;
        int &dir=robot.dir;
        //초기 로봇 좌표와 그 다음 이동도 무조건 아직 청소하지 않은 칸으로 이동하기 때문에 바로 Clean을 true로 변경
        clean[y][x]=true;
        count++;
        int cnt=0;
        int ndir;
        //현재 방향에서 왼쪽 방향부터 보기
        for(ndir=(dir+3)%4;cnt<4;ndir=(ndir+3)%4,cnt++){
            int nx=x+dx[ndir];
            int ny=y+dy[ndir];
            if(!map[ny][nx]&&!clean[ny][nx]) break;
            //여기까지 왔다면 4방 모두 이동 불가
            if(cnt==3){
                //cnt++에 대응하기 위해 cnt=-1
                cnt=-1;
                //현재 방향의 반대방향으로 후진
                x+=dx[(dir+2)%4];
                y+=dy[(dir+2)%4];
                //후진 좌표가 벽이면 끝내기
                if(map[y][x]) {
                    hasEnd=true;
                    break;
                }
            }
        }
        //이동 가능한 좌표를 찾았다면 해당 방향으로 이동
        dir=ndir;
        x+=dx[dir];
        y+=dy[dir];
    }
    cout<<count<<endl;
}