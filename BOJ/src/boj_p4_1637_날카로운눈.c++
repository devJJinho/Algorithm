#include <iostream>
#define MAX 20000
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.08.15
*난이도 : P4
*개인 풀이 시간 : 2hr
*개인 난이도 : 3/5
*분류 : 이분탐색, 큰 수
*풀이 : 
        A+KB를 따라가면서 카운트하면 시간 내에 할 수가 없음
        그리고 카운트를 위해선 2^32개의 배열이 필요하고 홀수개를 찾기 위해 2^32번 순회 하는 등 연산이 너무 큼
        이때 이분 탐색으로 구간 내에 가능한 수의 개수를 구하고, 그 것이 홀수라면 범위를 줄여나가며 찾는 방식
        홀수개인 정수가 있다면 결국은 그 수로 수렴하게 되어있음

*느낀점 :
        큰 수를 만나고 일방적인 방식으론 불가능하겠다 생각은 들었지만, 이분 탐색을 사용할 생각은 하지 못함
*/

struct INFO{
    int a,c,b;
};

int N;
INFO ref[MAX];

long long hasOddMember(int low, int high){
    long long total = 0;
    for(int i = 0 ; i < N ; i++){
        int &a = ref[i].a;
        int &b = ref[i].b;
        int &c = ref[i].c;
        //세그먼트 트리처럼 구간을 벗어나면 continue
        if(low > c || high < a) continue;
        int start = low > a ? low : a;
        int end = high > c ? c : high;
        //실구간 start - end를 구함
        //실구간 사이에서 b가 몇개 들어가는지
        long long subTotal = (((end - a) / b) - ((start - a) / b));
        //그리고 구간 시작을 포함할지 말지
        if((start - a) % b == 0)
            ++subTotal;
        total += subTotal;
    }
    return total;
}
long long int biSearch(){
    long long high = 2147483647;
    long long low = 1 , mid;
    long long oddIdx = 0;
    while(low <= high){
        mid = (low + high) / 2;
        long long temp = hasOddMember(low , mid);
        //만약 홀수라면 
        if(temp % 2){
            high = mid - 1;
            //홀수인 경우에만 oddIdx를 업데이트함
            oddIdx = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return oddIdx;
}
int main(){
    cin >> N;
    for(int i = 0 ; i < N ; i++){        
        scanf("%d %d %d" , &ref[i].a , &ref[i].c, &ref[i].b);
    }
    long long oddIdx = biSearch();
    //oddIdx에 해당하는 idx가 진짜 홀수개 있는지 검증
    long long cnt = hasOddMember(oddIdx, oddIdx);
    if(cnt % 2 == 0)
        cout << "NOTHING" << endl;
    else   
        cout << oddIdx << " " <<cnt << endl;
    return 0;
}