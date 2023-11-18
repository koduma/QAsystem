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
#include <mecab.h>

using namespace std;

#define CODE_LENGTH 1000
#define TURN 1000

unordered_map<string,int>word;
unordered_map<int,string>unword;
unordered_map<int,int>prob;
multimap<int,int>words;
unordered_map<string,int>dp;

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

struct nod{
int cur;
unordered_map<int, int>v;
string str;
double ev;
int length;
int prev;
vector<int>history;
};

string ans;

int LP[CODE_LENGTH+5][CODE_LENGTH+5];

double sum=0;

double hit_distance(string x,string y,int mode){
	
	ofstream fi("y.txt");
	fi<<y;
	fi.close();
	if(mode==1){
	system("python3 mecab.py");//一般含まない
	}
	else if(mode==0){
	system("python3 mecab2.py");//一般含む
	}
	int d2=0;
    
	FILE *file;
	file = fopen("score.txt", "r");
	fscanf(file, "%d", &d2);
	fclose(file);

    return (double)d2;
    
}

double edit_distance(string x,string y){
	
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

 

    /*

    unordered_map<string,int>dic_x;

    MeCab::Tagger *tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(x.c_str());

    char surface[1000];
    char surface2[1000];
    for (; node; node = node->next) {
        memset(surface, 0, 1000);
        memcpy(surface, node->surface, node->length);
        string s=surface;
        memset(surface2,0,1000);
        memcpy(surface2,node->feature,1000);
        int comma=0;
        string hinshi,ippan;
        for(int i=0;i<1000;i++){
        if(surface2[i]==','){
        comma++;
        if(comma>=2){break;}
        continue;
        }    
        if(comma==0){hinshi+=string({surface2[i]});}
        if(comma==1){ippan+=string({surface2[i]});}
        }
        if(mode==0){
        if(hinshi=="名詞"&&ippan=="一般"){
            dic_x[s]++;
            //cout<<s<<",score="<<dic_x[s]<<endl;
        }
        }
        else if(mode==1){
            dic_x[s]++;
        }
    }

    unordered_map<string,int>dic_y;

    const MeCab::Node* node2 = tagger->parseToNode(y.c_str());

    char surface3[1000];
    char surface4[1000];
    for (; node2; node2 = node2->next) {
        memset(surface3, 0, 1000);
        memcpy(surface3, node2->surface, node2->length);
        string s=surface3;
        memset(surface4,0,1000);
        memcpy(surface4,node2->feature,1000);
        int comma=0;
        string hinshi,ippan;
        for(int i=0;i<1000;i++){
        if(surface4[i]==','){
        comma++;
        if(comma>=2){break;}
        continue;
        }    
        if(comma==0){hinshi+=string({surface4[i]});}
        if(comma==1){ippan+=string({surface4[i]});}
        }
        if(mode==0){
        if(hinshi=="名詞"&&ippan=="一般"){
            dic_y[s]++;
        }
        }
        else if(mode==1){
            dic_y[s]++;
        }
    }


    for(auto itr = dic_x.begin(); itr != dic_x.end(); ++itr) {
	for(auto itr2 = dic_y.begin(); itr2 != dic_y.end(); ++itr2) {
        if(itr->first==itr2->first){d2+=(dic_x[itr->first]);}
    }    
	}
    */
    
    double d3=(double)(LP[(int)x.size()][(int)y.size()]);
    
    return d3;

}

void calc_words(){
    string ls,st;
    ifstream myf("zzz_dict.txt");
    st="";
    int row=1;    
    while(getline(myf,ls)){
        string st="";
        for(int i=0;i<(int)ls.size();i++){
            if(ls[i]==','){
                words.emplace(row,stoi(st));
                st="";
                continue;
            }
            st+=ls[i];
        }
        words.emplace(row,stoi(st));
        row++; 
    }
    
    ifstream myf2("yyy_dict.txt");
    st="";
    row=1;
    while(getline(myf2,ls)){
        string st="";
        for(int i=0;i<(int)ls.size();i++){
            st+=ls[i];
        }
        unword[row]=st;
        word[st]=row;
        row++;
    }
    ifstream myf3("prob.txt");
    st="";
    row=1;
    while(getline(myf3,ls)){
        string st="";
        for(int i=0;i<(int)ls.size();i++){
            st+=ls[i];
        }
        prob[row]=stoi(st);
        row++;
    }
    
    for (auto itr = prob.begin(); itr != prob.end(); ++itr){
    sum+=(double)prob[itr->second];
    }
    unword[word["["]]="";
    unword[word["]"]]="";
    unword[word["{"]]="";
    unword[word["}"]]="";
    unword[word["'"]]="";
    unword[68]="";
    unword[50]="";
    unword[51]="";
    unword[102]="";
    unword[103]="";
    unword[110]="";
    unword[59]="";
    unword[106]="";
    unword[107]="";
    unword[84]="";
    unword[128]="";
    unword[268]="";
    unword[269]="";
    unword[302]="";
    unword[92]="";
    unword[287]="";
    unword[1241]="";
    unword[126]="";
    unword[132]="";
    unword[38]="";
    unword[272]="";
    unword[129]="";
    unword[281]="";
    unword[3353]="";
    unword[1058]="";
    unword[286]="";
    unword[4102]="";
    unword[3353]="";
    unword[7728]="";
    unword[5365]="";
    unword[2626]="";
    unword[1734]="";
    unword[1250]="";
    unword[144]="";
    
    ifstream my("dp.txt");
    ls="";
    while(getline(my,ls)){
        st="";
        int comma=0;
        int a[3]={0};
        for(int i=0;i<(int)ls.size();i++){
            if(ls[i]==','){
                a[comma]=stoi(st);
                st="";
                comma++;
                continue;
            }
            st+=ls[i];
        }
        dp[to_string(a[0])+","+to_string(a[1])]=stoi(st);
        if(stoi(st)>0&&a[0]==1){
            //cout<<a[0]<<","<<a[1]<<","<<stoi(st)<<endl;
        }
    }
    
}

