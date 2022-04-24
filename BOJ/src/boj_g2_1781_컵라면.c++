#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

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
    sort(arr.begin() , arr.end() , cmp);
    int sum = 0;
    for(int i = 0 ; i < N ; i++){
        if(pq.size() < arr[i].deadline){
            pq.push(arr[i]);
            sum += arr[i].cnt;
        }
        else{
            INFO top = pq.top();
            if(arr[i].cnt > top.cnt){
                pq.pop();
                sum -= top.cnt;
                pq.push(arr[i]);
                sum += arr[i].cnt;
            }
        }
    }
    cout << sum << endl;
}