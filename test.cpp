#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<ctype.h>
#include<vector>
using namespace std;
struct st {
	string x, y, z,zz;
};
struct rule {
	st a, b, c;
};
vector<st> v;
vector<rule> v2;

bool f1(string s) {
	bool ok=true;
	if (!islower(s[0])) {
		cout << "词法错误：谓词" << s << "未使用小写字母开头" << '\n';
		ok = false;
	}
	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i]) && !isdigit(s[i]) && s[i] != '_') {
			cout << "词法错误：" << s << "使用了不符合规定的字符" << '\n';
			ok = false;
			break;
		}
	}
	return ok;
}

bool f2(string s) {
	bool ok = true;
	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i]) && !isdigit(s[i]) && s[i] != '_') {
			cout << "词法错误：" << s << "使用了不符合规定的字符" << '\n';
			ok = false;
			break;
		}
	}
	return ok;
}

bool divide_decision(string s) {
	if(s[0]=='/'&&s[1]=='*'){
		for(int i=1;i<s.length();i++){
			if(s[i-1]=='*'&&s[i]=='/')
				return true;
		}
	}
	bool ok = true;
	string a[100];
	int ii=0,count = 0;
	bool ookk = true;
	bool okk = true;
	for (int i = 0; i < s.length()-2; i++) {
		if (s[i] == ':'&&s[i + 1] == '-') {
			for (int j = 0; j < i; j++) {
				if (s[j] == '(' || s[j] == ')')
					ookk = false;
			}
			if (ookk) {
				a[0] = s.substr(0, i);
				a[1] = ":-";
				count = 2;
				ii = i + 2;
				break;
			}
		}
	}
	while (ii < s.length()) {
		int t = 0;
		while (s[ii] != ' '&&s[ii] != ','&&s[ii] != '.'&&s[ii] != ')'&&s[ii] != '(' && s[ii] != ']' && s[ii] != '[' && s[ii] != '}' && s[ii] != '{') {
			if (ii == s.length())
				break;
			if (ii<s.length()-1&&s[ii] == ':'&&s[ii + 1] == '-')
				break;
			if (ii<s.length() - 1 && s[ii] == '/'&&s[ii + 1] == '*')
				break;
			ii++;
			t++;
		}
		if (ii < s.length() - 1 && s[ii] == ':'&&s[ii + 1] == '-') {
			if(s[ii+2]=='-'){
				a[count++]=":--";
				ii+=3;
			}
			else{
				a[count++] = ":-";
				ii += 2;
			}
			continue;
		}
		if(t)
			a[count++] = s.substr(ii - t, t);
		if (ii < s.length() - 1 && s[ii] == '/'&&s[ii + 1] == '*') {
			bool ok1 = true;
			for (; ii < s.length() - 1; ii++) {
				if (s[ii] == '*'&&s[ii + 1] == '/') {
					ii += 2;
					ok1 = false;
					break;
				}
			}
			if (ok1) {
				cout << "注释缺少右半部分*/" << '\n';
				ok = false;
				return false;
			}
		}
		if (ii == s.length())
			break;
		for (; s[ii] == ' '; ii++) ;
		if (s[ii] == ',' || s[ii] == '.' || s[ii] == ')' || s[ii] == '(' || s[ii] == ']' || s[ii] == '[' || s[ii] == '}' || s[ii] == '{') {
			a[count++] = s[ii];
			ii++;
		}
		for (; s[ii] == ' '; ii++);
	}
	
	if (count == 0)
		return ok;
	bool ok2 = true;//not a rule
	for (int i = 0; ok2&&i < count&&a[i]!=""; i++) {
		for (int j = i+1; ok2&&j < count&&a[j]!=""; j++) {
			if (count>9&&a[i]!=","&&a[i] == a[j])
				ok2 = false;//rule
		}
	}
	if (!f1(a[0]))
		ok = false;
	ii = 2;
	if (a[1] != "(") {
		ok = false;
		if(a[1]==":-"){
			cout<<"缺少谓词后的括号和参数\n";
			ii=2;
			ok=false;
			goto L1;
		}
		for (int i = 0; i < a[1].length(); i++)
			if (isalpha(a[1][i])) {
				if(a[2]=="(")
					cout<<"谓词中间存在空格\n";
				else
					cout << "缺少左括号\n";
				return false;
			}
		if (ii == 2) {
			cout << "左括号被" << a[1] << "代替\n";
		}
		
	}
	if (ok2) {
		while (ii < count) {//进入括号内的判断
			if (!f1(a[ii++]))
				return false;
			if (ii == count) {
				cout << "缺少)和.\n";
				return false;
				
			}
			if (a[ii] == ")" || a[ii] == "(" || a[ii] == "}" || a[ii] == "]"||a[ii]==".") {
				if(ii+1<count&&a[ii]==")"&&a[ii+1]==")"){
					cout<<"连续使用了两个右括号\n";
					return false;
				}
				if(a[ii]==")"&&ii+1==count){
					cout<<"缺少最后的.\n";
					return false;
					
				}
				if(a[ii]==")"&&ii+2==count){
					if(a[ii+1]!="."){
						cout<<"最后的点被符号"<<a[ii+1]<<"代替\n";
						ok=false;
					}
				}
				if (a[ii] != ")") {
					if (a[ii] != "."){
						cout << "右括号被符号"<<a[ii] << "代替\n";
						if(ii==count-1)
							cout<<"缺少最后的.\n";
					}
					else{
						cout << "缺少右括号\n";
						ii--;
					}
					return false;
				}
				break;
			}
			if (a[ii] != ",") {
				bool b = true;
				for (int i = 0; i < a[ii].length(); i++)
					if (isalpha(a[ii][i])) {
						b = false;
						ii--;
						cout << "缺少逗号\n";
						break;
					}
				if (b)
					cout << "逗号被字符" << a[ii] << "代替\n";
				return false;
			}
			if(ii+1<count&&a[ii]==","&&a[ii+1]==","){
				cout<<"连续使用了两个逗号\n";
				return false;
			}
			if(ii+1<count&&a[ii]==","&&a[ii+1]==")"){
				cout<<"缺少一个参数\n";
				return false;
			}
			ii++;
		}
	}
	else {
	//	bool okk = true;//至少要有一个参数第一个大写
		while (ii < count) {//进入第一个括号内的判断
			if (!f2(a[ii]))
				return false;
			if (isupper(a[ii][0]))
				okk=false;
			ii++;
			if (a[ii] == ")" || a[ii] == "(" || a[ii] == "}" || a[ii] == "]" || a[ii] == ":"||a[ii]=="-") {
				if (a[ii] != ")") {
					if (a[ii] != ":-"&&a[ii] != "-"&&a[ii] != ":") {
						cout << "右括号被符号" << a[ii] << "代替\n";
						ii++;
					}
					else
						cout << "缺少右括号\n";
					return false;
				}
				else
					ii++;
				break;
			}
			if (a[ii] != ",") {
				bool b = true;
				for (int i = 0; i < a[ii].length(); i++)
					if (isalpha(a[ii][i])) {
						b = false;
						ii--;
						cout << "缺少逗号\n";
						break;
					}
				if (b)
					cout << "逗号被字符" << a[ii] << "代替\n";
				return false;
			}
			ii++;
		}
		//if (okk) {
		//	cout << "错误！rule中至少要有一个参数的首字母大写\n";
		//	ok = false;
		//}
		if (a[ii] != ":-") {
			bool okw = true;
			for (int i = 0; i < a[ii].length(); i++) {
				if (isalpha(a[ii][0])) {
					okw = false;
					cout << "缺少符号:-\n";
					ii--;
					break;
				}
			}
			if (okw)
				cout << "符号:-被" << a[ii] << "代替\n";
			return false;
		}
		ii++;
L1:		if (!f1(a[ii]))
			return false;
		if (a[++ii] != "(") {
			
			bool okw = true;
			for (int i = 0; i < a[ii].length(); i++)
				if (isalpha(a[ii][i])) {
					ii--;
					cout << "缺少左括号\n";
					okw = false;
					break;
				}
			if (okw) {
				cout << "左括号被" << a[ii] << "代替\n";
			}
			return false;
		}
		ii++;
		okk = true;
		while (ii < count) {//进入第2个括号内的判断
			if (!f2(a[ii]))
				return false;
			if (isupper(a[ii][0]))
				okk=false;
			ii++;
			if (a[ii] == ")" || a[ii] == "(" || a[ii] == "}" || a[ii] == "]") {
				if (a[ii] != ")") {
					cout << "右括号被符号" << a[ii] << "代替\n";
					ok = false;
				}
				ii++;
				break;
			}
			if (a[ii] != ",") {
				bool b = true;
				for (int i = 0; i < a[ii].length(); i++)
					if (isalpha(a[ii][i])) {
						b = false;
						ii--;
						cout << "缺少逗号\n";
						break;
					}
				if (b)
					cout << "逗号被字符" << a[ii] << "代替\n";
				return false;
			}
			ii++;
		}
		//if (okk) {
		//	cout << "错误！rule中至少要有一个参数的首字母大写\n";
		//	ok = false;
		//}
		if (a[ii] != ",") {
			bool okw = true;
			for (int i = 0; i < a[ii].length(); i++) {
				if (isalpha(a[ii][0])) {
					okw = false;
					cout << "缺少逗号\n";
					ii--;
					break;
				}
			}
			if(ii==count-1&&a[ii]==".")
				goto L2;
			if (okw)
				cout << "逗号被" << a[ii] << "代替\n";
			return false;
		}
		ii++;
		if (!f2(a[ii]))
			return false;
		if (a[++ii] != "(") {
			ok = false;
			bool okw = true;
			for (int i = 0; i < a[ii].length(); i++)
				if (isalpha(a[ii][i])) {
					ii--;
					cout << "缺少左括号\n";
					okw = false;
					break;
				}
			if (okw) {
				cout << "左括号被" << a[ii] << "代替\n";
			}
			return false;
		}
		ii++;
		okk = true;
		while (ii < count) {//进入第3个括号内的判断
			if (!f2(a[ii]))
				return false;
			if (isupper(a[ii][0]))
				okk = false;
			ii++;
			if (ii == count) {
				cout << "缺少右括号和最后的.\n";
				return false;
				
			}
			if (a[ii] == ")" || a[ii] == "(" || a[ii] == "}" || a[ii] == "]" || a[ii] == ".") {
				if (a[ii] != ")") {
					ok = false;
					if (a[ii] == ".") {
						cout << "缺少右括号\n";
						break;
					}
					if (a[ii] != ".") {
						cout << "右括号被符号" << a[ii] << "代替\n";
						ii++;
						if (ii == count)
							cout << "缺少最后的.\n";
						break;
					}
					return false;
				}
				else {
					ii++;
					if (ii == count)
						cout << "缺少最后的.\n";
					break;
				}
			}
			if (a[ii] != ",") {
				bool b = true;
				for (int i = 0; i < a[ii].length(); i++)
					if (isalpha(a[ii][i])) {
						b = false;
						ii--;
						cout << "缺少逗号\n";
						break;
					}
				if (b)
					cout << "逗号被字符" << a[ii] << "代替\n";
				return false;
			}
			ii++;
		}
		//if (okk) {
		//	cout << "错误！rule中至少要有一个参数的首字母大写\n";
		//	ok = false;
		//}
	}
	
L2:	if (ok) {
		char ch[100][100];
		for (int i = 0; i < 100; i++)
			strcpy(ch[i], a[i].c_str());
		FILE* f = fopen("token.txt", "a");
		for (int i = 0; i < count; i++) {
			if (i == 0)
				fprintf(f, "%s", "predicate:");
			else if (islower(a[i][0]))
				fprintf(f, "%s", "argument:");
			else if (isupper(a[i][0]))
				fprintf(f, "%s", "variable:");
			else
				fprintf(f, "%s", "symbol:");
			fprintf(f, "%s ", ch[i]);
		}
		fprintf(f, "\n\n");
		fclose(f);
		if (ok2) {//not the rule
			st s;
			s.x = a[0];
			s.y = a[2];
			if (count == 5) {
				s.z = "";
				s.zz = "";
			}
			if (count == 7) {
				s.z = a[4];
				s.zz = "";
			}
			if (count == 9) {
				s.z = a[4];
				s.zz = a[6];
			}
			v.push_back(s);
		}
		else {
			int cr=0,arr[3];//右括号位置
			for (int i = 0; i < count; i++) {
				if (a[i] == ")")
					arr[cr++] = i;
			}
			rule r;
			r.a.x = a[0];
			r.a.y = a[2];
			if(arr[0]==5||arr[0]==7)
				r.a.z = a[4];
			if (arr[0] == 7)
				r.a.zz = a[6];
			r.b.x = a[arr[0] + 2];
			r.b.y = a[arr[0] + 4];
			if (arr[0] + 7 == arr[1] || arr[0] + 9 == arr[1])
				r.b.z = a[arr[0] + 6];
			if (arr[1] + 9 == arr[2])
				r.b.zz = a[arr[0] + 8];
			r.c.x = a[arr[1] + 2];
			r.c.y = a[arr[1] + 4];
			if (arr[1] + 7 == arr[2] || arr[1] + 9 == arr[2])
				r.c.z = a[arr[1] + 6];
			if (arr[1] + 9 == arr[2])
				r.c.zz = a[arr[1] + 8];
			v2.push_back(r);
		}
	}
	return ok;
}

