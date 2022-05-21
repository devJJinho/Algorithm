#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/*

@author  :  Jinho Jeong
@date    :  2022.05.21

*난이도 : Level2
*개인 풀이 시간 : 3 Hour
*개인 난이도 : 2/5 
*분류 : 문자열 , 구현
*풀이 : 

*느낀점 : 

*/

bool cmp(vector<int>& a , vector<int>& b){
    return a.size() < b.size();
}

//하니씩 차이나는 것을 찾는 것
int findDiff(vector<int>& a , vector<int> b){
    for(int n : a){
        for(int i = 0 ; i < b.size() ; i++){
            if(b[i] == n) {
                b[i] = -1;
                //중복이 가능하기 때문에 하나를 찾으면 바로 break;
                break;
            }
        }
    }
    // -1로 변하지 않은게 있다면 return
    for(int n : b)
        if(n != -1) return n;
}
vector<int> solution(string s) {
    vector<int> answer;
    s = s.substr(2 , s.size() - 4);
    vector<string> str;
    string token;
    vector<vector<int>> arr;
    // },{ 을 / 로 변환
    while(s.find("},{") != -1){
        s.replace(s.find("},{") , 3 , "/");
    }
    stringstream ss(s);
    // 변환 한 것을 바탕으로 자르기
    while(getline(ss , token , '/')){
        str.push_back(token);
    }
    // 쉼표를 기준으로 다시 자르기
    for(string line : str){
        stringstream ss(line);
        string token;
        vector<int> temp;
        while(getline(ss , token , ','))
            //스트링의 숫자화
            temp.push_back(stoi(token));
        arr.push_back(temp);
    }
    // 벡터의 길이를 기준으로 정렬
    sort(arr.begin() , arr.end() , cmp);
    // 길이 하나짜리가 가장 앞
    answer.push_back(arr[0][0]);
    // 그 뒤로는 하나씩 차이나는 것을 추가하기
    for(int i = 1 ; i < arr.size() ; i++){
        answer.push_back(findDiff(arr[i - 1] , arr[i]));
    }
    return answer;
}