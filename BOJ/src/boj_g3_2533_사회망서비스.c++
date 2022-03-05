#include <iostream>
#include <vector>
#define MAX 1000000
#define INF 1000001

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.03.03

*난이도 : G3
*개인 풀이 시간 : 1.5hr
*개인 난이도 : 2/5 
*분류 : DP, 재귀, DFS
*풀이 : 

*느낀점 : 점화식이 너무 어려움. 문제에서 묻는게 단순하고 그것이 누적이라면 dp 생각을 해보는게 좋을 듯

*/

vector<int> edge[MAX+1];
//입력을 양방향 그래프를 입력 받아서 isVisited가 필요
bool isVisited[MAX+1];
int N;
//contain, except
pair<int,int> recul(int index){
   int containThis=0;
   int exceptThis=0;
   isVisited[index]=true;
   for(int next:edge[index]){
       if(isVisited[next]) continue;
       auto res=recul(next);
       //내 위치에 얼리어답터를 둔다면 내 자식에는 있거나 없거나 상관없이 최소만 올라오면 됨 때문에 min으로 비교
       containThis+=min(res.first,res.second);
       //내 위치에 두지 않는다면 내 자식에는 무조건 있어야함 때문에 (자식을 포함한 값)만 더함
       exceptThis+=res.first;
   }
   //주어진 간선이 트리를 가성하고 들어왔기 때문에 현재의 노드가 다시 이용될 리 없음. 때문에 메모이제이션은 필요X
   //부모에게 return만 하면 된다.
   return {1+containThis,exceptThis};
}

int main(){
    cin>>N;
    int a,b;
    for(int i=0;i<N-1;i++){
        cin>>a>>b;
        //(부모, 자식)순으로 입력이 들어오는게 아니기 때문에 일단 양방향으로 입력받음
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    //하나의 루트를 기준으로 다시 트리를 만드는게 아니기 때문에 isVisited 배열을 두고 트리를 순회함
    auto res=recul(1);
    cout<<min(res.first,res.second)<<endl;
}