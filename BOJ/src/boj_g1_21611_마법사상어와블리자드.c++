#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#define MAX 50
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.16

*난이도 : G1
*개인 풀이 시간 : 7+@hour
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬레이션, 자료구조
*풀이 : 선입선출의 자료구조가 필요했으나 queue의 경우 랜덤 접근이 어렵기 때문에 선입선출이 되는 deque를 사용함
       
*느낀점 : 
       조건 중에서 '맵을 벗어나는 항은 무시한다'는 것을 구현하지 않아 디버깅에 많은 시간이 소요됨
*/


int map[MAX][MAX];
int indexMap[MAX][MAX];

const int spiralX[4]={-1,0,1,0};
const int spiralY[4]={0,1,0,-1};
const int dx[]={0,0,0,-1,1};
const int dy[]={0,-1,1,0,0};
vector<pair<int,int>> inst;
int n,m;

class Maze{
    int n;
    pair<int,int> dragon;
    deque<int> ball;
    const int delFlag=-1;
    int expCnt[4]={0,0,0,0};
    //마킹 해놓은 구슬을 삭제
    void trimBall(){
        int size=ball.size();
        for(int i=0;i<size;i++){
            int temp=ball.front();
            ball.pop_front();
            if(temp!=delFlag) ball.push_back(temp);
        }
    }
    public:
        Maze(int n,deque<int> &ball){
            this->n=n;
            //vector에서 =연산은 대입 연산. 기존것을 삭제하고 우측것을 모두 복사하여 동일하게 만듦
            this->ball=ball;
        }
        void delBall(vector<int> &ls,bool isAdd){
            for(int index:ls){
                if(index>ball.size()) break;
                if(isAdd) expCnt[ball[index]]++;
                ball[index]=delFlag;
            }
            trimBall();
        }
        bool findSerial(){
            if(!ball.size()) return false;
            vector<int> res;
            int pre=ball[0];
            int cnt=1;
            int i;
            for(i=1;i<ball.size();i++){
                if(ball[i]==pre){
                    cnt++;
                    continue;
                }
                if(cnt>=4){
                    for(int j=i-1;j>i-1-cnt;j--)
                        res.push_back(j);
                }
                pre=ball[i];
                cnt=1;
            }
            //종료 이후에 남은 것에 대한 처리
            if(cnt>=4)
                for(int j=i-1;j>i-1-cnt;j--)
                    res.push_back(j);
            if(!res.size()) return false;
            delBall(res,true);
            return true;
        }
        void renewalBall(){
            if(!ball.size()) return;
            int pre=ball.front();
            ball.pop_front();
            int cnt=1;
            int renewedSize=0;
            int size=ball.size();
            for(int i=0;i<size;i++){
                int temp=ball.front();
                ball.pop_front();
                if(temp==pre) {
                    cnt++;
                    continue;
                }
                //n^2-1개 초과하는 항이 들어오면 pop만 진행하고 추가는 하지 않음
                if(++renewedSize<n*n) ball.push_back(cnt);
                if(++renewedSize<n*n) ball.push_back(pre);
                pre=temp;
                cnt=1;
            }
            if(++renewedSize>=n*n) return;
            ball.push_back(cnt);
            if(++renewedSize>=n*n) return;
            ball.push_back(pre);
        }
        int getValue(){
            return expCnt[1]+2*expCnt[2]+3*expCnt[3];
        }
};

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>map[i][j];
        }
    }
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        inst.push_back({a,b});
    }
    int dist=0;
    int dir=3;
    int cnt=0;
    int x,y;
    x=y=n/2;
    deque<int> ball;
    while(cnt<n*n){
        dir=(dir+1)%4;
        if(dir==0||dir==2)++dist;
        for(int i=0;i<dist;i++){
            x+=spiralX[dir];
            y+=spiralY[dir];
            indexMap[y][x]=cnt++;
            if(map[y][x])
                ball.push_back({map[y][x]});
        }
    }
    Maze maze(n,ball);
    for(auto attack:inst){
        vector<int> res;
        int nx,ny;
        nx=ny=n/2;
        for(int i=0;i<attack.second;i++){
            nx+=dx[attack.first];
            ny+=dy[attack.first];
            res.push_back(indexMap[ny][nx]);
        }
        maze.delBall(res,false);
        bool isChanged=maze.findSerial();
        while(isChanged){
            isChanged=maze.findSerial();
        }
        maze.renewalBall();
    }
    cout<<maze.getValue()<<endl;
}

////////////////////////////////////////////////////////
//실패한 이전 풀이 -> 구슬의 벡터가 0일때, 맵을 재편할때 개수 한계등을 구현하지 않은 듯 함.
////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 50
using namespace std;
// -> ^ <- v
const int dx[]={1,0,-1,0};
const int dy[]={0,-1,0,1};
const int convDir[]={0,1,3,2,0};

int n;
int map[MAX+1][MAX+1];
int index[MAX+1][MAX+1];
vector<int> list;

bool isValid(int x,int y){
    return x>=0&&x<n&&y>=0&&y<n;
}

void initIndex(){
    int cnt=0;
    int curX=(n-1)/2;
    int curY=(n-1)/2;
    index[curY][--curX]=cnt++;
    list.push_back(map[curY][curX]);
    index[++curY][curX]=cnt++;
    list.push_back(map[curY][curX]);
    int dir=0;
    int len=3;
    while(true){
        for(int j=0;j<2;j++){
            for(int i=0;i<len-1;i++){
                curX+=dx[dir];
                curY+=dy[dir];
                if(!isValid(curX,curY)) return;
                index[curY][curX]=cnt++;
                list.push_back(map[curY][curX]);
            }
            dir=(dir+1)%4;
        }
        ++len;
    }
}

int delNode(vector<int> &delList){
    int sum=0;
    for(auto i:delList){
        sum+=list[i];
        list[i]=-1;
    }
    while(true){
        auto iter=find(list.begin(),list.end(),-1);
        if(iter==list.end()) break;
        list.erase(iter);
    }
    return sum;
}
void resetArray(int size){
    int index=0;
    int start=0;
    int cnt=1;
    int value=list[start];
    vector<int> tempList(size,0);
    list.push_back(4);
    while(int tIndex=0<size&&index<list.size()-1){
        if(list[++index]==value)
            cnt++;
        else{
            tempList[tIndex++]=cnt;
            tempList[tIndex++]=value;
            value=list[index];
            start=index;
            cnt=1;
        }
    }
    list=tempList;
}
int findSerial(){
    int index=0;
    int start=0;
    int cnt=1;
    int value=list[start];
    vector<int> delList;
    list.push_back(4);
    while(index<list.size()-1){
        if(list[++index]==value)
            cnt++;
        else{
            if(cnt>=4){
                for(int i=start;i<start+cnt;i++)
                    delList.push_back(i);
            }
            cnt=1;
            start=index;
            value=list[start];
        }
    }
    list.pop_back();
    return delNode(delList);
}
int main(){
    int m;
    cin>>n>>m;
    int size=n*n-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cin>>map[i][j];
    }
    initIndex();
    int res=0;
    while(m--){
        int d,s;
        cin>>d>>s;
        int cx,cy;
        cx=cy=(n-1)/2;
        vector<int> delList;
        for(int i=0;i<s;i++){
            cx+=dx[convDir[d]];
            cy+=dy[convDir[d]];
            if(list[index[cy][cx]]!=0)
                delList.push_back(index[cy][cx]);
            else break;
        }
        delNode(delList);
        int score=findSerial();
        while(score){
            res+=score;
            score=findSerial();
        }
        resetArray(size);
    }
    cout<<res<<endl;
}