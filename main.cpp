/*
 * main.cpp
 *
 *  Created on: 2018年11月20日
 *      Author: User
 */




/*
 * main.cpp

 *
 *  Created on: 2018年11月19日
 *      Author: User
 */
#include <iostream>
#include <string>
#include <bitset>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;

void printexample(){
	cout<<"-------------------------------------"<<endl;
	cout<<"-Hamming generator by lam yiu tung  -"<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"input:(hamming code) (message) "<<endl;
	cout<<"output:(hamming code) \n      (correct message)"<<endl;
	cout<<"input:01011 ac "<<endl;
	cout<<"output:01011 \n      ab"<<endl;
}
void printintar(int size,int * array){
	for (int i=0 ;i<size ;i++){
		cout<<array[i];
	}
	cout<<endl;
}
void bittochararray(bitset<8> bit,char*temp,int pos){
	for(int i=0;i<8;i++){
	//	cout<<bit[i]<<endl;
		if(bit[i]==1){
			temp[pos*8-1+(8-i)]='1';

		}else{temp[pos*8-1+(8-i)]='0';}
	}
}
void chararraytobit(char*ans,char *temp,int bitarrlen){

	for(int j=0;j<bitarrlen/8;j++){
	bitset<8> bitarr ;
	for(int i=0 ; i< 8 ;i++){
		if(temp[i+j*8]=='1'){
			bitarr[7-i]=1;
		//	cout<<bitarr.to_string()<<endl;
		}else{
			bitarr[7-i]=0;
			//cout<<bitarr.to_string()<<endl;
		}
	}
	ans[j] = bitarr.to_ulong();
	//cout<<bitarr.to_ulong()<<endl;
	//cout<<char(ans[j])<<endl;
	}
}
void combparanddata(char *party ,int * pos ,char * data,char *out,int plen,int dlen){
	strcpy(out,data);
	//getline(data, out);
	char temp[dlen+plen];
	for(int i=0;i<plen;i++){

		if(i==0){
		strcpy(temp,data);
		}else{strcpy(temp,out);}
		out[pos[i]]=party[i];

		for(int j=pos[i];j<dlen+plen;j++){
			out[j+1]=temp[j];

		}
	}
}
void calparty(char * partyans,int * pos,int plen ,int dlen,char * hamchar){
	for(int i=0;i<plen ;i++){
		int messlen = dlen+plen ;
		int event =0;
		for (int j=(pos[i]);j<messlen;j+=((pos[i]+1)*2)){

			for(int k=0 ;k<=pos[i];k++){
				if(partyans[j+k]=='*'){continue;}
				//if(j==(pos[i]+1)*2){k++;}
				if(partyans[j+k]=='1'){

					event ++;
				}
			}
		}
		if(event%2==1){
		//partyans[pos[i]]='1';
		hamchar[i]='1';
		}else{
			//partyans[pos[i]]='0';
			hamchar[i]='0';
		}
	}

}
void finderror ( bool * check,int plen ,int dlen,char * partyans,int * pos){
char * errorpos = new char[plen+dlen];
int * errorposint = new int[plen+dlen];
int messlen = dlen+plen ;
for(int i=0;i<messlen;i++){
	errorpos[i]='*';
	errorposint[i]=-1;
}

for(int i=0;i<plen ;i++){
	for (int j=(pos[i]);j<messlen;j+=((pos[i]+1)*2)){

				for(int k=0 ;k<=pos[i];k++){
					if(partyans[j+k]=='*'){continue;}
					//if(j==(pos[i]+1)*2){k++;}
					if(i==0){
						if(check[i]==true){
							errorpos[j+k]='0';
							errorposint[j+k]=0;
							//printintar(plen+dlen,errorposint);
						}else if(check[i]==false && errorposint[j+k]!=0){
							errorpos[j+k]='0'+i;
							errorposint[j+k]=i+1;
							//printintar(plen+dlen,errorposint);
						}
					}else{
					if(check[i]==true){
						errorpos[j+k]='0';
						errorposint[j+k]=0;
						//printintar(plen+dlen,errorposint);
					}else if(check[i]==false && errorposint[j+k]!=0&&errorposint[j+k]!=-1){
						errorpos[j+k]='0'+i;
						errorposint[j+k]=i+1;
						//printintar(plen+dlen,errorposint);
					}
					}

				}
			}
		for(int z =0 ; z<messlen ;z++){
						if(errorposint[z]!=i+1 && (errorposint[z]!=-1 && check[i]==false)){
							errorposint[z]=0;
						}
					}
}
for(int i=0 ; i<messlen;i++){
	int max=plen;

	if(errorposint[i]==max){
		if(partyans[i]=='0'){partyans[i]='1';}else{partyans[i]='0';}
	//	cout<<"find"<<endl;
	}
}
}
void retrievedata(char* mess ,char * out ,int dlen ,int plen ){
	int messlen = plen + dlen;
	int datapos=0;
	for(int i=0;i<messlen;i++){
		if(mess[i]!='*'){
			out[datapos]=mess[i];
			datapos++;
		}
	}
}
int main(){
//	while(true){
	printexample();
	string partyinput="";
	string input="";
	string datainput="";
	cin>>partyinput;
	getline(std::cin, input);
	datainput=input.substr (1);
	int correct=0;
	int datasize = datainput.size();
	//cout<<datasize<<endl;
	int const actsize = datasize*8 ;
	char * databit=new char[actsize];
//	cout<<"databit size"<<actsize<<endl;
//	cout<<"databit size"<<strlen(databit)<<endl;
	int partylen = 0;
	while(pow(2,partylen)<datasize*8+partylen+1){
		partylen++;
	}
	char * mess = new char[datasize*8+partylen];
	for(int i=0;i<datasize*8+partylen;i++){
		mess[i]=' ';
	}
	int * hampos=new int[partylen];
	char * hamchar =new char[partylen];
	bool * checkparty = new bool[partylen];
	for(int i=0;i<partylen;i++){
		hamchar[i]='*' ;
	}

	for(int i=0;i<partylen;i++){
		hampos[i]=pow(2,i)-1;
//		cout<<hampos[i]<<endl;
	}

	for(size_t i=0;i<datainput.size();i++){
		bitset<8> temp =bitset<8>(datainput.c_str()[i]);
		bittochararray(temp,databit,i);
//		cout<<bitset<8>(input.c_str()[i])<<endl;

	}
//	for(int i=0;i<datasize*8;i++){
//	cout<<databit[i];}
//	cout<<endl;
//	cout<<partylen<<endl;
	combparanddata(hamchar,hampos,databit,mess,partylen,actsize);
//	for(int i=0;i<datasize*8+partylen;i++){
//		cout<<mess[i];}
//		cout<<endl;
	calparty(mess,hampos,partylen,actsize,hamchar);
//	for(int i=0;i<datasize*8+partylen;i++){
//		cout<<mess[i];}
//		cout<<endl;
	for(int i=0;i<partylen;i++){
		//cout<<hamchar[i];
		if(partyinput[i]!=hamchar[i]){
			correct++;
			//cout<<"GG";
			checkparty[i]=false;
		}else{
			checkparty[i]=true;
		}
	}
	char * ans = new char[actsize/8];
	if(correct==1){//mean party part is wrong
		for(int i=0;i<partylen;i++){
				cout<<hamchar[i];
			}
		cout<<endl;
		cout<<datainput<<endl;

	}else if(correct>1){//mean datainput is wrong
		finderror(checkparty,partylen,actsize,mess,hampos);
		calparty(mess,hampos,partylen,actsize,hamchar);
		cout<<partyinput<<endl;
//		for(int i=0;i<partylen+actsize;i++){
//				cout<<mess[i];
//			}
//			cout<<endl;
//			char * databit=new char[actsize];
//			char * correctmess= new char[actsize];
//			for(int i=0;i<actsize;i++){
//				correctmess[i]='0';
//			}
			retrievedata(mess ,databit ,actsize ,partylen );


					chararraytobit(ans,databit,actsize);
			//		cout<<bitset<8>(input.c_str()[i])<<endl;

					for(int i=0 ; i<actsize/8;i++){
						cout<<ans[i];
					}
					cout<<endl;

	}else if(correct==0){
		cout<<partyinput<<endl;
		cout<<datainput<<endl;
	}

	cout<<endl;
	//}
	return 0;
}

