#include <iostream>
#include <deque>
#include <unordered_set>
#include <string.h>
#define MAX 50
#define DEL -1
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.23

*난이도 : G3
*개인 풀이 시간 : 1.5
*개인 난이도 : 2/5 
*분류 : 구현, 시뮬, 삼성
*풀이 : 원판의 표현은 deque를 사용
       주변부 탐색은 한쌍만 이루어지면 되는지 체크하기 때문에 직전만 체크하도록 함.
*느낀점 : 배수의 포현은 +=x임. *=은 제곱의 표현
*/

deque<int> plates[MAX+1];
int N,M;

void clockWise(int index,int k){
    while(k--){
        int temp=plates[index].back();
        plates[index].pop_back();
        plates[index].push_front(temp);
    }
}

void antiClockWise(int index,int k){
    while(k--){
        int temp=plates[index].front();
        plates[index].pop_front();
        plates[index].push_back(temp);
    }
}

pair<int,int> getSum(){
    int sum=0;
    int cnt=0;
    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++)
            if(plates[i][j]!=DEL) {
                sum+=plates[i][j];
                cnt++;
            }
    }
    return {sum,cnt};
}
void func(int x,int d,int k){
    //회전시키기 배수,
    for(int index=x;index<=N;index+=x){
        if(d) antiClockWise(index,k);
        else clockWise(index,k);
    }
    //삭제 여부 체크를 bool 배열로
    bool hasVisited[N+1][M];
    memset(hasVisited,0,sizeof(hasVisited));
    for(int index=1;index<=N;index++){
        for(int j=0;j<M;j++){
            if(plates[index][j]==DEL) continue;
                int nx=(j-1)%M;
                if(nx<0) nx+=M;
                if(plates[index][nx]==plates[index][j]){
                    hasVisited[index][j]=true;
                    hasVisited[index][nx]=true;
                }
        }
        if(index==1) continue;
        for(int j=0;j<M;j++){
            if(plates[index][j]==DEL) continue;
                int ny=index-1;
                if(plates[ny][j]==plates[index][j]){
                    hasVisited[index][j]=true;
                    hasVisited[ny][j]=true;
            }
        }
    }
    bool hasDeleted=false;
    for(int index=1;index<=N;index++){
        for(int j=0;j<M;j++){
            if(hasVisited[index][j]){
                plates[index][j]=DEL;
                if(!hasDeleted) hasDeleted=true;
            }
        }
    }
    if(!hasDeleted){
        pair<int,int> res=getSum();
        double avg=(double)res.first/(double)res.second;
        for(int i=1;i<=N;i++){
            for(int j=0;j<M;j++){
                if(plates[i][j]==DEL) continue;
                double t=(double)(plates[i][j]);
                if(t>avg) plates[i][j]--;
                if(t<avg) plates[i][j]++;
            }
        }
    }
}

int main(){
    int T;
    cin>>N>>M>>T;
    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++){
            int temp;
            cin>>temp;
            plates[i].push_back(temp);
        }
    }
    for(int i=0;i<T;i++){
        int x,d,k;
        cin>>x>>d>>k;
        func(x,d,k);
    }
    pair<int,int> res=getSum();
    cout<<res.first<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <deque>
#include <unordered_set>
#define MAX 50
#define DEL -1
using namespace std;

deque<int> plates[MAX+1];
int N,M;

void clockWise(int index,int k){
    while(k--){
        int temp=plates[index].back();
        plates[index].pop_back();
        plates[index].push_front(temp);
    }
}

void antiClockWise(int index,int k){
    while(k--){
        int temp=plates[index].front();
        plates[index].pop_front();
        plates[index].push_back(temp);
    }
}

pair<int,int> getSum(){
    int sum=0;
    int cnt=0;
    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++)
            if(plates[i][j]!=DEL) {
                sum+=plates[i][j];
                cnt++;
            }
    }
    return {sum,cnt};
}
void func(int x,int d,int k){
    //회전시키기 배수,
    for(int index=x;index<=N;index+=x){
        if(d) antiClockWise(index,k);
        else clockWise(index,k);
    }
    //삭제 여부 체크를 해쉬셋으로
    unordered_set<int> delSet[MAX+1];
    for(int index=1;index<=N;index++){
        for(int j=0;j<M;j++){
            if(plates[index][j]==DEL) continue;
                int nx=(j-1)%M;
                if(nx<0) nx+=M;
                if(plates[index][nx]==plates[index][j]){
                    delSet[index].insert(j);
                    delSet[index].insert(nx);
                }
        }
        if(index==1) continue;
        for(int j=0;j<M;j++){
            if(plates[index][j]==DEL) continue;
                int ny=index-1;
                if(plates[ny][j]==plates[index][j]){
                delSet[index].insert(j);
                delSet[ny].insert(j);
            }
        }
    }
    bool hasDeleted=false;
    for(int index=1;index<=N;index++){
        for(auto delNum:delSet[index]){
            plates[index][delNum]=DEL;
            if(!hasDeleted) hasDeleted=true;
        }
    }
    if(!hasDeleted){
        pair<int,int> res=getSum();
        double avg=(double)res.first/(double)res.second;
        for(int i=1;i<=N;i++){
            for(int j=0;j<M;j++){
                if(plates[i][j]==DEL) continue;
                double t=(double)(plates[i][j]);
                if(t>avg) plates[i][j]--;
                if(t<avg) plates[i][j]++;
            }
        }
    }
}

int main(){
    int T;
    cin>>N>>M>>T;
    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++){
            int temp;
            cin>>temp;
            plates[i].push_back(temp);
        }
    }
    for(int i=0;i<T;i++){
        int x,d,k;
        cin>>x>>d>>k;
        func(x,d,k);
    }
    pair<int,int> res=getSum();
    cout<<res.first<<endl;
}