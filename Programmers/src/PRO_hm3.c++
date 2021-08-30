#include <iostream>
#include <vector>
#include <queue>
#define INF 2000000000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.29

*난이도 : 2/5
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 (Level 5 치고는 쉬운편) 
*분류 : DFS, 재귀+백트래킹 혹은 BFS
*풀이 : BFS가 가장 낮은 depth에서 답이 나올듯 하지만, 배열의 길이가 너무 길다. 매순간 상태를 저장하며 진행하기에 메모리 소모가 큼.
       때문에 재귀로 구현했다. 가장 최소값을 찾는 문제기 때문에 현재 최소 depth 보다 depth가 길어지는 경우에는 더 이상 진행하지 않았음 => 백트래킹

*느낀점 : 최악의 경우에 대한 테스트를 하지 않아서 이게 정답일거란 보장은 없다.

*/

void find_least(vector<int> &a,int *minDepth,int depth){
    int sum=a[0];
    for(int i=1;i<a.size();i++){
        sum=sum&a[i];
        if(sum==0){
            (*minDepth)=min((*minDepth),depth);
            return;
        }
    }
    if(depth==(*minDepth)) return;
    
    for(int i=0;i<a.size();i++){
        --a[i];
        find_least(a,minDepth,depth+1);
        ++a[i];
    }
}

int main(){
     vector<int> b={3,2,1,2};
    vector<int> m={2,2};
    int index=0;
    vector<int> res;
    for(int i=0;i<m.size();i++){
        int threshold=index+m[i];
        int min=INF;
        vector<int> a;
        int minDepth=min;
        for(;index<threshold;index++){
            a.push_back(b[index]);
            if(b[index]<min) min=b[index];
        }
        find_least(a,&minDepth,0);
        res.push_back(minDepth);
    }
    for(auto a:res)
    cout<<a<<endl;
    return 0;
}