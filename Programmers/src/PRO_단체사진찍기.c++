#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;

struct INFO{
    int nx, ineq, gap;
};
int dp[8][1<<8];
vector<INFO> hasR[8];
map<char,int> c;
int pre[8];

int recul(int stat, int idx){
    // int& ret = dp[idx][stat];
    // if(ret != -1) return ret;
    if(idx == 8) return 1;
    int ret = 0;
    for(int i = 0 ; i < 8 ; i++){
        if(stat & (1<<i)) continue;
        bool canGo = true;
        for(auto t : hasR[i]){
            int opp = t.nx;
            int gap = t.gap;
            int inq = t.ineq;
            if(pre[opp] == -1) continue;
            int dis = idx - pre[opp];
            --dis;
            if(inq == 0){
                if(dis == gap) continue;
                canGo = false;
                break;
            }
            else if(inq == 1){
                if(dis > gap) continue;
                canGo = false;
                break;
            }
            else{
                if(dis < gap) continue;
                canGo = false;
                break;
            }
        }
        if(!canGo) continue;
        pre[i] = idx;
        ret += recul(stat | (1<<i), idx + 1);
        pre[i] = -1;
    }
    return ret;
}

int solution(int n, vector<string> data) {
    int answer = 0;
    c={{'A',0},{'C',1},{'F',2},{'J',3},{'M',4},{'N',5},{'R',6},{'T',7}};
    // memset(dp, -1, sizeof(dp));
    memset(pre, -1, sizeof(pre));
    for(int i = 0 ; i < 8 ; i++)
        hasR[i].resize(0);
    for(string s : data){
        int a = c[s[0]];
        int b = c[s[2]];
        int gap = s[4]-'0';
        int inq;
        switch(s[3]){
            case '=' : inq = 0; break;
            case '>' : inq = 1; break;
            default : inq = 2;
        }
        hasR[a].push_back({b, inq, gap});
        hasR[b].push_back({a, inq, gap});
    } 
    answer = recul(0,0);
    return answer;
}

///////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

struct INFO{
    int nx, ineq, gap;
};
// int dp[8][1<<8];
vector<INFO> hasR[8];

int pre[8];
int convert(char a){
    switch(a){
        case 'A' : return 0;
        case 'C' : return 1;
        case 'F' : return 2;
        case 'J' : return 3;
        case 'M' : return 4;
        case 'N' : return 5;
        case 'R' : return 6;
        default : return 7;
    }
}

int recul(int stat, int idx){
    // int& ret = dp[idx][stat];
    // if(ret != -1) return ret;
    if(idx == 8) return 1;
    int ret = 0;
    for(int i = 0 ; i < 8 ; i++){
        if(stat & (1<<i)) continue;
        bool canGo = true;
        for(auto t : hasR[i]){
            int opp = t.nx;
            int gap = t.gap;
            int inq = t.ineq;
            if(pre[opp] == -1) continue;
            int dis = idx - pre[opp];
            --dis;
            if(inq == 0){
                if(dis == gap) continue;
                canGo = false;
                break;
            }
            else if(inq == 1){
                if(dis > gap) continue;
                canGo = false;
                break;
            }
            else{
                if(dis < gap) continue;
                canGo = false;
                break;
            }
        }
        if(!canGo) continue;
        pre[i] = idx;
        ret += recul(stat | (1<<i), idx + 1);
        pre[i] = -1;
    }
    return ret;
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    // memset(dp, -1, sizeof(dp));
    // memset(r, -1, sizeof(r));
    memset(pre, -1, sizeof(pre));
    for(int i = 0 ; i < 8 ; i++)
        hasR[i].resize(0);
    for(string s : data){
        int a = convert(s[0]);
        int b = convert(s[2]);
        int gap = s[4]-'0';
        int inq;
        switch(s[3]){
            case '=' : inq = 0; break;
            case '>' : inq = 1; break;
            default : inq = 2;
        }
        hasR[a].push_back({b, inq, gap});
        hasR[b].push_back({a, inq, gap});
    } 
    answer = recul(0,0);
    return answer;
}

