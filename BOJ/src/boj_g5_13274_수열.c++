#include <iostream>
#include <algorithm>
#define MAX 100000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.05.07

*난이도 : G5
*개인 풀이 시간 : 1hour 
*개인 난이도 : 3/5 
*분류 : 삽입 정렬
*풀이 : - 삽입 정렬을 구현해서 푸는게 정석 , 난 std sort를 사용함.
       - 전체 범위에 대해 정렬을 하면 시간 초과남 => 업데이트 된 범위와 수에 따라 범위를 줄여 정렬 실행
       - 삽입정렬로 다시 구현 할 필요 있음
*느낀점 : 배열을 정렬하기 위해선 sort(범위 + '몇번째' , 범위 + '몇번째)임

*/

int N , K;
long long int arr[MAX];
int main(){
    cin >> N >> K;
    for(int i = 0 ; i < N ; i++){
        scanf("%lld" , &arr[i]);
    }
    sort(arr , arr + N);
    int l , r , x;
    while(K--){
        scanf("%d %d %d" , &l , &r , &x);
        l--;  r--;
        for(int i = l ; i <= r ; i++)
            arr[i] += x;
        //만약 범위에서 크기가 커지면 이미 정렬되어 있는 배열에서 범위 이후 끝까지에서 정렬하면 됨
        if(x > 0){
        	sort(arr + l , arr + N);
        }
        //만약 범위의 수가 줄어들었으면 내림차순 기준으로 처음부터 범위의 끝까지에서 정렬하면 됨
        else if(x < 0){
        	sort(arr , arr + r + 1);
        }
    }

    for(int i = 0 ; i < N ; i++)
        printf("%lld " , arr[i]);
    return 0;
}