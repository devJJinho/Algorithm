#include <string>
#include <vector>
#include <set>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.15

*난이도 : 2/5
*개인 풀이 시간 : 2hour
*개인 난이도 : 2/5 
*분류 : 자료구조 사용
*풀이 : set 사용한 이유, find, erase 연산이 로그에 비례한다. 
       conference를 표현하는 set을 두고 leave 기준으로 나간 사람을 찾는다. 없으면 conference에 입장시킴
       입장하면서 기존 conference에 있는 사람을 다 만나게 되므로 답에 추가한다.
       그러면서 새로운 사람이 들어오면 기존에 conference에 있는 사람은 모두 한명씩 추가.

*느낀점 : 어떻게 해야될지는 알았는데 머리속에 그려지지 않았다. 결국은 실세계에서 어떻게 할지 고민한 다음 그것을 코드로 표현하는 방식으로 해야된다.
        실제로 저런 상황이면 어떻게 할지를 생각하자.
*/

vector<int> solution(vector<int> enter, vector<int> leave) {
    vector<int> answer(enter.size(),0);
    set<int> conference;
    int enterIndex=0;
    int leaveIndex=0;
    while(leaveIndex<enter.size()){
        int n=leave[leaveIndex];
        if(conference.find(n)==conference.end()){
            int nextN=enter[enterIndex++];
            for(auto a:conference){
                answer[a-1]++;
            }
            answer[nextN-1]=conference.size();
            conference.insert(nextN);
            continue;
        }
        conference.erase(n);
        leaveIndex++;
    }
    return answer;
}