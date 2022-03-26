#include <iostream>
#include <string.h>
#define SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))
#define MAX 50
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.25

*난이도 : G4
*개인 풀이 시간 : 1.5 hour
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬, 삼성문제
*풀이 :
*느낀점 : 공기청정기 바람의 순환이 어려웠음
*/

//북,동,남,서
const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};

int map[MAX+1][MAX+1];
int R,C,T;
int up=-1,down=-1;

bool isInside(int x,int y){
    return x>=0&&x<C&&y>=0&&y<R;
}

bool isPuri(int x,int y){
    return x==0&&(y==up||y==down);
}

void rotate(bool isUp){
    int r,x,y,dir,index,temp,finish;
    if(isUp){
        r=up;
        x=0;
        y=up-1;
        dir=0;
        index=1;
        finish=up;
    }
    else{
        r=R-down-1;
        x=0;
        y=down+1;
        dir=2;
        index=-1;
        finish=down;
    }
    map[up][0]=map[down][0]=0;
    bool isCol=true;
    int cnt=0;
    while(!(x==0&&y==finish)){
        int px=x-dx[dir];
        int py=y-dy[dir];
        SWAP(map[y][x],map[py][px],temp);
        ++cnt;
        if((isCol&&cnt==r)||(!isCol&&cnt==C-1)){
            dir=(dir+index+4)%4;
            cnt=0;
            isCol=!isCol;
        }
        x+=dx[dir];
        y+=dy[dir];
    }
}

void spread(){
    int temp[R][C];
    memset(temp,0,sizeof(temp));
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            //벽이 있거나, 공기청정기가 있는 곳에선 확산 일어나지 않음
            if(!map[i][j]||isPuri(j,i)) continue;
            int p=map[i][j]/5;
            //사방으로 확산
            for(int dir=0;dir<4;dir++){
                int nx=j+dx[dir];
                int ny=i+dy[dir];
                if(!isInside(nx,ny)||isPuri(nx,ny)) continue;
                temp[ny][nx]+=p;
                temp[i][j]-=p;
            }
        }
    }
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++)
            map[i][j]+=temp[i][j];
    }
}

int main(){
    cin>>R>>C>>T;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            scanf("%d",&map[i][j]);
            if(map[i][j]==-1){
                if(up==-1) up=i;
                else down=i;
                map[i][j]=0;
            }
        }
    }
    while(T--){
        spread();
        rotate(false);
        rotate(true);
    }
    int cnt=0;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(!map[i][j]||isPuri(j,i)) continue;
            cnt+=map[i][j];
        }
    }
    cout<<cnt<<endl;
    return 0;
}