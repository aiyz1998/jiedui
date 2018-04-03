// jiedui.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <math.h>
#include <cstdlib>
#include <ctime>


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

//#include<string.h>


#define random(a,b) (rand()%(b-a+1)+a)
#define NUMSIZE 50
#define GEN 100

using namespace std;

typedef struct {
	//the node of string
	char c;
	int num;
	int flag;
	int frac[4];

}Node, NNode[NUMSIZE];

//definition of Node


//end definition


//definition of stack

typedef struct {
	int num[NUMSIZE];
	int stacksize;
	int top;

}Nsqstack;

void Ninitstack(Nsqstack &s) {
	int i = 0;
	for (i = 0; i<10; i++) s.num[i] = 0;
	s.stacksize = 10;
	s.top = -1;
	return;
}//end Ninitstack

void Ndestroystack(Nsqstack &s) {
	s.stacksize = 0;
	s.top = -1;
	return;
}//end Ndestroystack

int  Ngettop(Nsqstack s, int &a) {
	if (s.top == -1) return 0;
	a = s.num[s.top];
	return 1;
}//Ngettop

void Npush(Nsqstack &s, int a) {
	s.num[++s.top] = a;
	return;
}//end Npush

int Npop(Nsqstack &s, int &a) {
	if (s.top == -1) return 0;
	a = s.num[s.top];
	s.num[s.top--] = 0;
	return 1;
}//end Npop

bool Nstackempty(Nsqstack s) {
	if (s.top == -1) return true;
	else return false;
}//end Nstackempty

 //end Initialization of stack



int isoperator(char ch) {
	//judge if a char is operator or not
	int m = 0;
	switch (ch) {
	case '#':
	case 'q':
	case 'l'://ln
	case ')':
	case 't'://tan
	case 'a':
	case '^':
	case 'c'://cos
	case 's'://sin
	case '(':
	case '+':
	case '-':
	case '*':
	case '/': m = 1; break;
	default:m = 0;

	}
	return m;
}

int cal(int a, int b, char ch) {
	//function of calculation
	int c = 0;
	switch (ch) {
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a*b;
	case '/':return a / b;// ********
	case '^':return pow(a, b);//********
	}
}//end cal



void getf(char *&p, char *q) {
	//capture the number(able to get double)
	//46 is '.'
	char *temp = q;
	int k = 1;
	if (*p<48 && *p>57) return;
	while (*p == 46 || *p >= 48 && *p <= 57) {
		*temp = *p;
		p++, temp++;
	}

	*temp = '\0';
}//end getf




int preop(char a, char b) {
	//-1,0,1 means the priority of a is smaller/equal_to/larger than b
	//-2 means error
	if (a == '+' || a == '-') {
		if (b == '*' || b == '/' || b == '(' || b == '^') return -1;
		else return 1;
	}
	if (a == '*' || a == '/') {
		if (b == '(' || b == '^') return -1;
		else return 1;
	}
	if (a == '(') {
		if (b == ')') return 0;
		else if (b == '#') return -2;
		else return -1;
	}
	if (a == ')') {
		if (b == '(')return -2;
		else return 1;
	}
	if (a == '^') {
		if (b == '(') return -1;
		else return 1;
	}
	if (a == '#') {
		if (b == ')') return -2;
		else if (b == '#') return 0;
		else return -1;
	}
}//end preop

bool srand_generator(int inf,int sup,int div) {
	//set the srand generator
	int j = 0;
	j = random(inf, sup);
	if (j < div) return false;
	else return true;
}//end srand_generator

int srand_generator(int div) {
	//set the srand generator
	int j = 0;
	j = random(1, GEN);
	int beg = 0;
	int temp = 100 / div;
	int result = 0;
	for (; result<=100; ) {
		result += temp;
		if (j <= result&&j > result - temp)
			break;
		else beg++;	
	}//end for
	return beg;

}//end srand_generator

void init_suffix(Node& suffix) {
	suffix.c = '\0';
	suffix.num = 0;
	suffix.flag = -1;
	for (int i = 0; i <= 3; i++) {
		suffix.frac[i] = 0;
	}
	return;
}//end init_suffix


void set_suffix(Node& suffix,int inf,int sup,int symbol,char* oper) {
	//set_suffix:setting char/num/fraction with differernt value of para sybol
	//case 0:num case 1: char case 2:fraction
	//inf: the inferior bound,sup: the superior bound
	//oper: the set of operator
	switch (symbol) {
	case 0:
		//set num
		suffix.num = random(inf, sup);
		suffix.flag = 0;
		break;
	case 1:
		//set char
		int len_oper = strlen(oper);
		suffix.flag = 1;
		suffix.c = oper[random(0, len_oper - 1)];
		break;
	case 2:
		//set fraction
		//(optional)using suffix.frac[0] to get the sup bound of the first num
		suffix.flag = 2;
		for (int i = 1; i <= 3; i++) {
			suffix.frac[i] = random(inf, sup);
		}
		break;
	case 3:
		//optional: set the double
		break;

	}//end switch

}//end set_suffix

