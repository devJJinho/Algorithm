#include <iostream>
#include <vector>
#define MAX 100
#define ABS(x) ( ((x)<0)?-(x):(x) )
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.18

*난이도 : G3
*개인 풀이 시간 : 2hr 
*개인 난이도 : 3/5 
*분류 : 구현
*풀이 : 경사로는 가로/세로에 대해서 독립적이기 때문에 최대값을 묻긴 했지만 BFS를 사용할 필요는 없었다. 그냥 배열을 한바퀴 돌면 되는 문제.
*느낀점 : 가로/세로에 따라 코드를 구분하는게 아닌 배열을 받을때 세로를 가로로 받고, 가로 알고리즘을 2번 돌렸다.
        풀이를 트리거->체크(1차 거름)->가능한 경사로 중에서 겹치는게 있는지 체크(2차 거름)으로 구현했는데 효율적이었다.
*/

bool isVisited[MAX+1][MAX+1];
int vertical[MAX+1][MAX+1];
int map[MAX+1][MAX+1];
int n,l;
struct info{
    int x,y;
};
bool isInside(info point){
    return point.x>=0&&point.x<n&&point.y>=0&&point.y<n;
}
bool checkLower(info point,bool dir){
    //트리거가 발동된 곳에서 dir 방향에 따라 위로 l개 또는 아래로 l개를 체크한다.
    //경사로를 놓을 수 있으면 true, 아니면 false 반환
    //-> : true , <- : false
    int value=map[point.y][point.x];
    for(int i=1;i<=l;i++){
        if(isInside(point)){
            if(value!=map[point.y][point.x]) return false;
            if(dir)
                point.x++;
            else 
                point.x--;
        }
        else{
            return false;
        }
    }
    return true;
}

int pointCheck(){
    int cnt=0;
    for(int i=0;i<n;i++){
        bool isAble=true;
        //경사로를 놓을 수 있는 곳들의 집합;
        vector<pair<info,bool>> stack;
        for(int j=1;j<n&&isAble;j++){
            info pre={j-1,i};
            if(isInside(pre)){
                if(map[i][j]-1==map[pre.y][pre.x]){
                    //직전이 낮다
                    if(checkLower(pre,false)) stack.push_back(make_pair(pre,false));
                    else{ 
                        isAble=false;
                    }
                }
                else if(map[i][j]==map[pre.y][pre.x]-1){
                    //지금이 낮다
                    info cur={j,i};
                    if(checkLower(cur,true)) stack.push_back(make_pair(cur,true));
                    else{
                        isAble=false;
                    }
                }
                //블럭의 높이차가 1이상일때 => 길 생성 불가능
                else if(ABS(map[i][j]-map[pre.y][pre.x])>1){
                    isAble=false;
                } 
            }
        }
        //아직까지 해당 행이 가능하며 놓을 수 있는 경사로가 있을 경우
        while(!stack.empty()&&isAble){
            info cur=stack.back().first;
            bool dir=stack.back().second;
            stack.pop_back();
            for(int i=1;i<=l;i++){
                if(isVisited[cur.y][cur.x]){
                    //경사로가 중복되면 불가능.
                    isAble=false;
                    break;
                }
                isVisited[cur.y][cur.x]=true;
                if(dir)
                    cur.x++;
                else   
                    cur.x--;
            }
        }     
        //모든걸 통과하면 길 추가
        if(isAble) ++cnt;
    }
return cnt;
}

int main(){
    cin>>n>>l;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int temp;
            cin>>temp;
            map[i][j]=temp;
            vertical[j][i]=temp;
        }
    }
    //가로에 대해서 수행
    int horizen=pointCheck();
    for(int i=0;i<n;i++){
    //visited 초기화 및 가로세로 변환
        for(int j=0;j<n;j++){
            map[i][j]=vertical[i][j];
            isVisited[i][j]=false;
        }
    }
    //세로에 대해서 한번 더 수행.
    int vert=pointCheck();
    cout<<horizen+vert<<endl;
}
