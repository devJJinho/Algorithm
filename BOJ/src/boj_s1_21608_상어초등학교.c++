#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 400
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.18

*난이도 : s1    
*개인 풀이 시간 : 4hour
*개인 난이도 : 3/5 
*분류 : 구현, 시뮬, 연산자오버라이딩, 정렬
*풀이 : 문제에서 제공하는 규칙은 연산자 오버라이딩에 모두 표현 할 수 있었음
       이것을 일일이 구현하다보니 세세한 곳에서 문제 발생
       앉을 수 있는 가능한 자리를 선택할때 이미 학생이 앉을 자리에 대해 체크하지 않아서 이미 앉은 자리가 계속 선택됨

*느낀점 : 한번 꼬이니까 걷잡을 수 없었음
        설계를 하고 풀어야함

*/

int N;
int prefer[MAX+1][4];
vector<int> stuOrder;
int map[21][21];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

struct info{
    int preferCnt,emptyCnt,y,x;
    //기본 정렬은 오름차순(1->10) 즉 less, 뒤에 오는 것에 비해 내가 작은지에 대해 true가 나오는 방식으로 정렬.
    bool operator<(const info &b)const{
        //문제에서 주어진 rule에 맞춰 연산자 오버라이딩으로 구현
        if(preferCnt!=b.preferCnt) return preferCnt>b.preferCnt;
        if(emptyCnt!=b.emptyCnt) return emptyCnt>b.emptyCnt;
        if(y!=b.y) return y<b.y;
        return x<b.x;
    }
};

void rule1(int stuNum,vector<info> &seats){
    int cntMap[21][21][2];
    int max=0;
    //결국 최대값을 찾기 위해선 한번 탐색해야함.
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(map[i][j])continue;
            int preferCnt=0;
            int emptyCnt=0;
            for(int dir=0;dir<4;dir++){
                int nx=j+dx[dir];
                int ny=i+dy[dir];
                if(nx>=1&&nx<=N&&ny>=1&&ny<=N){
                    for(int t=0;t<4;t++)
                        if(prefer[stuNum][t]==map[ny][nx]) preferCnt++;
                    if(!map[ny][nx]) emptyCnt++;
                }
            }
            //선호하는 학생과 비어있는 공간에 대해 동시에 계산
            if(preferCnt>max) max=preferCnt;
            cntMap[i][j][0]=preferCnt;
            cntMap[i][j][1]=emptyCnt;
        }
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            //@@주요한 코드@@
            //만약 이미 학생이 앉은 곳이라면 pass
            if(map[i][j]) continue;
            //최대값과 같다면 가능한 자리의 집단에 추가
            if(cntMap[i][j][0]==max) seats.push_back({cntMap[i][j][0],cntMap[i][j][1],i,j});
        }
    }
}

int cntHappiness(int x,int y){
    int cnt=0;
    int student=map[y][x];
    for(int dir=0;dir<4;dir++){
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(nx>=1&&nx<=N&&ny>=1&&ny<=N){
            for(int i=0;i<4;i++){
                if(prefer[student][i]==map[ny][nx]) cnt++;
            }
        }
    }
    return cnt;
}
int main(){
    cin>>N;
    for(int i=0;i<N*N;i++){
        int stu,a,b,c,d;
        cin>>stu>>a>>b>>c>>d;
        stuOrder.push_back(stu);
        prefer[stu][0]=a;prefer[stu][1]=b;prefer[stu][2]=c;prefer[stu][3]=d;
    }
    for(int stu:stuOrder){
        vector<info> seats;
        rule1(stu,seats);
        sort(seats.begin(),seats.end());
        map[seats[0].y][seats[0].x]=stu;
    }
    int total=0;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            int res=cntHappiness(j,i);
            switch(res){
                case 0 : break;
                case 1 : break;
                case 2 : res=10; break;
                case 3 : res=100; break;
                case 4 : res=1000; break;
            }
            total+=res;
        }
    }
    cout<<total<<endl;
}