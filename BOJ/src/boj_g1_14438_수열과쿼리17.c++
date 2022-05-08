#include <iostream>
#define INF 1000000000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.05.08

*난이도 : G1
*개인 풀이 시간 : 1 hour
*개인 난이도 : 2/5 
*분류 : 세그먼트 트리
*풀이 : 
*느낀점 : 

*/

//최대 배열 크기 100,000
//최대 배열 크기 보다 큰 2의 승보다 하나 더 큰 배열 필요
//2^17 > 100,000 , 때문에 2배 더 큰 2^18 길이의 배열 필요
int seg[1<<18];
int arr[100000];
int N , M;
void initTree(int start , int end , int idx){
    if(start == end){
        seg[idx] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    initTree(start , mid , idx * 2);
    initTree(mid + 1 , end , idx * 2 + 1);
    //최소값으로 업데이트
    seg[idx] = min(seg[2 * idx] , seg[2 * idx + 1]);
}

int findMin(int start , int end , int lower , int upper , int idx){
    if(upper < start || lower > end)
        return INF;
    if(lower <= start && upper >= end) return seg[idx];
    int minValue = INF;
    int mid = (start + end) / 2; 
    //범위 내에서 최소값 찾아서 return;
    minValue = min(minValue , findMin(start , mid , lower , upper , idx * 2));
    minValue = min(minValue , findMin(mid + 1 , end , lower , upper , idx * 2 + 1));
    return minValue;
}

void updateSeg(int start , int end , int idx , int target , int newValue){
    if(start > target || end < target) return;
    //업데이트하기
    if(start == end){
        seg[idx] = newValue;
        return;
    }
    int mid = (start + end) / 2;
    updateSeg(start , mid , idx * 2 , target , newValue);
    updateSeg(mid + 1 , end , idx * 2 + 1 , target , newValue);
    //업데이트 이후 최소값 다시 찾아서 업데이트
    seg[idx] = min(seg[idx * 2] , seg[idx * 2 + 1]);
    }

int main(){
    cin >> N;
    for(int i = 0 ; i < N ; i++)
        scanf("%d", &arr[i]);
    initTree(0 , N - 1 , 1);
    cin >> M;
    int a , b , c;
    while(M--){
        scanf("%d %d %d" , &a , &b , &c);
        if(a == 1){
            updateSeg(0 , N - 1 , 1 , b - 1 , c);
        }
        else if(a == 2){
            cout << findMin(0 , N - 1 , b - 1 , c - 1 , 1) << '\n';
        }
    }
}