/*

nod BEAM_SEARCH(nod n) {
	vector<nod>dque;
	dque.push_back(n);

	nod bestAction=n;
	
	double maxvalue=-1000000;

	//2手目以降をビームサーチで探索
	for (int i = 0; i < TURN; i++) {
		int ks = (int)dque.size();
		vector<nod>vn;
		for (int k = 0; k < ks; k++) {
			nod temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=5){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
				nod cand = temp;
				string s=unword[it->second];
				if(unword[it->second]==""){unword[it->second]=" ";}
				if(it->second==0){cand.ev=0;}
				cand.cur=it->second;
				cand.str=cand.str+unword[it->second];
				cand.ev=cand.ev+(double)prob[it->second];
				vn.push_back(cand);
			}
		}
		printf("depth=%d/%d\n",i+1,TURN);
		dque.clear();
		vector<pair<int,int> >vec;
		bool congrats=false;
		for (int j = 0; j < (int)vn.size(); j++) {
		vec.push_back(make_pair(-vn[j].ev,j));
		}
		sort(vec.begin(),vec.end());
		int push_node=0;
		for (int j = 0; push_node < 100 ;j++) {
			if(j>=(int)vec.size()){break;}
			int x=vec[j].second;
			nod temp = vn[x];
			if(temp.ev>maxvalue){
			maxvalue=temp.ev;
			bestAction=temp;   
			}
			if (i < TURN) {
				dque.push_back(temp);
				push_node++;
			}
		}
	}
	return bestAction;
}
*/

nod BEAM_SEARCH(nod n) {
	
	vector<nod>dque;
	dque.push_back(n);

	nod bestAction=n;
	double maxvalue=-1000000;

	//2手目以降をビームサーチで探索
	for (int i = 0;i<TURN; i++) {
		int ks = (int)dque.size();
		vector<nod>vn;
		for (int k = 0; k < ks; k++) {
			nod temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=5){continue;}
			auto p = words.equal_range(temp.cur);
			int m=0;
			for (auto it = p.first; it != p.second; ++it) {
			m++;
			if(dp[to_string(temp.prev)+","+to_string(it->second)]==0){continue;}
			if(m>=100000){break;}
			if((temp.v)[it->second]>=1){continue;}    
			nod cand = temp;
			string s=unword[it->second];    
			if(s==""||(it->second==0)){continue;}    
			cand.cur=it->second;   
			cand.str=cand.str+unword[it->second];    
			int a=(int)cand.str.size()-(int)unword[it->second].size();
			int b=(int)unword[it->second].size();
			if(a<0){a=0;}
			if(a>(int)ans.size()){a=(int)ans.size();}
			if(a+b>(int)ans.size()){b=(int)ans.size()-a;}
			if(b<0){b=0;} 
			string x=ans.substr(a,b);                
			string y=unword[it->second];
			double diff=edit_distance(x,y);
			if(diff<=1){    
			cand.ev+=(-diff)+hit_distance(x,y,1)*10000.0+(double)((i+1)*100000)+(double)(prob[it->second]/sum)+(double)dp[to_string(cand.prev)+","+to_string(it->second)];
			//cout<<"prob="<<prob[it->second]<<",dp="<<dp[to_string(cand.prev)+","+to_string(it->second)]<<endl;    
			cand.prev=it->second;
			cand.history.push_back(it->second);    
			vn.push_back(cand);
			}    
			}
		}
		printf("depth=%d/%d\n",i+1,TURN);
		dque.clear();
		vector<pair<int,int> >vec;
		for (int j = 0; j < (int)vn.size(); j++) {
		vec.push_back(make_pair(-vn[j].ev,j));
		}
		sort(vec.begin(),vec.end());
		int push_node=0;
		for (int j = 0; push_node < 10;j++) {
			if(j>=(int)vec.size()){break;}
			int x=vec[j].second;
			nod temp = vn[x];
			if(temp.ev>maxvalue){
				maxvalue=temp.ev;
				bestAction=temp;
				cout<<temp.str<<endl;
				for(int h=0;h<(int)temp.history.size();h++){
				cout<<temp.history[h]<<"->";
				}
				cout<<endl;
			}
			if (i < TURN) {
				dque.push_back(temp);
				push_node++;
			}
		}
		if(i==(int)ans.size()-1){return bestAction;}
	}
	return bestAction;
}
/*

nod BEAM_SEARCH2(nod n) {
	
	vector<nod>dque;
	dque.push_back(n);

	nod bestAction=n;
	
	double maxvalue=-1000000;

	//2手目以降をビームサーチで探索
	for (int i = 0;i<TURN; i++) {
		int ks = (int)dque.size();
		vector<nod>vn;
		for (int k = 0; k < ks; k++) {
			nod temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=2){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
			nod cand = temp;
			string s=unword[it->second];    
			if(s==""||(it->second==0)){continue;}
			cand.cur=it->second;   
			cand.str=cand.str+unword[it->second];    
			nod n2=BEAM_SEARCH(cand);
			int a=(int)cand.str.size()-(int)unword[it->second].size();
			int b=(int)unword[it->second].size();
			if(a<0){a=0;}
			if(a>(int)ans.size()){a=(int)ans.size();}
			if(a+b>(int)ans.size()){b=(int)ans.size()-a;}
			if(b<0){b=0;} 
			string x=ans.substr(a,b);                
			string y=unword[it->second];
			double diff=distance(x,y,1);
			cand.ev=(-diff*100.0)+n2.ev;    
			vn.push_back(cand);    
			}
		}
		printf("B2,depth=%d/%d\n",i+1,TURN);
		dque.clear();
		vector<pair<int,int> >vec;
		for (int j = 0; j < (int)vn.size(); j++) {
		vec.push_back(make_pair(-vn[j].ev,j));
		}
		sort(vec.begin(),vec.end());
		int push_node=0;
		bool congrats=false;
		for (int j = 0; push_node < 10;j++) {
			if(j>=(int)vec.size()){break;}
			int x=vec[j].second;
			nod temp = vn[x];
			if(temp.ev>maxvalue){
				maxvalue=temp.ev;
				bestAction=temp;
				cout<<temp.str<<endl;
    				for(int h=0;h<(int)temp.history.size();h++){
                    		cout<<temp.history[h]<<"->";
		      		}
                		cout<<endl;
				congrats=true;
			}
			if (i < TURN) {
				dque.push_back(temp);
				push_node++;
			}
		}
		if(!congrats||i==(int)ans.size()-1){return bestAction;}
	}
	return bestAction;
}

*/

