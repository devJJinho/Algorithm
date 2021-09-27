#include <string>
#include <vector>
#include <vector>
#include <queue>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.27

*난이도 : 2/5
*개인 풀이 시간 : 5min
*개인 난이도 : 1/5 
*분류 : 최대값 찾기
*풀이 : 양변 중 긴 변에서 최대값, 짧은 변에서 최대값을 찾아서 곱하면 된다.
       최대값을 찾기 위해 pq를 사용했다.

*느낀점 : 증명하는 방법을 찾고싶다.
*/

int solution(vector<vector<int>> sizes) {
    priority_queue<int,vector<int>> lHeap;
    priority_queue<int,vector<int>> sHeap;
    for(auto a:sizes){
        if(a[0]>a[1]){
            lHeap.push(a[0]);
            sHeap.push(a[1]);
        }
        else{
            lHeap.push(a[1]);
            sHeap.push(a[0]);
        }
    }
    int answer=lHeap.top()*sHeap.top();
    return answer;
}