#pragma once
#include<string>
#include<map>
#include<stack>
#include<iostream>
#include<sstream>
using namespace std;
class ExpressionHandler {
public:
	ExpressionHandler(string exp) {
		this->exp = exp;
	}
	bool infixtoprofix(string& exp);
	bool doprofix(string profix, double& result);
private:
	string exp;
};

bool ExpressionHandler::infixtoprofix(string& exp) {
    string from = this->exp;
    string to = "";
    stack<char> sym;
    map<char, int> pri;
    char tem;
    pri['+'] = 1;
    pri['-'] = 1;
    pri['*'] = 2;
    pri['/'] = 2;
    pri['%'] = 2;
    string::iterator it = from.begin();
    if (*it == '+' || *it == '-')to += '0';
    while (it != from.end()) {
        //cout<<1<<endl;
        switch (*it)
        {
        case'1':case'2':case'3':case'4':case'5':case'6':case'7':case
        '8':case'9':case'0':case'.':
        {
            to = to + *it;
            break;
        }
        case'+':case'-':case'*':case'/':case'%':
        {
            if ((it + 1) == from.end())
            {
                cout << "���������������ұ�ȱ��������" << endl;
                return false;
            }
            if ((*it == '*' || *it == '/') && it == from.begin())
            {
                cout << "�����������������ȱ��������" << endl;
                return false;
            }
            if ((it + 1) != from.end() && (*(it + 1) == '+' || *(it + 1) == '-' || *(it + 1) == '*' || *(it + 1) == '/' || *(it + 1) == '%'))
            {
                cout << "����������������������" << endl;
                return false;
            } 
            to = to + " ";
            if (sym.empty())
            {
                sym.push(*it);
                break;
            }
            tem = sym.top();
            while (pri[*it] <= pri[tem] && !sym.empty() && tem != '(')
            {
                to = to + tem + " ";
                sym.pop();
                if (sym.empty())break;
                tem = sym.top();
            }
            sym.push(*it);
            break;
        }
        case'(':
        {
            if ((it + 1) == from.end())
            {
                cout << "������󪩱��ʽ�������Ž�β" << endl;
                return false;
            }
            if (*(it + 1) == '-' || *(it + 1) == '+')
            {
                to = to + '0';
            }
            if ((it + 1) != from.end() && ((*(it + 1) == '*' || *(it + 1) == '/' || *(it + 1) == '%' || *(it + 1) == ')')))
            {
                cout << "��������������ұ߲���Ϊ������Ż�������" << endl;
                return false;
            }
            if (it != from.begin() && (*(it - 1) != '+' && *(it - 1) != '-' && *(it - 1) != '*' && *(it - 1) != '/' && *(it -
                1) != '%' && *(it - 1) != '('))
            {
                cout << "���������������߲���Ϊ��������������" << endl;
                return false;
            }
            sym.push(*it);
            break; }
        case')':
        {
            if ((it + 1) != from.end() && *(it + 1) != '+' && *(it + 1) != '-' && *(it + 1) != '*' && *(it + 1) != '/' && *(it
                + 1) != '%' && *(it + 1) != ')')
            {
                cout << "��������������ұ߲���Ϊ������" << endl;
                return false;
            }
            if (it != from.begin() && (*(it - 1) == '+' || *(it - 1) == '-' || *(it - 1) == '*' || *(it - 1) == '/' || *(it -
                1) == '%'))
            {
                cout << "���������������߲���Ϊ�������" << endl;
                return false;
            }
            to = to + " ";
            if (sym.empty())
            {
                cout << "������󪩱��ʽ�������ſ�ʼ" << endl;
                return false;
            }
            tem = sym.top();
            while (tem != '(')
            {
                to = to + tem + " ";
                sym.pop();
                if (sym.empty())
                {
                    cout << "�����������ƥ������" << endl;
                    return false;
                }
                tem = sym.top();
            }
            sym.pop();
            break;
        }
        default:
        {
            cout << "�������δ֪����" << endl; return false;
        }
        } ++it;
    }
    if (!sym.empty())
    {
        to = to + " ";
        tem = sym.top();
        while (!sym.empty())
        {
            if (tem == '(')
            {
                cout << "�����������ƥ������" << endl;
                return false;
            }
            to = to + tem + " ";
            sym.pop();
            if (sym.empty())break;
            tem = sym.top();
        }
    }
    exp = to;
    return true;
}
bool ExpressionHandler::doprofix(string profix, double& result)
{
    string numtemp;
    stack<double> numstack;
    stringstream strm;
    double d, d1, d2;
    for (string::iterator it = profix.begin(); it != profix.end(); ++it)
    {
        switch (*it)
        {
        case'1':case'2':case'3':case'4':case'5':case'6':case'7':case
        '8':case'9':case'0':case'.':
        {
            numtemp += *it;
            break;
        }
        case' ':
        {
            if (numtemp != "") {
                if (numtemp.find('.') && numtemp.find('.', (numtemp.find('.') + 1)) != string::npos){
                cout << "�������С������Ŀ������" + numtemp << endl;
                return false;
                }
                strm.str(numtemp);
                strm >> d;
                numstack.push(d);
                numtemp = "";
                strm.str("");
                strm.clear();
                break;
            }
            break;
        }
        case'+':
        {
            d2 = numstack.top();
            numstack.pop();
            d1 = numstack.top();
            numstack.pop();
            numstack.push(d1 + d2);
            break;
        }
        case'-':
        {
            d2 = numstack.top();
            numstack.pop();
            d1 = numstack.top();
            numstack.pop();
            numstack.push(d1 - d2);
            break;
        }
        case'*':
        {
            d2 = numstack.top();
            numstack.pop();
            d1 = numstack.top();
            numstack.pop();
            numstack.push(d1 * d2);
            break;
        } case'/':
        {
            d2 = numstack.top(); 
            numstack.pop();
            if (fabs(d2) < 0.0000001)
            {
                cout << "������󪩳�������Ϊ0" << endl;
                return false;
            }
            d1 = numstack.top();
            numstack.pop();
            numstack.push(d1 / d2);
            break;
        }
        case'%':
        {
            d2 = numstack.top();
            numstack.pop();
            d1 = numstack.top();
            numstack.pop();
            if ((fabs(d2 - (int)d2)) < 0.0000001 && (fabs(d1 - (int)d1)) < 0.0000001)
            {
                int n1 = (int)d1;
                int n2 = (int)d2;
                numstack.push((double)(n1 % n2));
                break;
            }
            else
            {
                cerr << "���������ģ����ֻ������������" << endl;
                return false;
            }
        }
        }
    }
    if (numtemp != "")
    {
        if (numtemp.find('.') && numtemp.find('.', (numtemp.find('.') + 1)) != string::npos)
        {
            cout << "�������С������Ŀ������" + numtemp << endl;
            return false;
        }
        strm.str(numtemp);
        strm >> d; 
        numstack.push(d);
    }
    if (numstack.empty())
    {
        cout << "������󪩱��ʽ��û�кϷ�������" << endl;
        return false;
    }
    result = numstack.top();
    return true;
}
int main()
{
	string str;
	double r;
	cout << "������һ�����мӡ������ˡ�������ģ����ı��ʽ���м䲻���пո�" << endl;
	cin >> str;
	cout << "��������" << endl;
	ExpressionHandler eh(str);
	string result;
	if (eh.infixtoprofix(result))
	{
		if (eh.doprofix(result, r))
			cout << r << endl;
		else  cout << "������ֹ" << endl;
	}
	else cout << "������ֹ" << endl;
	system("pause");
}