#include <iostream>
#include <queue>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.06.27

*난이도 : Silver3
*개인 풀이 시간 : 20min 
*개인 난이도 : 1/5 
*분류 : 자료구조 queue, maxheap
*풀이 : 현재 큐 내의 최대값이 항상 필요하기 때문에 Max heap을 별도로 사용했다.
        최대 배열 길이가 100이라 순회하며 최대값을 구해도 무리는 없지만 Max heap 사용이 효율적이라 판단했다.
*느낀점 : 테스트 케이스가 여러개인 경우 큐,힙을 따로 사용해야된다.
*/

int main(){
    int num;
    cin>>num;
    while(num--){
        queue<pair<bool,int>> printerQ;
        priority_queue<int,vector<int>> pq;
        int len,index;
        cin>>len>>index;
        for(int i=0;i<len;i++){
            int temp;
            bool isSelect=false;
            cin>>temp;
            if(i==index)
                isSelect=true;
            //isSelect가 true인 노드를 출력 순서를 알아야한다.
            printerQ.push(make_pair(isSelect,temp));
            pq.push(temp);
        }
        int cnt=0;
        while(!printerQ.empty()){
            pair<bool,int> cur;
            cur=printerQ.front();
            printerQ.pop();
            if(cur.second>=pq.top()){
                cnt++;
                pq.pop();
                if(cur.first) break;
            }
            else{
                printerQ.push(cur);
            }
        }
        cout<<cnt<<endl;
    }
}