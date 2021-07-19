#include <vector>
#include <cmath>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.07.19

*난이도 : Level 1
*개인 풀이 시간 : 30min 
*개인 난이도 : 1/5 
*분류 : n진수로 변환하는 알고리즘
*풀이 : n진수로 변환하는 과정에서 차례대로 stack에 넣으면 자연스럽게 reverse 배열이 만들어짐.
*느낀점 : 
        모든 알고리즘을 더 핵심만 가지고 짤 필요가 있음.
        while(true)로 시작하고 중간에 break로 나오는건 리스크가 있음.
        
*/

vector<int> num;
int solution(int n) {
    int a,b;
    
    while(n!=0){
        a=n%3;
        num.push_back(a);
        n=n/3;
    }
    
    long long total=0;
    for(int i=0;i<num.size();i++){
        if(num[i]){
            total+=num[i]*pow(3,num.size()-1-i);
        }
    }
    return total;
}