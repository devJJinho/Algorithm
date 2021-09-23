#include <iostream>
#include <deque>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.23

*난이도 : G4
*개인 풀이 시간 : 2hr
*개인 난이도 : 2/5 
*분류 : LIS 알고리즘 DP 풀이 (범위가 작기 때문에 dp만 사용했음)
*풀이 : 가능한 값의 범위도 1~1000, 입력값도 1~1000이었기 때문에 값의 범위를 dp 인자로 두고 풀이했다. 그리고 수열을 print하기 위해 직전 index도 보관하는 index 배열도 선언했다.
       이 풀이로 테스트 케이스는 다 통과했으나, 문제는 중복된 값이 들어왔을때 index배열이 오염된다는 것이다.
       1 3 4 5 6 2 3이 들어오면 정답은 길이 5에 수열은 13456이다. 하지만 마지막에 2,3이 들어왔을때 3은 직전에 1만 있어서 길이 2였던 것에서 1,2,3이 가능해지기 때문에 dp와 index를 모두 업데이트해버린다.
       이러면 정답이 보장되지 않는다.
       때문에 dp는 인력값의 순위로 진행했으며 순열 순회를 위한 index를 사용하지 않았다. 문제가 가능한 모든 조합 중 하나를 출력하라고 했기 때문에 전체 범위를 한바퀴 돌면서 가능한 최대값부터 하나씩 출력했다. 
       index를 따로 기록하지 않고도 가능했던 이유는, dp[i]의 정의는 i번째 input 보다 작은값이 dp[i]-1개 있다는 뜻이다. 그러면 dp[i]=3, dp[j]=2, (i>j) 일 때 i는 j값을 다 포함하기 때문에 dp[i]=2를 깔고 가지만 1이 더 크다 즉 index[j]의 값이 더 크다는 뜻이 된다.

*느낀점 : LIS 알고리즘에 대해 처음 알게되었다. 
        중복된 input이 들어왔을 때 생기는 영향에 대해서도 고민하며 풀이해야겠다.
*/

int dp[1002];
int index[1002];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>index[i];
        int value=0;
        for(int j=0;j<i;j++){
            if(index[j]<index[i]&&dp[j]>value)
                value=dp[j];
        }
        dp[i]=value+1;
    }
    deque<int> answer;
    int cnt=0;
    for(int i=0;i<n;i++)
        if(dp[i]>cnt) cnt=dp[i];
    cout<<cnt<<endl;
    for(int i=n-1;i>=0&&cnt;i--){
        if(dp[i]==cnt){
            answer.push_front(index[i]);
            --cnt;
        }
    }
    for(auto a:answer)
        cout<<a<<" ";  
    return 0;
}

//값에 대해서 dp한 경우 => 틀림//

#include <iostream>
#include <deque>
using namespace std;

int dp[1002];
int index[1002];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        int max=0;
        int idx=0;
        for(int j=1;j<num;j++){
            if(dp[j]>max) {
                max=dp[j];
                idx=j;
            }
        }
        dp[num]=max+1;
        index[num]=idx;    
    }
    deque<int> answer;
    int idx,max;
    idx=max=0;
    for(int i=1;i<=1000;i++){
        if(dp[i]>max) {
            max=dp[i]; 
            idx=i;
        }
    }
    while(idx){
        answer.push_front(idx);
        idx=index[idx];
    } 
    cout<<answer.size()<<" "<<endl;
    for(auto a:answer)
        cout<<a<<" ";  
    return 0;
}