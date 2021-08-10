#include <iostream>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.10

*난이도 : S5
*개인 풀이 시간 : 20min
*개인 난이도 : 1/5 
*분류 : 몫/나머지 연산 사용
*풀이 : 이전 달ㄹ에서 남은 날 만큼을 더해서 모듈러 연산을 했다.
*느낀점 : 출력 값에서 공백,개행까지 모두 똑같이 해야했음. 출력값 예시를 자세히 살펴 볼 필요가 있다.

*/

int main(){
    int num;
    cin>>num;
    for(int n=1;n<=num;n++){
        int monInYear,daysInMon,daysInWeek;
        int row=0;
        int left=0;
        cin>>monInYear>>daysInMon>>daysInWeek;
        for(int i=0;i<monInYear;i++){
            row+=(daysInMon+left)/daysInWeek;
            if((daysInMon+left)%daysInWeek!=0)++row;
            left=(daysInMon+left)%daysInWeek;
        }
        if(n!=1)cout<<endl;
        cout<<"Case #"<<n<<": "<<row<<" ";
    }
}