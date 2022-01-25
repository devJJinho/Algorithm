/*
@author  :  Jinho Jeong
@date    :  2022.01.25

*난이도 : G2
*개인 풀이 시간 : 2hour 
*개인 난이도 : 3/5 
*분류 : Union-Find
*풀이 : 뒤에서 부터 채우는게 가장 효율적인 이유: 
           문제에서 최대한 많은 비행기를 도킹하라고 했음.
           가능한 게이트는 1~최대 게이트, 가능한 최대 게이트 번호는 그 아래보다 다른 비행기와 겹칠 확률이 적거나 같음. 때문에 위에서부터 채움.

*느낀점 : union-find가 어떻게 적용되는지 감을 못잡았으나, 단순히 check만 하고 배열을 타고 내려가는 방법을 구상하다가 비효율적임을 깨닫고 union-find의 사용 이유를 알아냄.
        union-find의 활용에 대해 알게됨
      
*/

// 전체 소팅 후 뒤에서부터 채우는 코드 => 테스트케이스 중 10%만 해결 가능. General한 코드는 아님.

#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 100001
using namespace std;

vector<pair<int,int>> order;
int main(){
    int g,p;
    cin>>g>>p;
    int index=1;
    int errorMin=MAX;
    for(int i=0;i<p;i++){
        int num;
        cin>>num;
        order.push_back({num,index++});
    }
    sort(order.begin(),order.end());
    int gateNum=1;
    for(auto plane:order){
        if(plane.first<gateNum){
            errorMin=min(errorMin,plane.second);
            continue;
        }
        gateNum++;
    }
    cout<<errorMin<<endl;
}

/////////////////////////////////////////////////

//Union-find로 가능한 다음 블럭의 위치를 저장했음.
//Union-find를 통해 메모리 탐색을 최소화 함.

#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 100001
using namespace std;

bool isDocked[MAX];
int parent[MAX];

int findParent(int index){
    if(parent[index]==index)
        return index;
    return parent[index]=findParent(parent[index]);
}

void unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a<b)
        parent[b]=a;
    else   
        parent[a]=b;
}

int main(){
    int g,p;
    cin>>g>>p;
    for(int n=0;n<=g;n++)
        parent[n]=n;
    int cnt=0;
    for(int i=0;i<p;i++){
        int gate;
        cin>>gate;
        int writingIndex=findParent(gate);
        if(writingIndex==0) break;
        cnt++;
        unionParent(writingIndex,writingIndex-1);
    }
    cout<<cnt<<endl;
}
