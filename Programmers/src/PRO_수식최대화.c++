#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#define ABS(a) ((a) < 0 ? -(a) : (a))
using namespace std;

bool selected[3];
char opp[3] = {'+' , '-' , '*'};
char defined[3];
map<char , int> mp;
string exp;
long long maxValue;
long long calc(vector<string>& a){
    stack<long long> st;
    //후위 연산자 순서대로 연산 진행
    for(string i : a){
        if(i == "+" || i == "*" || i == "-"){
            long long temp = st.top();
            st.pop();
            switch(i[0]){
                case '+' : temp += st.top(); break;
                case '-' : temp = st.top() - temp; break;
                case '*' : temp *= st.top(); 
            }
            st.pop();
            st.push(temp);
        }
        else{
            st.push(stoi(i));
        }
    }
    cout<<"res:"<<st.top()<<endl;
    return st.top();
}

void fac(int idx){
    if(idx == 3){
        //순열이 완성되면
        stack<int> ope;
        long long n = 0;
        vector<string> arr;
        // 아래부턴 후위 연산자를 만들기 위한 코드
        for(int i = 0 ; i <exp.length() ; i++){
            char c = exp[i];
            if(c >= '0' && c <= '9'){
                n = n * 10 + c - '0';
            }
            else{
                //숫자 완성되면 담기
                arr.push_back(to_string(n));
                n = 0;
                //비어있으면 담기
                if(ope.empty()){
                    ope.push(mp[c]);
                    continue;
                }
                if(ope.top() >= mp[c]){
                    while(!ope.empty()&& ope.top() >= mp[c]){
                    string ft;
                    ft += defined[ope.top()];
                    arr.push_back(ft);
                    ope.pop();
                    }
                    ope.push(mp[c]); 
                }
                else{
                    ope.push(mp[c]);
                }
            }
        }
        //마지막 숫자 담기
        arr.push_back(to_string(n));
        //남아있는 연산자 모두 붙이기. 순서는 stack에서 pop되는 순서대로
        while(!ope.empty()){
            string ft;
            ft += defined[ope.top()];
            arr.push_back(ft);
            ope.pop();
        }
        long long ret = calc(arr);
        ret = ABS(ret);
        if(maxValue < ret) maxValue = ret;
        return;
    }
    //순열 만드는 코드                        
    for(int i = 0 ; i < 3 ; i++){
        if(!selected[i]){
            selected[i] = true;
            //map에 없으면 삽입 
            //있으면 수정
            //만약 Insert만 연달아 수행하면 중복되는 것은 반영되지 않음
            if(mp.find(opp[idx]) != mp.end())
                mp[opp[idx]] = i;
            else
                mp.insert({opp[idx] , i});
            // map이 char로 우선 순위를 추적하는 용이라면 이것은 우선순위로 char를 추적하기 위한 역추역용
            defined[i] = opp[idx];
            fac(idx + 1);
            selected[i] = false;
        }
    }
}

long long solution(string expression) {
    exp = expression;
    maxValue = 0;
    fac(0);
    long long answer = maxValue;
    return answer;
}