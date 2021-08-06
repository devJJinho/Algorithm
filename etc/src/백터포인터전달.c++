#include <iostream>
#include <vector>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.04

*해설 : 
    함수에 백터의 포인터 전달이 가능한지 확인하기 위해 작성한 코드
    2차원 백터를 call by reference로 받은 다음 n값의 시작점(n값 중 최소 index)를 이분탐색으로 탐색하고 결과를 반환한다.

*결과값 : 
        0
        3
        6
        9
*/

int findStart(vector<vector<int>> *v,int n){
    int start=0;
    int end=(*v).size();
    int min=0;

    while(start<=end){
        int mid=(start+end)/2;
        if((*v)[mid][0]<n){
            start=mid+1;
        }
        //v[mid][0]==n 조건이 else에 걸리기 때문에 min 값을 여기서 mid값으로 업데이트한다.
        else{
            min=mid;
            end=mid-1;
        }
    }
    return min;
}

int main(){
    vector<vector<int>> a(10);
    a[0].push_back(1);
    a[1].push_back(1);
    a[2].push_back(1);
    a[3].push_back(2);
    a[4].push_back(2);
    a[5].push_back(2);
    a[6].push_back(3);
    a[7].push_back(3);
    a[8].push_back(3);
    a[9].push_back(4);
    
    cout<<findStart(&a,1)<<endl;
    cout<<findStart(&a,2)<<endl;
    cout<<findStart(&a,3)<<endl;
    cout<<findStart(&a,4)<<endl;
}