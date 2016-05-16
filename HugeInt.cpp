#include "HugeInt.h"
#include <cstdlib>
#include <sstream>

HugeInt::HugeInt(){
	arrsize=2;
	int_arr = new int[arrsize];
	for(int i=0;i<arrsize;++i)
		int_arr[i]=0;
	minus=false;
}

HugeInt::HugeInt(int size,int num){
	arrsize=size;
	int_arr = new int[arrsize];
	for(int i=0;i<arrsize;++i)
		int_arr[i]=num;
	minus=false;
}

HugeInt::HugeInt(int a){
	arrsize=2;
	int_arr = new int[arrsize];
	int_arr[0] = a/100000;
	int_arr[1] = a%100000;
	minus=false;
}

HugeInt::HugeInt(string str){ 
	
	if(str.size()%5==0){
		arrsize=str.size()/5;
	}else{
		arrsize=str.size()/5+1;
	}
	int_arr = new int[arrsize];
	string str_arr[arrsize];
	int arr[arrsize-1];
	for(int i=0;i<arrsize-1;++i){
		arr[i]=str.size()-5*(i+1);
	}
	for(int i=0;i<arrsize;++i){
		if(i==0){
			str_arr[i]=str.substr(0,arr[arrsize-2]);
		}else{
			str_arr[i]=str.substr(arr[arrsize-1-i],5);
		}
	}
	for(int i=0;i<arrsize;++i){
		istringstream is(str_arr[i]);
		is >> int_arr[i];
	}
	minus=false;
}

HugeInt& HugeInt::operator=(const HugeInt &huge){
		
		delete []int_arr;
		arrsize = huge.arrsize;
		int_arr = new int[huge.arrsize];
		
		for(int i=0;i<huge.arrsize;++i){
			int_arr[i]=huge.int_arr[i];
		}
	
	return *this;
}

HugeInt HugeInt::operator+(const HugeInt& huge){
	int diff;
	HugeInt a(arrsize,0);
	HugeInt b(huge.arrsize,0);

	if(arrsize>=huge.arrsize){	
		diff=arrsize-huge.arrsize;
		for(int i=0;i<diff;++i){
			a.int_arr[i]=int_arr[i];
		}
		for(int i=diff,j=0;i<arrsize;++i,++j){
			a.int_arr[i]=int_arr[i]+huge.int_arr[j];
		}
		return a;
	}else{
		diff=huge.arrsize-arrsize;	
		for(int i=0;i<diff;++i){
			b.int_arr[i]=huge.int_arr[i];
		}
		for(int i=diff,j=0;i<huge.arrsize;++i,++j){
			b.int_arr[i]=huge.int_arr[i]+int_arr[j];
		}
		return b;
	}
}

HugeInt HugeInt::operator-(const HugeInt& huge){
	int diff;
	bool bigger=true;
	HugeInt a(arrsize,0);
	HugeInt b(huge.arrsize,0);

	if(arrsize>huge.arrsize){	
		diff=arrsize-huge.arrsize;
		for(int i=0;i<diff;++i){
			a.int_arr[i]=int_arr[i];
		}
		for(int i=diff,j=0;i<arrsize;++i,++j){
			a.int_arr[i]=int_arr[i]-huge.int_arr[j];
		}
		return a;
	}else if(arrsize<huge.arrsize){
		diff=huge.arrsize-arrsize;	
		minus=true;
		for(int i=0;i<diff;++i){
			b.int_arr[i]=huge.int_arr[i];
		}
		for(int i=diff,j=0;i<huge.arrsize;++i,++j){
			b.int_arr[i]=huge.int_arr[i]-int_arr[j];
		}
		return b;
	}else{
		if(int_arr[0]<huge.int_arr[0]){
			bigger=false;
		}else if(int_arr[0]==huge.int_arr[0] && int_arr[1]<huge.int_arr[1]){
			bigger=false;
		}else if(int_arr[0]==huge.int_arr[0] && int_arr[1]==huge.int_arr[1] && int_arr[2]<huge.int_arr[2]){
			bigger=false;
		}else if(int_arr[0]==huge.int_arr[0] && int_arr[1]==huge.int_arr[1] && int_arr[2]==huge.int_arr[2] && int_arr[3]<huge.int_arr[3]){
			bigger=false;
		}else if(int_arr[0]==huge.int_arr[0] && int_arr[1]==huge.int_arr[1] && int_arr[2]==huge.int_arr[2] && int_arr[3]==huge.int_arr[3] && int_arr[4]<huge.int_arr		[4]){
			bigger=false;
		}
	if(bigger==true){
		for(int i=0;i<arrsize;++i){
			a.int_arr[i]=int_arr[i]-huge.int_arr[i];
		}
		return a;
	}else{
		for(int i=0;i<huge.arrsize;++i){
			b.int_arr[i]=huge.int_arr[i]-int_arr[i];
		}
		b.int_arr[0]=(-1)*(b.int_arr[0]);
		return b;
	}
	
	}

}


ostream &operator<<(ostream &out, HugeInt& huge){
	string str_arr[huge.arrsize];
	
	for(int i=1;i<huge.arrsize;++i){
			if(huge.int_arr[i]>99999){
				huge.int_arr[i-1]+=huge.int_arr[i]/100000;
				huge.int_arr[i]=huge.int_arr[i]%100000;
			}
		
			if(huge.int_arr[i]<0){
				huge.int_arr[i-1]--;
				huge.int_arr[i]+100000;
			}
	}
	for(int i=0;i<huge.arrsize;++i){
		stringstream ss;
		ss << huge.int_arr[i];
		str_arr[i] = ss.str(); 
	}
	for(int i=1;i<huge.arrsize;++i){
		if(str_arr[i].size()==4){
			str_arr[i]="0"+str_arr[i];
		}else if(str_arr[i].size()==3){
			str_arr[i]="00"+str_arr[i];
		}else if(str_arr[i].size()==2){
			str_arr[i]="000"+str_arr[i];
		}else if(str_arr[i].size()==1){
			str_arr[i]="0000"+str_arr[i];
		}
	}
	huge.answer="";
	if(huge.minus==true){
		huge.answer="-";
	}
	
	for(int i=0;i<huge.arrsize;++i){
		huge.answer+=str_arr[i];
	}
	out << huge.answer;

	return out;

}

istream &operator>>(istream &in,HugeInt& huge){
	string str;
	in >> str;
	delete []huge.int_arr;
	if(str.size()%5==0){
		huge.arrsize=str.size()/5;
	}else{
		huge.arrsize=str.size()/5+1;
	}
	huge.int_arr = new int[huge.arrsize];
	string str_arr[huge.arrsize];
	if(huge.arrsize>1){
		int arr[huge.arrsize-1];
	
		for(int i=0;i<huge.arrsize-1;++i){
			arr[i]=str.size()-5*(i+1);
		}
		for(int i=0;i<huge.arrsize;++i){
			if(i==0){
				str_arr[i]=str.substr(0,arr[huge.arrsize-2]);
			}else{
				str_arr[i]=str.substr(arr[huge.arrsize-1-i],5);
			}
		}
	}else if(huge.arrsize==1){
		str_arr[0]=str.substr(0,str.size());
	}
	for(int i=0;i<huge.arrsize;++i){
		istringstream is(str_arr[i]);
		is >> huge.int_arr[i] ;
	}
	return in;
}
