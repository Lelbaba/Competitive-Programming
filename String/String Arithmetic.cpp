
class str_num
{
public:
	string s;
	vector <int> v; // from lsd to msd
	str_num(string _s = "0") {
		s = _s;
		bool f = false;
		for(auto x:s){
			if(x=='-') {
				f = true;
				continue;
			}
			int num = x-'0'; 
			if(f) num*=-1;
			v.push_back(num);
		}
		reverse(v.begin(), v.end());
	}
	str_num(vector <int> &_v){
		v = _v;
		if(v.empty()) v = {0};
		if(v[v.size()-1]<0) s = "-";
		reverse(v.begin(), v.end());

		for(auto x:v) s+=char(abs(x)+'0');
		reverse(v.begin(), v.end());
	}
	void invert(){
		if(s[0]=='-') s = s.substr(1);
		else s = "-"+s;
		for(auto &e:v){
			e*=-1;
		}
	}
	bool operator < (str_num &rhs){
		if(s[0]!='-' && rhs.s[0]=='-') return false;
		if(s[0]=='-' && rhs.s[0]!='-') return true;
		if(s.size()< rhs.s.size()) return s[0]!='-';
		if(s.size()> rhs.s.size()) return s[0]=='-';
		for(int i=0;i<s.size();i++){
			if(s[i]<rhs.s[i]) return s[0]!='-';
			if(s[i]>rhs.s[i]) return s[0]=='-';
		}
		return false;
	}
	bool operator == (str_num &rhs) {
		return s==rhs.s;
	}
	bool operator <= (str_num &rhs){
		return *this==rhs || *this<rhs;
	}
	bool operator > (str_num &rhs){
		return (rhs<*this);
	}
	bool operator >= (str_num &rhs){
		return (rhs<=*this);
	}
	
	str_num operator + (str_num &rhs){
		int sz = max(v.size(),rhs.v.size());
		while(v.size()<sz) v.push_back(0);
		while(rhs.v.size()<sz) rhs.v.push_back(0);
		vector <int> Sum,Nsum;
		int carry = 0,ncarry = 0;
		for(int i=0;i<sz;i++){
			int sum = carry + v[i] + rhs.v[i];
			carry = 0;
			while(sum>9) { sum-=10,carry++;}
			while(sum<0) {sum+=10,carry--;}
			Sum.push_back(sum);
			int nsum = ncarry + v[i] + rhs.v[i];
			ncarry = 0;
			while(nsum>0) { nsum-=10,ncarry++;}
			while(nsum<-9){ nsum+=10,ncarry--;}
			Nsum.push_back(nsum);
		}
		if(carry>0) Sum.push_back(carry);
		if(ncarry<0) Nsum.push_back(ncarry);

		while(v.size()>1 && v.back()==0){
			v.pop_back();
		}
		while(rhs.v.size()>1 && rhs.v.back()==0){
			rhs.v.pop_back();
		}

		while(Sum.size()>1 && Sum.back()==0){
			Sum.pop_back();
		}
		while(Nsum.size()>1 && Nsum.back()==0){
			Nsum.pop_back();
		}
		if(carry>=0) return str_num(Sum);
		else return str_num(Nsum);
	}
	str_num operator - (str_num rhs){
		rhs.invert();
		return *this+rhs;
	}
	
};
