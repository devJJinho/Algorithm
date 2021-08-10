#include <iostream>
#define MAX 1000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.10

*난이도 : B2
*개인 풀이 시간 : 10min 
*개인 난이도 : 1/5 
*분류 : 배열의 이해, index 사용
*풀이 : 배열에서 인덱스를 두며 순회하며 최대값을 찾았다.
*느낀점 : 테스트는 가장 작음 값에서 옳바르게 나오는지, 최대값에서 런타임 레어가 안뜨는지, 알고리즘의 마지막 부분이 잘 수행되는지 체크해야된다.

*/

int map[MAX+1];

int main(){
    int len;
    cin>>len;
    for(int i=0;i<len;i++){
        int temp;
        cin>>temp;
        map[i]=temp;
    }
    int preValue=map[0];
    int firstValue=map[0];
    int maxEle=0;
    for(int i=1;i<len;i++){
        if(map[i]>preValue){
            if(i==len-1){
                maxEle=max(maxEle,map[i]-firstValue);
            }
            preValue=map[i];
        }
        else{
            maxEle=max(maxEle,preValue-firstValue);
            firstValue=preValue=map[i];
        }
    }
    cout<<maxEle;
}