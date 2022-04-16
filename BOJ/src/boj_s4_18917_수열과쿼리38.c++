#include <iostream>

using namespace std;


/*
 
@author  :  Jinho Jeong
@date    :  2022.04.16

*난이도 : Silver 4
*개인 풀이 시간 : 10min
*개인 난이도 : 2/5
*분류 : 수학, XOR 연산의 역원
*풀이 : 묻는게 합과 XOR이기 때문에 전체 배열을 유지할 필요가 없었음
       덧셈과 XOR의 역원을 취해 수를 제외하는 연산을 구현함.
*느낀점 : 

*/

typedef long long int lli;
int N;
lli sum;
int gate;
int main(){
    cin >> N;
    int a,b;
    for(int i = 0 ; i < N ; i++){
        scanf("%d" , &a);
        if(a == 1){
            scanf("%d" , &b);
            sum += b;
            gate ^= b;
        }
        else if(a == 2){
            sum -= b;
            //XOR 연산의 덧셈에 대한 역원은 XOR 연산
            gate ^= b;
        }
        else if(a == 3){
            printf("%lld\n" , &sum);
        }
        else 
            printf("%d\n" , gate);
    }
    return 0;
}