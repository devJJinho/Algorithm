#include <string>
#include <vector>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.16

*난이도 : Level 1
*개인 풀이 시간 : 5min 
*개인 난이도 : 1/5 
*분류 : 모듈러 연산 사용
*풀이 : 총 날짜 수를 구한 다음 %7로 계산
*느낀점 : 윤년이 뭔지 알아야함.
        c++ enum을 사용해서 풀었으면 더 좋았을 듯.
        
*/


string solution(int a, int b) {
    int dates[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
    string name[]={"FRI","SAT","SUN","MON","TUE","WED","THU"};
    int totalDate=0;
    for(int i=0;i<a;i++){
        totalDate+=dates[i];
    }
    totalDate+=b;

    return name[(totalDate-1)%7];
}