bool operator==(st &t1, st &t2){
	return (t1.x == t2.x) && (t1.y == t2.y)&&(t1.z==t2.z)&&(t1.zz==t2.zz);
}

void handle() {
	for (int i = 0; i < v2.size(); i++) {
		string s1 = v2[i].a.y, s2 = v2[i].a.z;
		if (isupper(s1[0]) && isupper(s2[0])) {//X,Y
			int flag, flag1;
			if (s1 == v2[i].b.y)
				flag = 1;
			if (s1 == v2[i].b.z)
				flag = 2;
			if (s2 == v2[i].c.y)
				flag1 = 1;
			if (s2 == v2[i].c.z)
				flag1 = 2;
			if (flag == 1 && flag1 == 1) {//F(X,Z),F(Y,Z)
				for (int ii = 0; ii < v.size(); ii++) {
					if (v[ii].x == v2[i].b.x) {
						for (int j = 0; j < v.size(); j++) {
							if (ii!=j&&v[j].x == v2[i].c.x&&v[ii].z == v[j].z) {
								st ss;
								ss.x = v2[i].a.x;
								ss.y = v[ii].y;
								ss.z = v[j].y;
								v.push_back(ss);
							}
						}
					}
				}
			}
			if (flag == 1 && flag1 == 2) {
				for (int ii = 0; ii < v.size(); ii++) {
					if (v[ii].x == v2[i].b.x) {
						for (int j = 0; j < v.size(); j++) {
							if (ii != j&&v[j].x == v2[i].c.x&&v[ii].z == v[j].y) {
								st ss;
								ss.x = v2[i].a.x;
								ss.y = v[ii].y;
								ss.z = v[j].z;
								v.push_back(ss);
							}
						}
					}
				}
			}
			if (flag == 2 && flag1 == 1) {
				for (int ii = 0; ii < v.size(); ii++) {
					if (v[ii].x == v2[i].b.x) {
						for (int j = 0; j < v.size(); j++) {
							if (ii != j&&v[j].x == v2[i].c.x&&v[ii].y == v[j].z) {
								st ss;
								ss.x = v2[i].a.x;
								ss.y = v[ii].z;
								ss.z = v[j].y;
								v.push_back(ss);
							}
						}
					}
				}
			}
			if (flag == 2 && flag1 == 2) {
				for (int ii = 0; ii < v.size(); ii++) {
					if (v[ii].x == v2[i].b.x) {
						for (int j = 0; j < v.size(); j++) {
							if (ii != j&&v[j].x == v2[i].c.x&&v[ii].y == v[j].y) {
								st ss;
								ss.x = v2[i].a.x;
								ss.y = v[ii].z;
								ss.z = v[j].z;
								v.push_back(ss);
							}
						}
					}
				}
			}
			continue;
		}
		//int po = 0;
		string temp;
		if (isupper(s1[0]))
			temp = s1;
		if (isupper(s2[0]))
			temp = s2;
		int flag,flag1;
		if (temp == v2[i].b.y)
			flag = 1;
		if (temp == v2[i].b.z)
			flag = 2;
		if (temp == v2[i].c.y)
			flag1 = 1;
		if (temp == v2[i].c.z)
			flag1 = 2;
		for (int ii = 0; ii < v.size(); ii++) {
			if (flag == 1 && flag1 == 1) {
				if (v[ii].x == v2[i].b.x&&v[ii].z==v2[i].b.z) {
					for (int j = 0; j < v.size(); j++) {
						if (ii != j&&v[j].x == v2[i].c.x&&v[ii].y == v[j].y&&v[j].z==v2[i].c.z) {
							st ss;
							ss.x = v2[i].a.x;
							if (temp == s1) {
								ss.y = v[j].y;
								ss.z = v2[i].a.z;
							}
							else {
								ss.y = v2[i].a.y;
								ss.z = v[j].y;
							}
							v.push_back(ss);
						}
					}
				}
			}
			if (flag == 1 && flag1 == 2) {
				if (v[ii].x == v2[i].b.x&&v2[i].b.z==v[ii].z) {
					for (int j = 0; j < v.size(); j++) {
						if (ii != j&&v[j].x == v2[i].c.x&&v[ii].y == v[j].z&&v2[i].c.y==v[j].y) {
							st ss;
							ss.x = v2[i].a.x;
							if (temp == s1) {
								ss.y = v[j].z;
								ss.z = v2[i].a.z;
							}
							else {
								ss.y = v2[i].a.y;
								ss.z = v[j].z;
							}
							v.push_back(ss);
						}
					}
				}
			}
			if (flag == 2 && flag1 == 1) {
				if (v[ii].x == v2[i].b.x&&v2[i].b.y==v[ii].y) {
					for (int j = 0; j < v.size(); j++) {
						if (ii != j&&v[j].x == v2[i].c.x&&v[ii].z == v[j].y&&v2[i].c.z==v[j].z) {
							st ss;
							ss.x = v2[i].a.x;
							if (temp == s1) {
								ss.y = v[j].y;
								ss.z = v2[i].a.z;
							}
							else {
								ss.y = v2[i].a.y;
								ss.z = v[j].y;
							}
							v.push_back(ss);
						}
					}
				}
			}
			if (flag == 2 && flag1 == 2) {
				if (v[ii].x == v2[i].b.x&&v2[i].b.y==v[ii].y) {
					for (int j = 0; j < v.size(); j++) {
						if (ii != j&&v[j].x == v2[i].c.x&&v[ii].z == v[j].z&&v2[i].c.y==v[j].y) {
							st ss;
							ss.x = v2[i].a.x;
							if (temp == s1) {
								ss.y = v[j].z;
								ss.z = v2[i].a.z;
							}
							else {
								ss.y = v2[i].a.y;
								ss.z = v[j].y;
							}
							v.push_back(ss);
						}
					}
				}
			}
		}
	}
}

