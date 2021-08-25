#include <iostream>
#include <vector>
#include <set>
#define MAX 50

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.25

*난이도 : G5
*개인 풀이 시간 : 3hour
*개인 난이도 : 2/5 
*분류 : 구현, 자료구조 사용 (Set)
*풀이 : 양동이는 2차원 int배열, 구름은 set으로 표현했다.
*느낀점 : set이 검색에서 유리하기 때문에 set을 사용했다.
        전체 코딩에는 30분이 안걸렸으나 모듈러 연산 디버깅에서 3시간을 헤맸다. 
        c에서 % 나머지 연산은 나누어지는 수의 부호에 따라간다 따라서 결과값에 나누는 수를 더하고 다시 나머지 연산을 해야된다.
        괄호 안에서 분배법칙이 된다는 보장이 없다. ==> 하지만 디버깅 단계에선 다른 로직의 오류인지 단지 모듈러의 오류인지 구분하지 못해서 한참 걸렸다.
        이럴땐 비효율적이라도 확실한 방법으로 수정해서 해 볼 필요가 있다.
*/

int n;
int map[MAX+1][MAX+1];
set<pair<int,int>> cloudArray;

const int dx[]={0,-1,-1,0,1,1,1,0,-1};
const int dy[]={0,0,-1,-1,-1,0,1,1,1};
const int diagonal[]={2,4,6,8};

bool isValid(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=n;
}
void move(int dir,int cnt){
    set<pair<int,int>> newCloud;
    for(auto cloud:cloudArray){
        int* x=&cloud.first;
        int* y=&cloud.second;
        *x=((dx[dir]*cnt)%n+*x-1+n)%n+1;
        *y=((dy[dir]*cnt)%n+*y-1+n)%n+1;
        map[*y][*x]+=1;
        newCloud.insert(cloud);
    }
    for(auto cloud:newCloud){
        int x=cloud.first;
        int y=cloud.second;
        int basketCnt=0;
        for(int i=0;i<4;i++){
            int nx=x+dx[diagonal[i]];
            int ny=y+dy[diagonal[i]];
            if(isValid(nx,ny)&&map[ny][nx]) basketCnt++;
        }
        map[y][x]+=basketCnt;
    }
    cloudArray.clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j]>=2&&newCloud.find({j,i})==newCloud.end()){
                map[i][j]-=2;
                cloudArray.insert({j,i});
            }
        }
    }
}
int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cin>>map[i][j];
    }
    cloudArray.insert({1,n});
    cloudArray.insert({2,n});
    cloudArray.insert({1,n-1});
    cloudArray.insert({2,n-1});

    while(m--){
        int dir,cnt;
        cin>>dir>>cnt;
        move(dir,cnt);
    }
    int waterSum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            waterSum+=map[i][j];
        }
    }
    cout<<waterSum<<endl;
}