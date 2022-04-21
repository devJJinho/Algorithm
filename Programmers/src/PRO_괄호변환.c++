#include <string>
#include <vector>
#include <stack>
using namespace std;

string ans = "";
string str;
void recul(int idx){
    int cnt[2] = {0,0};
    stack<char> st;
    bool isError = false;
    for(int i = idx ; i < str.length() ; i++){
        if(str[i] == '('){
            cnt[0]++;
            st.push('(');
        }
        else{ 
            cnt[1]++;
            if(st.empty()) isError = true;
            else st.pop();
        }
        //만약에 균형잡힌 괄호라면
        if(cnt[0] == cnt[1]){
            //만약 올바른 괄호라면 그냥 추가
            if(!isError && st.empty()){
                for(int j = idx ; j <= i ; j++)
                    ans.push_back(str[j]);
                recul(i + 1);
            }
            else{
                //아니라면 재귀 수행하기
                ans.push_back('(');
                recul(i + 1);
                ans.push_back(')');
                string temp = "";
                for(int j = idx + 1 ; j < i ; j++){
                    if(str[j] == '(') temp += ')';
                    else temp += '(';
                }
                ans += temp;
            }
            return;
        }
    }
}

string solution(string p) {
    if(p == "") return "";
    str = p;
    recul(0);
    string answer = ans;
    return answer;
}