#include <vector>
#include <cfloat>
#include <cstdio>
#include <cstring>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <random>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>    

using namespace std;

#define CODE_LENGTH 1000

unordered_map<string,int>word;
unordered_map<int,string>unword;
unordered_map<int,int>prob;
multimap<int,int>words;
unordered_map<string,bool>history;

string output;

double d_rnd() {
	static mt19937 mt((int)time(0));
	uniform_real_distribution<double> dice(0.0, 1.0);
	return dice(mt);
}
int rnd(int mini, int maxi) {
	static mt19937 mt((int)time(0));
	uniform_int_distribution<int> dice(mini, maxi);
	return dice(mt);
}

struct node{
int cur;
unordered_map<int, int>v;
string str;
int ev;
int length;    
};

string ans;

int LP[CODE_LENGTH+5][CODE_LENGTH+5];

int distance(string x,string y){
  
  int j,k;
    
  memset(LP,0,sizeof(LP));  
    
  for(j=1;j<=(int)x.size();j++) LP[j][0] = j;
  for(k=1;k<=(int)y.size();k++) LP[0][k] = k;

  for(j=1;j<=(int)x.size();j++) {
    for(k=1;k<=(int)y.size();k++) {
      int m = min(LP[j-1][k]+1, LP[j][k-1]+1);
      if(x[j-1] == y[k-1]) {
        m = min(m,LP[j-1][k-1]);
        LP[j][k] = m;
      }else {
        m = min(m,LP[j-1][k-1]+1);
        LP[j][k] = m;
      }
    }
  }
	
ofstream fi("y.txt");
fi<<y;
fi.close();
system("python3 mecab.py");
int d2;
FILE *file;
file = fopen("score.txt", "r");
fscanf(file, "%d", &d2);
fclose(file);
cout<<d2<<endl;
return LP[(int)x.size()][(int)y.size()]-(d2*100);

}
int main(){
	
	string start;
	
	getline(cin, start,'$');
	while(1){
	bool escape=true;
	for(int i=0;i<(int)start.size();i++){
        if(start[i]=='\n'){start.erase(i, 1);escape=false;break;}
	}
	if(escape){break;}
	}
	
	ofstream fi("x.txt");
	fi<<start;
	fi.close();
    
    
	int mind=1000000;
	int find=-1;
    
	for(int i=0;i<=2525;i++){
	string s=to_string(i);
	ifstream myfile (s+"_q.txt");    
	if( !myfile ) {continue;}
	string line;
	string t_path="";
	while(getline(myfile,line)){
	t_path+=line;    
	}
	myfile.close();
	while(1){
	if((int)t_path.size()<CODE_LENGTH){t_path+="@";}
	else{break;}
	}   
	int d=distance(start,t_path);
	if((int)t_path.size()>CODE_LENGTH){d=1000000;}    
	if(mind>d){mind=d;find=i;}
	cout<<"i="<<i<<",d="<<d<<endl;
	}
	
	string line;
	string tmp="";
	string t_path="";
	ifstream myfile (to_string(find)+"_a.txt");
	while(getline(myfile,line)){
	if(line!=""){    
	t_path+=line+'@';
	if(tmp==""){tmp=line[0];}
	}    
	}
	myfile.close();
	ans=t_path;
	cout<<find<<"_a.txt"<<endl;
	for(int i=0;i<(int)ans.size();i++){
	if(ans[i]=='@'){ans[i]='\n';}
	}
	cout<<ans<<endl;
    
	return 0;
}
