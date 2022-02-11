#include <iostream>
#include <vector>
#define MAX 10000
using namespace std;

/*
*난이도 : G1
*개인 풀이 시간 : 4hour
*개인 난이도 : 4/5 
*분류 : DFS, 트리, 
*풀이 : 

*느낀점 : 
*/

vector<int> map[MAX+1];
int value[MAX+1];
int n;
pair<int,int> recul(int preIndex,int index){
    int normalVil=0;
    int goodVil=0;
    for(int nextNode:map[index]){
        if(nextNode==preIndex) continue;
        auto res=recul(index,nextNode);
        normalVil+=max(res.first,res.second);
        goodVil+=res.first;
    }
    goodVil+=value[index];
    return {normalVil,goodVil};
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&value[i]);
    }
    int a,b;
    for(int i=0;i<n-1;i++){
        scanf("%d %d",&a,&b);
        map[a].push_back(b);
        map[b].push_back(a);
    }
    pair<int,int> res=recul(0,1);
    cout<<max(res.first,res.second)<<endl;
}

///////////////////////////////////////////////////////////

#include <iostream>
#include <stack>
#include <vector>
#define MAX 10000
using namespace std;

//현재 index에서 다음 값만 조회, 여태까지 선택지를 공유할 필요가 있음
//여태까지 선택을 보면서 중복되지 않으면 선택하고 선택지에 추가
//백트래킹으로 복원
vector<int> village;
vector<int> map[MAX+1];
int value[MAX+1];
// bool isVisited[MAX+1];
int n;
int maxValue=0;
void recul(int index){
    //기저케이스
    if(index>n){
        int sum=0;
        bool isSelected[MAX+1];
        for(int i=0;i<=n;i++) isSelected[i]=false;
        
        for(int node:village){
            cout<<node<<" ";
            sum+=value[node];
            isSelected[node]=true;
        }
        cout<<endl;
        //검증 시작
        if(sum<maxValue) return;
        bool isCorrespond=true;
        for(int i=1;i<=n;i++){
            if(!isSelected[i]){
                bool isExist=false;
                for(int connected:map[i]){
                    if(isSelected[connected]){
                        isExist=true;
                        break;
                    }
                }
                if(!isExist){
                    isCorrespond=false;
                    break;
                }
            }
        }
        if(isCorrespond){
            //검증 결과 가능하면
            if(sum>maxValue) maxValue=sum;
            cout<<"max:"<<maxValue<<endl;
        }
        return;
    }
    // if(isVisited[index]) return;

    //stack안의 마을과 직접적으로 연결된 점이 있는지?
    // isVisited[index]=true;
    bool isStackable=true;
    for(int preNode:village){
        if(!isStackable) break;
        for(int connected:map[preNode]){
            if(connected==index){
                isStackable=false;
                break;
            }
        }
    }
    if(isStackable) village.push_back(index);
    recul(index+1);
    if(isStackable) {
        village.pop_back();
        recul(index+1);
    }
    // for(int nextNode:map[index]){
    //     //stack에 현재 점을 넣은 채로 재귀를 할건지?
    //     // if(isVisited[nextNode]) continue;
    //     cout<<"now:"<<index<<" nextNode:"<<nextNode<<endl;
    //     if(isStackable) village.push_back(index);
    //     recul(nextNode,cnt+1);
    //     if(isStackable) {
    //         village.pop_back();
    //         recul(nextNode,cnt+1);
    //     }
    // }
    // isVisited[index]=false;

    //진짜 갈 수 없을때와 분리 필요
    // if(!isAble) {
    //     if(isStackable) village.push_back(index);
    //     recul(n+1);
    //     if(isStackable) village.pop_back();
    // }
    // isVisited[index]=false;
}

int main(){
    //재귀로 구현
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&value[i]);
    }
    int a,b;
    for(int i=0;i<n-1;i++){
        scanf("%d %d",&a,&b);
        map[a].push_back(b);
        map[b].push_back(a);
    }
    recul(1);
    cout<<maxValue<<endl;
    cout<<"changed"<<endl;
}

/////////////////////////////////////////////////////////////

#include <iostream>
#include <stack>
#include <vector>
#define MAX 10000
using namespace std;

//현재 index에서 다음 값만 조회, 여태까지 선택지를 공유할 필요가 있음
//여태까지 선택을 보면서 중복되지 않으면 선택하고 선택지에 추가
//백트래킹으로 복원
vector<int> village;
vector<int> map[MAX+1];
int value[MAX+1];
// bool isVisited[MAX+1];
int n;
int maxValue=0;
void recul(int index){
    //기저케이스
    if(index>n){
        int sum=0;
        bool isSelected[MAX+1];
        for(int i=0;i<=n;i++) isSelected[i]=false;
        
        for(int node:village){
            cout<<node<<" ";
            sum+=value[node];
            isSelected[node]=true;
        }
        cout<<endl;
        //검증 시작
        if(sum<maxValue) return;
        bool isCorrespond=true;
        for(int i=1;i<=n;i++){
            if(!isSelected[i]){
                bool isExist=false;
                for(int connected:map[i]){
                    if(isSelected[connected]){
                        isExist=true;
                        break;
                    }
                }
                if(!isExist){
                    isCorrespond=false;
                    break;
                }
            }
        }
        if(isCorrespond){
            //검증 결과 가능하면
            if(sum>maxValue) maxValue=sum;
            cout<<"max:"<<maxValue<<endl;
        }
        return;
    }
    // if(isVisited[index]) return;

    //stack안의 마을과 직접적으로 연결된 점이 있는지?
    // isVisited[index]=true;
    bool isStackable=true;
    for(int preNode:village){
        if(!isStackable) break;
        for(int connected:map[preNode]){
            if(connected==index){
                isStackable=false;
                break;
            }
        }
    }
    if(isStackable) village.push_back(index);
    recul(index+1);
    if(isStackable) {
        village.pop_back();
        recul(index+1);
    }
    // for(int nextNode:map[index]){
    //     //stack에 현재 점을 넣은 채로 재귀를 할건지?
    //     // if(isVisited[nextNode]) continue;
    //     cout<<"now:"<<index<<" nextNode:"<<nextNode<<endl;
    //     if(isStackable) village.push_back(index);
    //     recul(nextNode,cnt+1);
    //     if(isStackable) {
    //         village.pop_back();
    //         recul(nextNode,cnt+1);
    //     }
    // }
    // isVisited[index]=false;

    //진짜 갈 수 없을때와 분리 필요
    // if(!isAble) {
    //     if(isStackable) village.push_back(index);
    //     recul(n+1);
    //     if(isStackable) village.pop_back();
    // }
    // isVisited[index]=false;
}

int main(){
    //재귀로 구현
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&value[i]);
    }
    int a,b;
    for(int i=0;i<n-1;i++){
        scanf("%d %d",&a,&b);
        map[a].push_back(b);
        map[b].push_back(a);
    }
    recul(1);
    cout<<maxValue<<endl;
    cout<<"changed"<<endl;
}