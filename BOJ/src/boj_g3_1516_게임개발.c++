#include <iostream>
#include <queue>
#include <vector>
#define MAX 500
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.21

*난이도 : G3
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 위상정렬
*풀이 :

*느낀점 :

*/

vector<int> n[MAX+1];
priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> z;
int in[MAX+1];
int weight[MAX+1];
int res[MAX+1];
int N;
int main(){
    cin>>N;
    int t;
    for(int i=1;i<=N;i++){
        cin>>t;
        weight[i]=t;
        int pre;
        cin>>pre;
        while(pre!=-1){
            n[pre].push_back(i);
            in[i]++;
            cin>>pre;
        }
    }
    for(int i=1;i<=N;i++){
        if(in[i]==0) z.push({weight[i],i});
    }
    while(!z.empty()){
        auto cur=z.top();
        z.pop();
        int curT=cur.first;
        int now=cur.second;
        res[now]=curT;
        for(int outNode:n[now]){
            if(--in[outNode]==0) z.push({weight[outNode]+curT,outNode});
        }
    }
    for(int i=1;i<=N;i++)
        cout<<res[i]<<endl;
}