int main(){
	
	calc_words();
    
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
    
    
	double mind=1000000;
	int find=-1;
	int dir=-1;
    
	//for(int j=1;j<=15;j++){
	//for(int i=((j-1)*4000);i<=(j*4000);i++){
	for(int j=12;j<=12;j++){
        for(int i=44308;i<=44308;i++){
	string s=to_string(i);
	ifstream myfile ("dir"+to_string(j)+"/"+s+"_q.txt");
	ifstream myfile2 ("dir"+to_string(j)+"/"+s+"_a.txt");
	if( (!myfile) || (!myfile2)) {continue;}
	string line;
	string t_path="";
	while(getline(myfile,line)){
	t_path+=line;    
	myfile.close();
	}
	while(1){
	if((int)t_path.size()<CODE_LENGTH){t_path+="@";}
	else{break;}
	}
	if((int)start.size()>CODE_LENGTH){start=start.substr(0,CODE_LENGTH);}
	if((int)t_path.size()>CODE_LENGTH){t_path=t_path.substr(0,CODE_LENGTH);}    
	double d=edit_distance(start,t_path);
	d-=100.0*hit_distance(start,t_path,0);        
	if((int)t_path.size()>CODE_LENGTH){d=1000000;}    
	if(mind>d){mind=d;find=i;dir=j;cout<<"dir="<<dir<<",i="<<i<<",d="<<d<<",mind="<<mind<<",find="<<find<<endl;}
	}
	}

	
	string line;
	string tmp="";
	string t_path="";
	ifstream myfile ("dir"+to_string(dir)+"/"+to_string(find)+"_a.txt");
	while(getline(myfile,line)){
	if(line!=""){    
	t_path+=line+'@';
	if(tmp==""){tmp=line;}
	}    
	}
	myfile.close();
	ans=t_path;
	cout<<find<<"_a.txt"<<endl;
	
	ofstream fiv("z.txt");
	fiv<<tmp;
	fiv.close();
	system("python3 test3.py");
	
	ifstream mi("w.txt");
	while(getline(mi,line)){
	tmp=line;
	bool ok=false;
	auto p = words.equal_range(word[tmp]);
	for (auto it = p.first; it != p.second; ++it) {
        ok=true;
        break;
	}
	if(ok){break;}
	}
	remove("w.txt");
	string rrr;
	int cur;
	cur=word[tmp];    
	unordered_map<int, int>v2;
	nod n;
	n.cur=cur;
	n.v=v2;
	n.str=unword[cur];
	n.ev=0;
	n.prev=cur;
	n.history.push_back(cur);
	n=BEAM_SEARCH(n);
	for(int i=0;i<(int)n.str.size();i++){
	if(n.str[i]=='@'){n.str[i]='\n';}
	}
	cout<<n.str<<endl;
    
	return 0;
}
