#include <iostream>
#include <vector>
#define MAX 11
#define MINF -100000001
#define INF 100000001

using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.01.29

*난이도 : S1
*개인 풀이 시간 : 40min
*개인 난이도 : 2/5 
*분류 : 브루트포스, 재귀, DFS, 백트래킹
*풀이 : 사용할 수 있는 연산의 수가 정해져있음. 예를들어 현재 자리에서 앞 뒤 수의 곱이 가장 크다 할지라도 곱을 나중에 썼을 때 더 큰 값이 나올 수가 있음. => 그리디 불가, 브루트포스 필요함.
       4가지의 연산에 대해 최대값은 이전 최대에 연산을 하는 것이고 최솟값은 이전 연산의 최솟값에 연산을 하는 것임.
       최대/최소 값을 찾는 재귀함수를 따로 두고 풀이함.

*느낀점 : 그리디를 사용할 때와 브루트포스를 사용할 때의 차이점을 느꼈음.
*/

int n;
vector<int> ls;
//완전 그리디하게는 하지 못한다. 지금 최선이 나중의 최선이란 보장이 없음.
// int maxLs[MAX];
// int minLs[MAX];
// dp처럼 cache가 가능한가? 미리 방문한 곳이 최적일것이라는 보장이 없다. 전제가 바뀐 후 다시 같은 점을 방문 했을떄 예전 값은 Return할 수가 없음. 다시 계산해봐야함
//+, -,*,/
int cnt[4]={0,0,0,0};
//내가 곱셈을 여기서 쓸지 나중에 쓸지에 따라 나중의 값도 변하는가? => 변한다.
//그럼 전체 경우에 대해 해야한다.

int cal(int a,int b,int operand){
    switch(operand){
        case 0: return a+b;
        case 1: return a-b;
        case 2: return a*b;
        case 3: return a/b;
    }
}
int calMin(int index, int total){
    if(index>=n) return total;
    
    int res=INF;
    for(int op=0;op<4;op++){
        if(!cnt[op]) continue;
        cnt[op]--;
        int temp=calMin(index+1,cal(total,ls[index],op));
        res=min(res,temp);
        cnt[op]++;
    }
    return res;
    //operand별로 연산 돌리기
        //내가 operand 하나 선택하면 선택지 하나 줄이고,
    //그 중 최소값 최대값 하기
    // maxLs[index]=max(maxLs[index],maxLs[index-1])
}

int calMax(int index,int total){
    if(index>=n) return total;
    int res=MINF;
    for(int op=0;op<4;op++){
        if(!cnt[op]) continue;
        cnt[op]--;
        int temp=calMax(index+1,cal(total,ls[index],op));
        res=max(res,temp);
        cnt[op]++;
    }
    return res;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        // maxLs[i]=MINF;
        // minLs[i]=INF;
        int temp;
        cin>>temp;
        ls.push_back(temp);
    }
    // maxLs[0]=minLs[0]=ls[0];
    for(int i=0;i<4;i++){
        int num;
        cin>>num;
        cnt[i]=num;
    }
    int minValue=calMin(1,ls[0]);
    int maxValue=calMax(1,ls[0]);

    cout<<maxValue<<endl<<minValue<<endl;
}