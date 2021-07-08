#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#define MAX 50
#define INF 9999999

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.08

*난이도 : G4
*개인 풀이 시간 : 3hr
*개인 난이도 : 3/5
*분류 : BFS
*풀이 : 
    거울이 45도 각도로 놓인다는 조건에서 빛은 수평 수직으로만 움직인다는 것을 도출해낸다.

    BFS 진행간에 거울을 놓을 수 있는 '!'을 만나면 
        1. 거울을 놓지않고 기존 방향으로 진행
        2. 거울을 놓고 기존 진행 방향과 수직인 방향(2방향)으로 진행.
    총 3가지 경우를 queue에 넣었다.

    빛이 한 좌표에 도달할 수 있는 경우가 총 4가지(동서남북)이기 때문에 check 배열을 [row][col][4]으로 선언했다.
    2차원 배열 하나만 사용 해서 풀어보려고 했으나, queue push 조건이 '기존 경로를 단축했을 때만 넣자'일 때 거울을 놓지않고 직진하는 것이 거울을 놓는 경우보다 항상 적기 때문에 알고리즘이 진행되지 않았다.

*느낀점 :
        다음부턴 기능별로 함수를 나눠보자. 예) bfs(), input()
        잔실수를 줄이자.
        최대한 안전하게 코딩하자.
        적절한 전처리나 자료구조 사용은 알고리즘 진행 간에 메모리를 적게 쓰게 해준다. 나무 보다 숲을 보자.
        ([row][col][1] 하나만 사용하려고 했을때 queue의 overflow가 발생함)

*/

struct info{
    int x,y,dir;
};

/*
    1,3 : 동서
    2,4 : 남북
    동남서북
*/

// 허수, 동, 남, 서, 북
const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};

vector<pair<int,int>> door;
queue<info> mirQ;

char map[MAX+2][MAX+2];
int check[MAX+2][MAX+2][5]={0};

int main(){
    int size;
    cin>>size;
    for(int i=0;i<size;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<size;j++){
            map[i][j]=temp[j];
            if(map[i][j]=='#')
                door.push_back(make_pair(j,i));
        }
    }

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            check[i][j][1]=INF;
            check[i][j][2]=INF;
            check[i][j][3]=INF;
            check[i][j][4]=INF;
        }
    }

    int startX=door[0].first;
    int startY=door[0].second;
    map[startY][startX]='*';
    check[startY][startX][1]=check[startY][startX][2]=check[startY][startX][3]=check[startY][startX][4]=0;
    mirQ.push({startX,startY,1});
    mirQ.push({startX,startY,2});
    mirQ.push({startX,startY,3});
    mirQ.push({startX,startY,4});
    
    while(!mirQ.empty()){
        info curInfo=mirQ.front();
        mirQ.pop();

        int curX=curInfo.x;
        int curY=curInfo.y;
        int curDir=curInfo.dir;
        
        int postX=curX;
        int postY=curY;
        while(true){
            postX+=dx[curDir];
            postY+=dy[curDir];
            if(postX>=0&&postY>=0&&postX<size&&postY<size){
                char temp=map[postY][postX];
                if(temp=='*') break;
                else if(temp=='!'){
                    //갱신할때만 큐에 넣자!!
                    if(check[postY][postX][curDir]>check[curY][curX][curDir]){
                        check[postY][postX][curDir]=check[curY][curX][curDir];
                        mirQ.push({postX,postY,curDir});
                    }
                    //짝수 : 세로 이동 -> 가로 이동
                    vector<int> index;
                    if(curDir%2==0){
                        index.push_back(1);
                        index.push_back(3);
                    }
                    else{
                        index.push_back(2);
                        index.push_back(4);
                    }

                    for(int i=0;i<index.size();i++){
                        if(check[postY][postX][index[i]]>check[curY][curX][curDir]+1){
                            check[postY][postX][index[i]]=check[curY][curX][curDir]+1;
                            mirQ.push({postX,postY,index[i]});
                        }
                    }
                }
                else if(temp=='#'){
                    if(check[postY][postX][curDir]>check[curY][curX][curDir]){
                        check[postY][postX][curDir]=check[curY][curX][curDir];
                    }
                    break;
                }
            }
            else break;
        }
    }
    int endX=door[1].first;
    int endY=door[1].second;
    cout<<min({check[endY][endX][1],check[endY][endX][2],check[endY][endX][3],check[endY][endX][4]})<<endl;
    return 0;
}