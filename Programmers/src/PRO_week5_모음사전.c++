#include <string>
#include <vector>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.16

*난이도 : 2/5
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 부르트 포스, 재귀
*풀이 : 경우의 수를 따질지 아님 직접 재귀로 따라가볼지 사이에서 고민했다.
       수식이 생각나지 않아 재귀로 구현하였으나 성능이 나쁘지 않았다. 하지만 문자가 고작 5개 뿐이라 가능했던거 같다. 모든 알파벳에 대해서도 이 알고리즘이 가능할지는 회의적이다.

*느낀점 : 재귀로 풀어야지 마음 먹고도 코드를 생각해내는데 꽤나 까다로웠다.
        어떤 것을 전역에 둘지, 어떤 것을 재귀 함수에서 return할지, 기저 조건으론 어떤 것을 할지 등등 생각 할 것이 많았다.
*/

vector<char> ch={'A','E','I','O','U'};
string str;
int cnt=0;
int recul(int depth,string word){
    //depth가 깊어지면 return 0;
    if(depth==5)
        return 0;
    for(int i=0;i<5;i++){
        //각 단계마다 검사해야되기 때문에 각 재귀의 매 반복문 마다 하나 넣고 검사를 한다.
        str.push_back(ch[i]);
        cnt++;
        //같으면 당시 cnt 값을 return;
        if(str==word) return cnt;
        int res=recul(depth+1,word);
        //return 된 값이 있으면 그 값을 리턴한다. 만약 0이 리턴 됐다면 앞서 push 했던 char을 빼고 다음 포문에서 다음 캐릭터를 넣는다.
        if(res) return res;
        str.pop_back();
        }
    
}
int solution(string word) {
    int answer = recul(0,word);
    return answer;
}