#include <string>
#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

int dp[8][1<<8];
vector<int> hasR[8];
int r[8][8];
int inequal[8][8];
int pre[8];
int convert(char a){
    switch(a){
        case 'A' : return 0;
        case 'C' : return 1;
        case 'F' : return 2;
        case 'J' : return 3;
        case 'M' : return 4;
        case 'N' : return 5;
        case 'R' : return 6;
        default : return 7;
    }
}

int recul(int stat, int idx){
    int& ret = dp[idx][stat];
    if(ret != -1) return ret;
    if(idx == 8) return ret = 1;
    ret = 0;
    for(int i = 0 ; i < 8 ; i++){
        if(stat & (1<<i)) continue;
        bool canGo = true;
        for(int nx : hasR[i]){
            cout<<i<<" "<<nx<<endl;
            if(pre[nx] == -1) continue;
            int dis = idx - pre[nx];
            int gap = r[i][nx];
            int inq = inequal[i][nx];
            if(inq == 0){
                if(dis == gap) continue;
                canGo = false;
                break;
            }
            else if(inq == 1){
                if(dis > gap) continue;
                canGo = false;
                break;
            }
            else{
                if(dis < gap) continue;
                canGo = false;
                break;
            }
        }
        if(!canGo) continue;
        pre[i] = idx;
        ret += recul(stat | (1<<i), idx + 1);
        pre[i] = -1;
    }
    return ret;
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    memset(dp, -1, sizeof(dp));
    memset(r, -1, sizeof(r));
    memset(pre, -1, sizeof(pre));
    for(string s : data){
        int a = convert(s[0]);
        int b = convert(s[2]);
        int gap = s[4]-'0';
        int inq;
        switch(s[3]){
            case '=' : inq = 0; break;
            case '>' : inq = 1; break;
            default : inq = 2;
        }
        hasR[a].push_back(b);
        r[a][b] = gap;
        inequal[a][b] = inq;
    } 
    answer = recul(0,0);
    return answer;
}


#include <cstring>
#include <vector>

using namespace std;

int dp[8][1<<8];
vector<int> hasR[8];
int r[8][8];
int inequal[8][8];

int convert(char a){
    switch(a){
        case 'A' : return 0;
        case 'B' : return 1;
        case 'F' : return 2;
        case 'J' : return 3;
        case 'M' : return 4;
        case 'N' : return 5;
        case 'R' : return 6;
        default : return 7;
    }
}

int recul(int stat, int idx){
    int& ret = dp[idx][stat];
    if(ret != -1) return ret;
    ret = 0;
    for(int i = 0 ; i < 8 ; i++){
        if(stat & (1<<i)) continue;
        bool contain = !include[idx].size();
        for(int inc : include[idx]){
            if(inc == i){
                contain = true;
                break;
            }
        }
        if(!contain) continue;
        contain = false;
        for(int exc : exclude[idx]){
            if(exc == i){
                contain = true;
                break;
            }
        }
        if(contain) continue;
        for(int nx : hasR[i]){
            int inq = inequal[i][nx];
            int gap = r[i][nx];
            if(inq == 0){
                int nx = i + gap;
                if(nx >= 8) continue;
                for()
            }
            else if(inq == 1){
                
            }
            else{
                
            }
        }
        
    }
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    memset(dp, -1, sizeof(dp));
    memset(r, -1, sizeof(relation));
    for(string s : data){
        int a = convert(s[0]);
        int b = convert(s[2]);
        int gap = stoi(s[4]);
        int inq;
        switch(s[3]){
            case '=' : inq = 0; break;
            case '>' : inq = 1; break;
            default : inq = 2;
        }
        hasR[a].push_back(b);
        hasR[b].push_back(a);
        r[a][b] = r[b][a] = gap;
        inequal[a][b] = inequal[b][a] = inq;
    } 
    return answer;
}