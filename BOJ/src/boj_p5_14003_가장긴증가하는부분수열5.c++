#include <iostream>
#include <vector>
#include <deque>
#define MAX 1000005
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.23

*난이도 : p5
*개인 풀이 시간 : 1hour 
*개인 난이도 : 2/5 
*분류 : LIS (DP+이분 탐색)
*풀이 : 
        DP[i]=i번째 인풋의 최대 lis 길이
        이분 탐색은 정확히 말하면 Lower Bound를 구하는 알고리즘이다. 일반적인 이분 탐색으로 위치를 찾으려다가 계속 실패했으나 lower_bound라는 알고리즘이 있었다.
        lis 배열을 벡터를 사용해도 되지만, 나는 입출력의 빠르기를 위해 일반 배열로 하고 index만 따로 유지했다. => 중간 어느 값 이후로 다 삭제해야되는 줄 알고 그렇게 했으나, 그럴 필요는 없었다. 하지만 벡터보단 빠를거라 생각된다.
        lis 유지 방법 : 1. 비어있으면 바로 삽입한다.
                      2. 정렬되어 있는 lis의 가장 마지막 값보다 Input이 크다면 뒤에 삽입
                      3. 그 사이 어느 값이라면 lower Bound를 통해 찾은 위치에 삽입한다. 그리고 그 위치까지 길이가 lis이다.

*느낀점 : 이분 탐색 코드에 문제가 있는 줄은 알았으나 이것을 lower bound 형식으로 바꿀 생각을 못했다.
        더 많은 경험이 필요해보인다. 
        
*/

int dp[MAX];
int a[MAX];
int lis[MAX];
int last=-1;
//
int lowerBound(int value){
    int low=0; //index 기준
    int high=last;
    int mid;
    while(high>low){
        mid=(low+high)/2;
        //나보다 작은거 보다 뒤에 와야되기 때문에 나보다 작다면 바로 low를 올린다.
        if(lis[mid]<value)
            low=mid+1;
        else //크거나 같은 경우는 모두 mid로 내린다. mid 값을 중복하기 때문에 작거나 같은 경우도 검출이 된다.
            high=mid;
    }
    //마지막으로 high 값을 리턴한다. high=low일때 마치기 떄문에 사실 low 값을 리턴해도 된다.
    return high;
}

int findLis(int value){
    //비어 있으면 바로 넣는다.
    if(last==-1) {
        lis[++last]=value;
        return 1;
    }
    //정렬되어 있기 때문에 마지막값보다 크면 삽입한다.
   int res=lowerBound(value);
   if(res==last&&lis[last]<value){
       lis[++last]=value;
       return last+1;
   }
   // 그 외 lis에서 자기 위치를 찾아야 한다면 lowerBound를 실행시켜 자기 자리를 찾고 그 위치의 값을 업데이트한다.
   // 본인 위치까지 lis가 유지되기 때문에 index+1 (0부터 시작)이 최고긴 lis이다 => 리턴한다.
   lis[res]=value;
   return res+1;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int cnt=0;
    int num;
    cin>>num;
    for(int i=0;i<num;i++){
        cin>>a[i];
        //i번째 input에 대해서 lis를 구한 뒤 dp[i]에 업데이트 한다. dp[i]는 i번째 인풋의 최대 lis 길이
        dp[i]=findLis(a[i]);
        //바로 길이를 구한다.
        if(dp[i]>cnt) cnt=dp[i];
    }
    cout<<cnt<<endl;
    deque<int> answer;
    //뒤에서 부터 돌아오면서 최대길이-- 을 구한다.
    //역순을 위해 deque의 앞에 넣는다.
    for(int i=num-1;i>=0;i--){
        if(dp[i]==cnt){
            answer.push_front(a[i]);
            --cnt;
            //이게 가능한 이유는 dp[j], dp[i] (j>i)일 경우 j는 i의 범위까지 다 포함하고도 길이가 dp[i]보다 길기 때문에 a[j]는 a[i]보다 항상 크다.
        }
    }
    for(int temp:answer)
        cout<<temp<<" ";
    return 0;
}