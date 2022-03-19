#include <iostream>
#include <vector>
#include <string.h>
#define MAX 100
using namespace std;

vector<int> robots;
int weight[MAX+1];
int N,K;
int main(){
    cin>>N>>K;
    int pos=-1;
    int zCnt=0;
    for(int i=0;i<N;i++){
        cin>>weight[i];
        if(!weight[i]) zCnt++;
    }
    int cnt;
    for(cnt=1;zCnt<K;cnt++){
        pos=(pos+1)%N;
        bool hasRobot[N];
        memset(hasRobot,0,sizeof(hasRobot));
        for(int index : robots){
            int nIndex=(index+pos)%N;
            hasRobot[nIndex]=true;
        }
        bool isPos=false;
        for(int index : robots){
            int nIndex=(index+pos+1)%N;
            if(weight[nIndex]&&!hasRobot[nIndex]){
                hasRobot[(index+pos)%N]=false;
                hasRobot[nIndex]=true;
                if(--weight[nIndex]==0) {
                    zCnt++;
                    if(nIndex==pos) isPos=true;
                }
            }
        }
        if(weight[pos]) robots.push_back(pos);
        else if(!weight[pos]&&!isPos) zCnt=0;
    }
}
