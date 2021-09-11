#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2021.09.11

*난이도 : 2/5
*개인 풀이 시간 : 30min
*개인 난이도 : 2/5 
*분류 : 문자열, 자료구조 사용, HASH or MAP, 검색에 유리한 자료구조
*풀이 : 검색에서 유리하고자 멀티맵, set을 사용했다. 스트링에 대한 검색을 빨리하고자 index를 부여하고 유지했다. 
       하지만 id를 인덱스에서 찾는 것과 스트링으로 찾는 것이 같은 성능이지 않나 싶다.

*느낀점 : 카카오는 문자열, 현업의 문제와 비슷한 문제가 많이 나오는 듯 하다.
*/

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    multimap<string,string> umap;
    vector<int> answer(id_list.size(),0);
    set<pair<string,string>> isReported;
    for(string user:report){
        string from,to;
        stringstream ss;
        ss.str(user);
        ss>>from>>to;
        if(isReported.find({to,from})==isReported.end()){
            isReported.insert({to,from});
            umap.insert({to,from});
        }
    }
    std::map<string,int> userMap;
    for(int i=0;i<id_list.size();i++)
        userMap.insert({id_list[i],i});
    for(string id:id_list){
        if(umap.count(id)>=k){
            auto iter=umap.find(id);
            for(int i=0;i<umap.count(id);i++,iter++){
                int index=userMap.find(iter->second)->second;
                answer[index]++;
            }
        }
    }
    return answer;
}