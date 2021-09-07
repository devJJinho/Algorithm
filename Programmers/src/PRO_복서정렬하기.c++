#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define ABS(a) a<0?a*-1:a
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.07

*난이도 : ?
*개인 풀이 시간 : 코딩 20min, 디버깅 40min => cmp 함수에서 인자 오타
*개인 난이도 : 2/5 (Level 5 치고는 쉬운편) 
*분류 : 연산자 오버로딩
*풀이 : 주어진 정렬 순서를 cmp 함수로 구현하고 algorithm->sort를 cmp를 사용해서 돌린다.
       double의 비교는 찜찜하긴 하지만 !=과 오차범위 비교 둘 다 가능했다.

*느낀점 : 
        0.1의 double 표현은 상황에 따라 다를수가 있다고 한다. 이 문제에선 단순 비교 !=로도 작동했지만
        더 안전한 방법은 {차의 절대값이 오전범위 내인 경우 => 같다고 판단} 이다.

*/

const double Eps=0.000000000000001;
struct info{
    double per;
    int winsHeavier;
    int weight;
    int index;
};
bool cmp(info a,info b){
    if(a.per!=b.per) return a.per>b.per;
    //차의 절대값이 오처범위 내인지 비교하는 함수
    //if(ABS(a.per-b.per)>Eps) return a.per>b.per;
    if(a.winsHeavier!=b.winsHeavier) return a.winsHeavier>b.winsHeavier;
    if(a.weight!=b.weight) return a.weight>b.weight;
    return a.index<b.index;
}
vector<int> solution(vector<int> weights, vector<string> head2head) {
    vector<int> answer;
    vector<info> list;
    for(int i=0;i<head2head.size();i++){
        int index=i+1;
        int weight=weights[i];
        int cnt,wins,winsHeavier;
        cnt=wins=winsHeavier=0;
        for(int j=0;j<head2head[i].length();j++){
            if(head2head[i][j]=='W'||head2head[i][j]=='L') ++cnt;
            if(head2head[i][j]=='W'){
                ++wins;
                if(weights[j]>weight) ++winsHeavier;
            }
        }
        double per=cnt?wins/(double)cnt:0.0;
        list.push_back({per,winsHeavier,weight,index});
    }
    sort(list.begin(),list.end(),cmp);
    for(auto a:list)
        answer.push_back(a.index);
    return answer;
}