#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "framework.h"
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
extern char output[50];
extern string OutPut;
using namespace std;
void Changestrs(string out, string in, string input);
bool isnumber(char c) {
	if (c >= '0' && c <= '9')return true;
	else return false;
}
bool islinenumber(string s, int beg) {
	for (int i = beg; i < s.size(); i++) {
		if (s[i] == 'x')return true;
	}
	return false;
}
bool isprevnumber(string s, int d) {
	for (int i = 0; i < d; i++) {
		if (isnumber(s[i]) == false)return false;
	}
	return true;
}
int step;
int isstep(string s, int beg) {
	for (int i = beg; i < s.size(); i++) {
		if (s[i] == '^')return 1;
	}
	return 0;
}
void FindDif(string input) {
	string out = "";
	string in = "";
	int pokasat = 0;
	int stepfunc = 0;
	int d = 0;
	int open = 0; int close = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '^') {
			if (input[i - 1] == 'x')continue;
			if (isprevnumber(input, i) == true && islinenumber(input, i + 1) == true) {
				pokasat = 1;
				break;
			}
			d = i;
			stepfunc = isstep(input, d);
			if (stepfunc == 0)break;
			input = '(' + input + ')';
			for (int j = 1; j <= d; j++) {
				in += input[j];
				out += input[j];
			}
			for (int k = d + 1; k < input.size() - 1; k++) {
				out += input[k];
			}
			break;
		}
	}
	if (pokasat == 0 && stepfunc == 0)input = '(' + input + ')';
	step = pokasat;
	if (pokasat == 1) {
		int flag = 0;
		for (int i = 0; i < input.size(); i++) {
			if (isnumber(input[i]) == true && flag == 0)out += input[i];
			if (flag == 1)in += input[i];
			if (input[i] == '^')flag = 1;
		}
	}
	int j = -1; int j1 = -1;
	if (stepfunc == 0 && pokasat == 0) {
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == '(') open++;
			if (input[i] == ')') close++;
			if (open <= 1) {
				out += input[i];
				j1++;
			}
			if (open >= 2) {
				in += input[i];
				j++;
			}
			if (out.size() > 0) {
				if (out[j1] == ')' || out[j1] == '(') {
					out.resize(out.size() - 1);
					j1--;
				}
			}
			if (in.size() > 0) {
				if ((in[j] == ')' || in[j] == '(') && (open != 3 || close > 1)) {
					in.resize(in.size() - 1);
					j--;
				}
			}
		}
	}
	if (out == "")Changestrs(in, out, input);
	else Changestrs(out, in, input);
}
string getconst(string data) {
	int fl = 0;
	string end = "";
	for (int i = 0; i < data.size(); i++) {
		if (isnumber(data[i]) == false && fl == 0) {
			fl = 1;
			break;
		}
		if (fl == 0 && (data[i] >= '0' && data[i] <= '9'))
			end += data[i];
	}
	if (end != "")return end;
	else return "";
}
string getpower(string data) {
	string end = "";
	int countpow = 0;
	for (int i = 0; i < data.size(); i++)if (data[i] == '^')countpow++;
	int countpow1 = 0;
	int fl = 0;
	for (int i = 0; i < data.size(); i++) {
		if (countpow1 == countpow) {
			fl = 1;
		}
		if (fl == 1 && isnumber(data[i]) == true)end += data[i];
		if (data[i] == '^')countpow1++;

	}


	return end;
}
void Changestrs(string out, string in, string input) {
	string end;
	stringstream ss;
	string Const = "";
	string power = "";
	if (step == 0) {
		Const = getconst(out);
		power = getpower(out);
	}
	//if (power == "")power = getpower(in);
	if (out == (Const + "sqrt")) {
		if(Const=="")end = "1/(2(sqrt(" + in + "))";
		else end = Const + "/2*(sqrt(" + in + ")";
	}
	if (out + "^" + in == input) {
		end = input + "*ln(" + out + ")";
	}
	if (out == (Const + "x" + "^" + power)) {
		int num;
		ss << power;
		ss >> num;
		int newnum = num - 1;
		string power1;
		power1 = to_string(newnum);
		if(newnum==1)end = ("(" + Const + "*" + to_string(num) + "x" + ")");
		else end = ("(" + Const + "*" + to_string(num) + "x" + "^" + power1 + ")");
	}
	if (out == (Const + in + "^" + power)) {
		int num;
		ss << power;
		ss >> num;
		int newnum = num - 1;
		string power1;
		power1 = to_string(newnum);
		if (newnum == 1)end = ("(" + Const + "*" + to_string(num) + in + ")");
		else end = ("(" + Const + "*" + to_string(num) + in + "^" + power1 + ")");
	}
	if (out == (Const + "sin")) {
		if(Const=="")end = "cos(" + in + ")";
		else end = Const + "cos(" + in + ")";
	}
	if (out == (Const)) {
		end = "";
	}
	if (out == (Const + "arccos")) {
		if(Const=="")end = "1/(-scrt(1-(" + in+")^2))";
		else end = Const + "/(-scrt(1-(" + in + ")^2))";
	}
	if (out == (Const + "arcsin")) {
		if (Const == "")end = "1/(scrt(1-(" + in + ")^2))";
		else end = Const + "/(scrt(1-(" + in + ")^2))";
	}
	if (out == (Const + "arctg")) {
		if (Const == "")end = "1/(1+(" + in + ")^2)";
		else end = Const + "/(1+(" + in + ")^2)";
	}
	if (out == (Const + "arcctg")) {
		if (Const == "")end = "1/-(1+(" + in + ")^2)";
		else end = Const + "/-(1+(" + in + ")^2)";
	}
	if (out == (Const + "cos")) {
		if (Const == "")end = "(-sin(" + in + "))";
		else end = Const + "*(-sin(" + in + "))";
	}
	if (out == (Const + "tg")) {
		if(Const=="")end = "1/(cos" + in + ")^2";
		else end = Const + "/(cos" + in + ")^2";
	}
	if (out == (Const + "ctg")) {
		if (Const == "")end = "1/-(sin" + in + ")^2";
		else end = Const + "/-(sin" + in + ")^2";
	}
	string easy = Const + "x";
	if (out == easy) {
		end = Const;
	}
	if (out == (Const + "ln")) {
		if(Const=="")end = "1/(" + in + ")";
		else end = Const + "/(" + in + ")";
	}
	OutPut += end;
	//cout << end;
	//cout << "*";
	if (getconst(in) != "")OutPut += "*";
	if (end != "1" && end != "0" && end != "") {
		FindDif(in);
	}
}
void CheckSummary(string inp) {
	vector<string> summ(20);
	int j = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp[i] == '+' || inp[i] == '-') {
			FindDif(summ[j]);
			if (inp[i] == '+')OutPut += "+";
			if (inp[i] == '-')OutPut += "-";
			i++;
			j++;
		}
		summ[j] += inp[i];
	}
	FindDif(summ[j]);
}
void CheckMulty(string inp) {
	vector<string> mult(2);
	int j = 0;
	int fl = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp[i] == '*') {
			i++;
			j++;
			fl = 1;
		}
		mult[j] += inp[i];
	}
	if (fl == 1) {
		OutPut += mult[0];
		OutPut += "*";
		CheckSummary(mult[1]);
		OutPut += "+";
		CheckSummary(mult[0]);
		OutPut += "*";
		OutPut += mult[1];
	}
	else CheckSummary(inp);
}
void CheckDivision(string inp) {
	vector<string> mult(2);
	int j = 0;
	int fl = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp[i] == '/') {
			i++;
			j++;
			fl = 1;
		}
		mult[j] += inp[i];
	}
	if (fl == 1) {
		OutPut += "(";
		CheckMulty(mult[0]);
		OutPut += "*";
		OutPut += mult[1];
		OutPut += "-";
		CheckMulty(mult[1]);
		OutPut += "*";
		OutPut += mult[0];
		OutPut += ")/(";
		OutPut += mult[1]; OutPut += ")^2";
	}
	else CheckMulty(inp);
}
/*int main() {
	string vod;
	getline(cin, vod);
	CheckDivision(vod);
	return 0;
}*/