void suffix_generator(NNode &suffix,char* oper,int symbol) {
	//generate the suffix erpression

	int i = 0, j = 0, k = 0;// invariable of count
	bool flag = 0;			// flag of generating operator or num

	int sup = 20;// the superior bound of the num
	int inf = 1; // the inferior bound of the num

	int count_num  = 0; //the number of num in the experssion
	int count_oper = 0; //the number of operator in the experssion

	int inf_len = 5;//the inferior bound of the length of expression
	int sup_len = 9;//the superior bound of the length of expression
	
	int len_oper = strlen(oper);		 //the length of the operator set
	int length = random(inf_len,sup_len);//the length of the exp,randomized

	//end definition

	if (length % 2 == 0) length++;
	
	//initialization
	suffix[0].flag = 2;    //2 ************* 2means begin
	suffix[0].num = length;//store the length
	//end initialization


	switch (symbol) {
	case 0:

		suffix[1].num = random(inf, sup);
		suffix[1].flag = 0;
		suffix[2].num = random(inf, sup);
		suffix[2].flag = 0;
		count_num = 2;
		i = 3;

		while (count_num < (1 + (length - 1) / 2)) {
			if (count_num <= count_oper + 1) {
				//the prefix is full(n numbers and n-1 operators)
				suffix[i].flag = 0;
				suffix[i++].num = random(inf, sup);
				count_num++;
			}//end if
			else if (count_oper == ((length - 1) / 2 - 1)) {
				//if there is almost done，then num should not be the last
				suffix[i].flag = 0;
				suffix[i++].num = random(inf, sup);
				count_num++;
			}
			else {
				flag = srand_generator(inf, sup, (inf + sup) / 2);
				//generating num & operator with equal possibility
				if (flag == 0) {
					//generating the number
					suffix[i].flag = 0;
					suffix[i++].num = random(inf, sup);
					count_num++;
				}//end if
				else {
					//generating the operator
					suffix[i].flag = 1;
					suffix[i++].c = oper[random(0, len_oper - 1)];
					count_oper++;
				}//end else
			}//end else

		}//end while
		while (count_oper < (length - 1) / 2) {
			//fill the last operator
			suffix[i].flag = 1;
			suffix[i++].c = oper[random(0, len_oper - 1)];
			count_oper++;

		}//end while
	case 1:
		flag = srand_generator(inf, sup, (inf + sup) / 2);

		//if(flag==0){
		suffix[1].num = random(inf, sup);
		suffix[1].flag = 0;
		suffix[2].num = random(inf, sup);
		suffix[2].flag = 0;
		count_num = 2;
		i = 3;
		//end initialization

	case 2:


	}
	

	

	suffix[i].flag = -1;// not need

}//end suffix_generator

void node_out_file(fstream filename, Node suffix) {
	//f_out a node to the file
	if (suffix.flag == -1) return;
	else if (suffix.flag = 0) {
		filename << suffix.num << ' ';
	}//end elseif
	else {
		filename << suffix.c << ' ';
	}//end else
}//end node_out_file




int calculate(NNode suffix) {
	//calculate the suffix
	//未考虑分数，小数，真分数，返回整数
	//未考虑中间出现负数
	Nsqstack s;
	Ninitstack(s);
	int length = suffix[0].num;//the length of exp
	int len_num = (length + 1) / 2;
	int len_oper = (length - 1) / 2;

	if (length >= 3) {
		Npush(s, suffix[1].num);
		Npush(s, suffix[2].num);
	}
	else return -10000;

	int i = 3;
	int left = 0, right = 0;//left number and right number 
	char op = 0;			//operator
	int result = 0;			//result

	while (i<=length) {
		if (suffix[i].flag == 0) {
			//get a num
			Npush(s, suffix[i].num);
			i++;
		}//end if

		else if (suffix[i].flag == 1) {
			//get a operator
			Npop(s, right);
			Npop(s, left);
			op = suffix[i].c;
			result=cal(left, right, op);
			Npush(s, result);
			i++;
		}//end else if

	}//end while

	Npop(s, result);
	return result;

}//end calculate ,return int*********



int main()
{
	NNode suffix;
	int i = 0;
	int key = 0;//key is the result of suffix
	string dist = "C:/Users/38084/Documents/Visual Studio 2015/Projects/jiedui/jiedui/result.txt";
	string dist1 = "C:/Users/38084/Documents/Visual Studio 2015/Projects/jiedui/jiedui/key.txt";
	
	srand((unsigned)time(NULL));
	char* oper = "+-*";
	for (i = 0; i < NUMSIZE; i++) {
		init_suffix(suffix[i]);
	}
	fstream ofn(dist,ios::out);
	fstream ofn_key(dist1, ios::out);

	for (int j = 0; j < 100; j++) {
		suffix_generator(suffix, oper);
		ofn << j + 1 << "	";
		key=calculate(suffix);
		ofn_key << j + 1 << "	" << key << endl;
		for (i = 1; i <= suffix[0].num; i++) {
			if (suffix[i].flag == -1) break;
			else if (suffix[i].flag == 0) {

				ofn << suffix[i].num << ' ';
				cout << suffix[i].num << ' ';
			}//end elseif
			else {
				ofn << suffix[i].c << ' ';
				cout << suffix[i].c << ' ';
			}//end else
			
		}
		cout << endl;
		ofn << endl;

	}
	system("pause");
	return 0;
}//end main

