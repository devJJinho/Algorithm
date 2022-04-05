#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.05

*개인 풀이 시간 : 50Min
*개인 난이도 : 2/5
*분류 : 문자열, 자료구조, pq
*풀이 : 주석 참조
*느낀점 : 
*/

//각각은 pq;
priority_queue<int> maxHeap;
priority_queue<int,vector<int>,greater<int>> minHeap;

//삭제된 것을 담는 hash Map
unordered_map<int,int> delMax;
unordered_map<int,int> delMin;

//최대값 삭제
int popMax(){
    int cur=0;
    bool isFind=false;
    while(true){
        if(!maxHeap.size()) break;
        cur=maxHeap.top();
        maxHeap.pop();
        auto pt=delMin.find(cur);
        //방금 pop한 최대값이 삭제된 최소값 목록에 없을 때까지 진행
        if(pt == delMin.end()) {
            isFind=true;
            break;
        }
        else{
            //만약 삭제된 목록에 있으면 cnt 감소
            //만약 감소된 cnt가 0이면 아예 삭제하기
            if(pt->second == 1){
                delMin.erase(pt->first);
                continue;
            }
            pt->second = pt->second-1;
        }
    }
    //만약 못찾았으면 0반환. 못찾을 경우 : maxHeap 안에 있는 내용물이 Minheap에서 다 삭제해서 쓸 수 있는게 없음
    if(!isFind) return 0;
    //찾았으면 cur안에는 실제 최대값이 담겨있음
    auto pt=delMax.find(cur);
    //만약 delMax에 cur이 없으면 만들어주고
    if(pt == delMax.end()) 
        delMax.insert({cur,1});
    else
    //있으면 그 값을 하나 올려줌. 이는 동일한 값이 들어왔을때 처리를 위해
        pt->second = pt->second+1;
    
    return cur;
}

int popMin(){
    int cur=0;
    bool isFind=false;
    while(true){
        if(!minHeap.size()) break;
        cur=minHeap.top();
        minHeap.pop();
        auto pt=delMax.find(cur);
        if(pt == delMax.end()) {
            isFind=true;
            break;
        }
        else{
            if(pt -> second == 1){
                delMax.erase(pt -> first);
                continue;
            }
            pt->second = pt->second-1;
        }
    }
    if(!isFind) return 0;
    auto pt=delMin.find(cur);
    if(pt == delMin.end()) 
        delMin.insert({cur,1});
    else
        pt->second = pt->second+1;
    
    return cur;
}
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    for(auto n : operations){
        if(n[0] == 'I'){
            stringstream ss(n);
            //임시로 담기는 곳
            string s;
            //공백과 개행을 기준으로 자른 뒤 담을 곳
            vector<string> temp;
            while(ss >> s) temp.push_back(s);
            int num=stoi(temp[1]);
            maxHeap.push(num);
            minHeap.push(num);
        }
        else if(n[0] == 'D'){
            if(n[2] == '-'){
               popMin();
            }
            else{
                popMax();
            }
        }
    }
    answer.push_back(popMax());
    answer.push_back(popMin());
    return answer;
}