void select(string s) {
	bool ok = true;
	string a[100];
	int ii = 0, count = 0;
	while (ii < s.length()) {
		int t = 0;
		while (s[ii] != ' '&&s[ii] != ','&&s[ii] != '.'&&s[ii] != ')'&&s[ii] != '(' && s[ii] != ']' && s[ii] != '[' && s[ii] != '}' && s[ii] != '{') {
			if (ii == s.length())
				break;
			if (ii<s.length() - 1 && s[ii] == ':'&&s[ii + 1] == '-')
				break;
			if (ii<s.length() - 1 && s[ii] == '/'&&s[ii + 1] == '*')
				break;
			ii++;
			t++;
		}
		if (ii < s.length() - 1 && s[ii] == ':'&&s[ii + 1] == '-') {
			a[count++] = ":-";
			ii += 2;
			continue;
		}
		if (t)
			a[count++] = s.substr(ii - t, t);
		if (ii < s.length() - 1 && s[ii] == '/'&&s[ii + 1] == '*') {
			bool ok1 = true;
			for (; ii < s.length() - 1; ii++) {
				if (s[ii] == '*'&&s[ii + 1] == '/') {
					ii += 2;
					ok1 = false;
					break;
				}
			}
			if (ok1) {
				cout << "注释缺少右半部分*/" << '\n';
				ok = false;
				return;
			}
		}
		if (ii == s.length())
			break;
		for (; s[ii] == ' '; ii++);
		if (s[ii] == ',' || s[ii] == '.' || s[ii] == ')' || s[ii] == '(' || s[ii] == ']' || s[ii] == '[' || s[ii] == '}' || s[ii] == '{') {
			a[count++] = s[ii];
			ii++;
		}
		for (; s[ii] == ' '; ii++);
	}
	if (count == 0)
		return;
	if (!f1(a[0]))
		ok = false;
	ii = 2;
	if (a[1] != "(") {
		ok = false;
		for (int i = 0; i < a[1].length(); i++)
			if (isalpha(a[1][i])) {
				ii--;
				cout << "缺少左括号\n";
				break;
			}
		if (ii == 2) {
			cout << "左括号被" << a[1] << "代替\n";
		}
	}

	while (ii < count) {//进入括号内的判断
			if (!f2(a[ii++]))
				ok = false;
			if (ii == count) {
				cout << "缺少)和.\n";
				ok = false;
				break;
			}
			if (a[ii] == ")" || a[ii] == "(" || a[ii] == "}" || a[ii] == "]" || a[ii] == ".") {
				if(a[ii]==")"&&ii+1==count){
                                          cout<<"缺少最后的.\n";
                                          ok=false;
                                          break;
                                  }
                                  if (a[ii] != ")") {
                                          if (a[ii] != "."){
                                                  cout << "右括号被符号"<<a[ii]   << "代替\n";
                                                  if(ii==count-1)
                                                          cout<<"缺少最后的.\n";
                                          }
                                          else{
                                                  cout << "缺少右括号\n";
                                                  ii--;
                                          }
                                          ok = false;
                                  }
                                  break;
			}
			if (a[ii] != ",") {
				bool b = true;
				for (int i = 0; i < a[ii].length(); i++)
					if (isalpha(a[ii][i])) {
						b = false;
						ii--;
						cout << "缺少逗号\n";
						break;
					}
				if (b)
					cout << "逗号被字符" << a[ii] << "代替\n";
				ok = false;
			}
			ii++;
	}
	
	if (ok) {
		st s;
		s.x = a[0];
		s.y = a[2];
		if (count == 5) {
			s.z = "";
			s.zz = "";
		}
		if (count == 7) {
			s.z = a[4];
			s.zz = "";
		}
		if (count == 9) {
			s.z = a[4];
			s.zz = a[6];
		}
		if (isupper(s.y[0])) {
			bool ol = false;
			cout << s.y << " =";
			for (int i = 0; i < v.size(); i++) {
				if (v[i].x == s.x&&v[i].z == s.z&&v[i].zz == s.zz) {
					cout << " " << v[i].y;
					ol = true;
				}
			}
			if (!ol)
				cout << " no data";
			return;
		}
		if (isupper(s.z[0])) {
			bool ol = false;
			cout << s.z << " =";
			for (int i = 0; i < v.size(); i++) {
				if (v[i].x == s.x&&v[i].y == s.y&&v[i].zz == s.zz) {
					cout << " " << v[i].z;
					ol = true;
				}
			}
			if (!ol)
				cout << " no data";
			return;
		}
		if (isupper(s.zz[0])) {
			bool ol = false;
			cout << s.zz << " =";
			for (int i = 0; i < v.size(); i++) {
				if (v[i].x == s.x&&v[i].z == s.z&&v[i].y == s.y) {
					cout << " " << v[i].zz;
					ol = true;
				}
			}
			if (!ol)
				cout << " no data";
			return;
		}
		for (int i = 0; i < v.size(); i++) {
			if (s == v[i]) {
				cout << "true.";
				return;
			}
		}
		cout << "false.";
	}
}

int main() {
	cout << "\n?-";
	string s;
		cin >> s;
		getchar();
		if (s == "halt.")
			return 0;
		if (s.substr(0, 7) == "consult") {
			int i = 8;
			for (; s[i] != ')'; i++);
			string file = s.substr(8, i - 8)+".pl";
			char files[80];
			strcpy(files, file.c_str());
			string line;
			ifstream in(files);
			if (!in) {
				cout << "No file!";
				return 0;
			}
			bool ok = true;
			while (getline(in, line)) {
				cout << line << '\n';
				if(line[line.length()-1]=='\r')
					line=line.substr(0,line.length()-1);
				if (!divide_decision(line))
					ok = false;
			}
			if (!ok)
				return 0;
			cout << "true.";
			handle();
			while (1) {
				cout << "\n?-";
				string s1;
				getline(cin,s1);
				if(line[s1.length()-1]=='\r')
                                        s1=s1.substr(0,s1.length()-1);
				if (s1 == "halt.")
					return 0;
				select(s1);
			}
		}
}
