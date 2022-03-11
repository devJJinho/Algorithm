#include <iostream>
#include <queue>
#include <algorithm>
#define BAG_MAX 300000

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.11

*난이도 : G2
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 이분탐색, 그리디, min-heap, union-find
*풀이 : 위상정렬으로 하되, 진입차수가 0인 것이 많으면 그땐 주어진 규칙에 맞춰 선택함.
       
*느낀점 : 
       위상정렬을 알면 쉬운 문제였음.
*/

int bag[BAG_MAX+1];
int parent[BAG_MAX+1];
priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> pq;
int N,K;

int findParent(int n){
    if(parent[n]==n) return n;
    return parent[n]=findParent(parent[n]);
}

void unionParent(int a,int b){
    a=findParent(a);
    b=findParent(b);
    if(a==b) return;
    //더 큰 인덱스로 합치기 => 딱 맞는 가방이 없으면 더 큰 가방이라도 써야하기 때문
    if(a>b) parent[b]=a;
    else parent[a]=b;
}

int binarySearch(int capa){
    int bottom=0;
    int ceiling=K-1;
    int res=K;
    while(bottom<=ceiling){
        int middle=(bottom+ceiling)/2;
        //무조건 보석이 가방에 들어가야하기 때문에 가방의 크기는 보석과 같거나 큼
        if(bag[middle]>=capa){
            res=middle;
            //res가 담기는 쪽에서 ceiling을 middle-1로 줄임
            //그래서 같은 무게의 가방이 있으면 그 중 가장 최소 인덱스를 반환하게끔(union할때 본인 인덱스보다 높은 것과 합치기 때문)
            ceiling=middle-1;
        }
        else{                        
            bottom=middle+1;
        }
    }
    return res;
}

int main(){
    cin>>N>>K;
    int M,V;
    for(int i=0;i<N;i++){
        scanf("%d %d",&M,&V);
        pq.push({V,M});
    }
    for(int i=0;i<K;i++){
        scanf("%d",&bag[i]);
        parent[i]=i;
    }
    //N까지 초기화, 유파에서 더 큰 인덱스로 합칠 것.
    //만약 불가능하면 N으로 합쳐질 것
    parent[K]=K;
    //가방을 크기 순으로 정렬
    sort(&bag[0],&bag[K]);
    long long sum=0;
    int cnt=K;
    while(cnt&&!pq.empty()){
        //pq 기준은 보석의 가치
        //한 가방에 하나의 보석만 담을 수 있다면 보석의 가치가 높은 순으로 k개 선택하는게 가장 최선 => 그리디
        //값어치가 더 큰 것을 담는게 무조건적으로 좋음
        //보석을 가방에 담을땐 보석의 무게에 딱 맞는 가방이 최선, 그 다음으로는 그거보다 한단계 큰 것
        //그런 가방을 찾아주는 것이 이분탐색 함수
        auto jewelry=pq.top();
        pq.pop();
        //보석 크기에 맞는 가방을 찾는다
        int bagIndex=binarySearch(jewelry.second);
        //만약 그 인덱스가 이미 사용됐다면 union-find의 결과로 parent[]에는 사용 가능한 다음 가방의 인덱스를 가르키고 있음
        bagIndex=findParent(bagIndex);
        //만약 그것이 K라면 사용할 수 있는 가방이 없음.
        //현재 보석을 담을 가방이 없음 => 다음 보석을 봄
        if(bagIndex==K) continue;
        //가방을 찾았으면 가치를 더하고 현재 index와 더 큰 가방의 인덱스를 union함
        sum+=jewelry.first;
        unionParent(bagIndex,bagIndex+1);
        --cnt;
    }
    cout<<sum<<endl;
}