#include <iostream>
#include <unordered_map>
#include <string>
#define MAX 200002
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.10.04

*난이도 : G2
*개인 풀이 시간 : 2hour 
*개인 난이도 : 2/5 
*분류 : indexing, hash, union-find
*풀이 : 문자열에 대한 union-find이기 때문에 문자열 마다 숫자 index를 부여하고 union-find를 진행했다. => index 관리는 hash(unordered_map)을 사용함.
       집단에 속한 수를 물었기 때문에 union-find 할 때 size도 최신화 했다.
*느낀점 : 
       size를 따로 유지하지 않고 마지막에 전체 범위에 대해, findParent()를 진행하고 부모가 같은 경우 cnt를 셋다 => 시간초과
       union-find로 부모를 합칠때 각자의 size를 합치는 방향으로 했다.
*/

int parent[MAX];
int num[MAX];
int findParent(int par){
    if(parent[par]==par) return par;
    return parent[par]=findParent(parent[par]);
}

int unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a==b) return a;
    if(a>b) {
        parent[a]=b;
        //각자의 크기도 합친다.
        num[b]+=num[a];
        return b;
    }
    else {
        parent[b]=a;
        num[a]+=num[b];
        return a;
    }
    //합친 부모를 return 한다.
}

int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
    int cs;
    cin>>cs;
    while(cs--){
        int n;
        cin>>n;
        //초기화
        for(int i=0;i<2*n;i++){
            //union-find를 위한 초기화
            parent[i]=i;
            // num[b]+=num[a]이기 때문에 모두 하나씩 존재한다.
            num[i]=1;
        }
        //Unordered_map의 사용이 map 사용보다 빨랐다. 300ms => 150ms
        unordered_map<string,int> index;
        int cnt=0;
        for(int i=0;i<n;i++){
            string a,b;
            cin>>a>>b;
            auto aIndex=index.find(a);
            auto bIndex=index.find(b);
            //처음 들어온 문자열의 경우 index에 insert한다.
            if(aIndex==index.end()){
                index.insert({a,cnt++});
                aIndex=index.find(a);
            }
            if(bIndex==index.end()){
                index.insert({b,cnt++});
                bIndex=index.find(b);
            }
            //return받은 부모를 가지고 그 부모의 사이즈를 출력한다.
            int res=unionParent(aIndex->second,bIndex->second);
            cout<<num[res]<<'\n';
        }
    }
}