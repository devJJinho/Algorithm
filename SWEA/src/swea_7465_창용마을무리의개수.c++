#include <iostream>
#include <vector>
using namespace std;

int getParent(vector<int> &mother,int a){
    if(mother[a]==a)
        return a;
    return mother[a]=getParent(mother,mother[a]);
}
int main(){
    int num;
    cin>>num;
    for(int cs=1;cs<=num;cs++){
        int n,m;
        int i;
        cin>>n>>m;
        vector<int> mother(n+1);
        for(i=0;i<mother.size();i++)
            mother[i]=i;
        for(int i=0;i<m;i++){
            int a,b;
            cin>>a>>b;
            a=getParent(mother,a);
            b=getParent(mother,b);
            if(a<b) mother[b]=a;
            else mother[a]=b;
        }
        vector<int> count(n+1,0);
        for(int i=1;i<mother.size();i++)
            count[mother[i]]++;
        int cnt=0;
        for(int i=1;i<count.size();i++){
            cout<<mother[i]<<" ";
            if(count[i]) cnt++;
        }   
        cout<<endl;
        cout<<"#"<<cs<<" "<<cnt<<endl;
    }
}