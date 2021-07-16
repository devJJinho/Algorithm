#include <iostream>
#define MAX 1000000

using namespace std;

/*
 
@author  :  Jinho Jeong
@date    :  2021.06.29

*난이도 : Silver 3
*개인 풀이 시간 : 20min
*개인 난이도 : 1/5
*분류 : 이분 탐색
*풀이 : 이분 탐색으로 찾아낸다.
*느낀점 : 자료 값의 최대 값을 알고 주의해서 코딩해야된다.
        
*/

int forest[MAX+2];
int main(){
    int n,m;
    int max=0;
    cin>>n>>m;

    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        if(max<temp)max=temp;
        forest[i]=temp;
    }
    int low=0;
    int high=max;
    int maxHeight=0;
    while(low<=high){
        int mid=(low+high)/2;
        //cnt는 int 범위를 넘어선다.
        long long cnt=0;
        for(int i=0;i<n;i++){
            if(forest[i]-mid>0) cnt+=forest[i]-mid;
            //더 더할 필요가 없다.
            if(cnt>mid)break;
        }
        if(cnt>=m){
            // 최대값을 묻기 때문에 mid값을 올리는 쪽에 ==조건을 준다.
            maxHeight=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
   cout<<maxHeight;
   return 0;
}
