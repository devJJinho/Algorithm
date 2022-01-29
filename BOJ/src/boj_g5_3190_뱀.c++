#include <iostream>
#include <queue>
#define MAX 101
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.01.29

*난이도 : G5
*개인 풀이 시간 : 1.5hr
*개인 난이도 : 2/5
*분류 : 시뮬레이션, queue, 구현
*풀이 : 
        Snake 객체를 두고 움직임과 벽 부딪침, 본인과 부딪침에 대해서 check하도록 하고 main 문에서 초당 움직임과 명령어에 따른 움직임을 구현함.

*느낀점 :
        Snake 객체가 어디까지 기능을 해야될지 구분하기가 힘들었음.
        map 관리도 객체로 하면 어떨지?
*/

//동남서북
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};

bool map[MAX][MAX];

class Snake{
    bool loca[MAX][MAX];
    int n;
    queue<pair<int,int>> locaQueue;
    public:
    Snake(int n){
        this->n=n;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                loca[i][j]=false;
        }
    }
    bool goForward(int x,int y){
        if(!isAvailable(x,y)) return false;
        locaQueue.push({x,y});
        loca[y][x]=true;
        return true;
    }
    void withdrawBack(){
        auto back=locaQueue.front();
        locaQueue.pop();
        loca[back.second][back.first]=false;
    }
    bool isAvailable(int x,int y){
        return x>=1&&x<=n&&y>=1&&y<=n&&!loca[y][x];
    }
};

int main(){
    int n,k;
    cin>>n>>k;
    //초와 dir 관리는 밖에서
    for(int i=0;i<k;i++){
        int y,x;
        cin>>y>>x;
        map[y][x]=true;
    }
    int l;
    int dir=0;
    int cnt=0;
    int x=1,y=1;
    Snake snake=Snake(n);
    snake.goForward(x,y);
    cin>>l;
    while(l--){
        int t; char c;
        cin>>t>>c;
        while(cnt<t){
            int nx=x+dx[dir];
            int ny=y+dy[dir];
            cnt++;
            bool isAvailable=snake.goForward(nx,ny);
            if(!isAvailable){
                cout<<cnt<<endl;
                return 0;
            }
            if(!map[ny][nx]){
                snake.withdrawBack();
            }
            else
                map[ny][nx]=false;
            x=nx;
            y=ny;
        }
        if(c=='D') dir=(dir+1)%4;
        else if(c=='L'){
            dir-=1;
            if(dir<0) dir=(dir%4)+4;
        }
    }
    while(true){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        cnt++;
        bool isAvailable=snake.goForward(nx,ny);
        if(!isAvailable) break;
        if(!map[ny][nx])
            snake.withdrawBack();
        x=nx;
        y=ny;
    }
    cout<<cnt<<endl;
    return 0;
}