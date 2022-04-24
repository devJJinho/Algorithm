#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.24

*난이도 : G2
*개인 풀이 시간 : 1hour
*개인 난이도 : 2/5 
*분류 : 그리디 , pq
*풀이 : 
       
*느낀점 : 
       
*/

struct INFO{
    int deadline , cnt;
    bool operator<(const INFO& b)const{
        return cnt > b.cnt;
    }
};
bool cmp(INFO& a , INFO& b){
    return a.deadline < b.deadline;
}
int N;
vector<INFO> arr;
priority_queue<INFO> pq;
int main(){
    cin >> N;
    int idx = 0;
    arr.resize(N);
    int deadline , cnt;
    for(int i = 0 ; i < N ; i++){
        scanf("%d %d" , &deadline , &cnt); 
        arr[idx++] = {deadline , cnt};
    }
    //deadline이 작은 순으로 정렬
    sort(arr.begin() , arr.end() , cmp);
    int sum = 0;
    for(int i = 0 ; i < N ; i++){
        // 현재 데드라인(arr[i])에는 최대 데드라인 일 만큼의 일을 할 수 있음
        // 때문에 pq의 사이즈가 데드라인보다 작다면 더 넣을 수 있음
        if(pq.size() < arr[i].deadline){
            pq.push(arr[i]);
            sum += arr[i].cnt;
        }
        //만약 데드라인만큼의 일이 이미 있다면? 크기를 비교해서 하나를 빼거나 아님 무시하고 넘어가야함
        else{
            INFO top = pq.top();
            //컵라면의 개수가 더 많은 걸 남김
            //가지고 있는 문제 중에서 컵라면이 가장 적은 것(민힙 사용)과 arr[i]와 비교
            if(arr[i].cnt > top.cnt){
                pq.pop();
                //빼면서 합에서 빼기
                sum -= top.cnt;
                pq.push(arr[i]);
                sum += arr[i].cnt;
            }
        }
    }
    cout << sum << endl;
}