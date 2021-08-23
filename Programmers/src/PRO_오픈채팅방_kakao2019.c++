#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>

using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.08.23

*난이도 : kakao blind 2019
*개인 풀이 시간 : 30min 
*개인 난이도 : 2/5
*분류 : 해쉬 사용, 문자열
*풀이 : uid를 key값으로 한 해쉬테이블을 유지함으로써 최신 아이디를 기록했다.
*느낀점 : log 벡터를 두고 첫 record 순회때 다시 쓸 uid,action을 기록한게 주요했다.
        action의 경우 bool로 구현했어도 될 듯
        unordered_map의 경우 hash_table로 구현되어 있고 그냥 map의 경우 red black tree로 구현되어있다.
        hash를 사용했던 것이 메모리는 더 차지했지만 성능은 더 좋았다고 생각한다.
        c에서 문자열 다루기가 너무 힘들다. 연습일 더 필요하다. 필요하다면 다른 언어의 사용도 고려해봐야겠다.
*/

unordered_map<string,string> map;
vector<pair<string,string>> log;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    for(auto node:record){
        string msg[3];
        stringstream ss;
        //공백 기준이라 이렇게 풀었지만, 만약 특정 문자열 기준으로 잘라야한다면 어떻게 할지?
        ss.str(node);
        ss>>msg[0]>>msg[1]>>msg[2];
        if(msg[0]=="Enter"||msg[0]=="Change"){
            if(map.count(msg[1]))
                map.at(msg[1])=msg[2];
            else
                map.insert({msg[1],msg[2]});
        }
        if(msg[0]=="Enter"||msg[0]=="Leave")
            log.push_back({msg[0],msg[1]});
    }
    string exp[2]={"님이 들어왔습니다.","님이 나갔습니다."};
    for(auto a:log){
        string ret="";
        ret+=map.find(a.second)->second;
        ret+=a.first=="Enter"?exp[0]:exp[1];
        answer.push_back(ret);
    }

    return answer;
}
