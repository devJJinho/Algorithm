#include <iostream>
#include <vector>
#define MAX 100
#define MAP_MAX 40
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.08

*난이도 : G3
*개인 풀이 시간 : 2hr 
*개인 난이도 : 2/5 
*분류 : 구현
*풀이 : 모든 스티커를 90,180,270도 회전시키는 전처리를 한 후 문제를 풀었다.
*느낀점 : 3차원 벡터를 사용해서 데이터를 관리한 것은 좋은 시도였다.
        사실 모든 점에 대해서 매칭 해보고 안되면 회전을 시키기 때문에 스티커를 회전시키는 전처리를 할 필요가 없었다.
        (만약, 한 지점에서 4방향을 모두 시도해보고 다음 지점으로 넘어간다면 전처리를 하는게 효율적이었음)
        그리고 나는 스티커 속의 도형의 좌표만 가지고 풀이했지만 스티커를 map 자체로 유지하는게 구현이 더 수월해보였다.
        도형의 좌표만 가지고 회전을 구현하기 위해선 y축의 길이가 필요했음 => 코드내에서 stickerInfo라는 벡터를 또 선언해야되는 번거로움이 있었다.
*/

struct info{
    int x,y;
};

int row,col,num;

//3차원 벡터 선언
vector<vector<vector<info>>> sticker(MAX+1,vector<vector<info>>(4));
vector<info> stickerInfo(MAX+1);
bool map[MAP_MAX+1][MAP_MAX+1]={false};

info rotate(info a,int yLen){
    int ny=a.x;
    int nx=yLen-a.y-1;
    return {nx,ny};
}

bool isValid(int x,int y){
    return x<col&&y<row&&!map[y][x];
}
void initArray(){
for(int i=0;i<num;i++){
    for(int j=1;j<4;j++){
        //y축의 길이를 찾는다.
        int yLen=(j-1)%2==1?stickerInfo[i].x:stickerInfo[i].y;
        for(info temp:sticker[i][j-1]){
            sticker[i][j].push_back(rotate(temp,yLen));
        }
    } 
}
}

int main(){
    cin>>row>>col>>num;
    for(int k=0;k<num;k++){
        int srow,scol;
        cin>>srow>>scol;
        stickerInfo[k]={scol,srow};
        for(int i=0;i<srow;i++){
            for(int j=0;j<scol;j++){
                int input;
                cin>>input;
                if(input) sticker[k][0].push_back({j,i});
            }
        }
    }
   initArray();
   //스티커
   for(int st=0;st<num;st++){
   bool isDone=false;
   //회전
    for(int dir=0;dir<4;dir++){
        //map의 좌표 (j,i)
       for(int i=0;i<row&&!isDone;i++){
           for(int j=0;j<col&&!isDone;j++){
                   bool valid=true;
                   //매칭 시도
                   for(info temp:sticker[st][dir]){
                       if(!isValid(j+temp.x,i+temp.y)){
                           valid=false;
                           break;
                       }
                   }
                   //가능하면 map에 붙이기
                   if(valid){
                       for(info temp:sticker[st][dir]){
                           map[i+temp.y][j+temp.x]=true;
                       }
                       isDone=true;
                       break;
                   }
               }
           }
       }
   }
    int cnt=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(map[i][j]) cnt++;
        }
    }
    cout<<cnt<<endl;
}
