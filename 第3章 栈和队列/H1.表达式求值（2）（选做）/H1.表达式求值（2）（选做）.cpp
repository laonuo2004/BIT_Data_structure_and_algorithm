#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <vector>
#define isNum 1
#define isOperator 0
#define isLeftBracket -1
#define isRightBracket -2
using namespace std;

const int priority_table[9][9] = {
	{1,1,-1,-1,-1,-1,-1,1,1},
	{1,1,-1,-1,-1,-1,-1,1,1},
	{1,1,1,1,1,-1,-1,1,1},
	{1,1,1,1,1,-1,-1,1,1},
	{1,1,1,1,1,-1,-1,1,1},
	{1,1,1,1,1,-1,-1,1,1},
	{-1,-1,-1,-1,-1,-1,-1,0,-2},
	{1,1,1,1,1,1,-2,1,1},
	{-1,-1,-1,-1,-1,-1,-1,-2,0}
};

typedef struct variable
{
	string name;
	int value;
}Variable;

vector<Variable> variables;

int getIndex(char);
void searchForVariable(string);
void insertNum(string&, int&, stack<string>&);
void insertVariable(string&, int&, stack<string>&);
void updateVariable(Variable);
stack<string> reverse(stack<string>&);

int main()
{
	string formula;
	while (cin >> formula, formula != "end")
	{
		if (formula == "?")
		{
			cin >> formula;
			searchForVariable(formula);
			continue;
		}
		stack<char> op;
		stack<string> rpn;
		stack<string> re_rpn;
		stack<int> num;
		int last_state = isOperator;
		Variable temp;
		for(int i = 0; i <= formula.size(); ++i)
			if (formula[i] == '=')
			{
				string name = formula.substr(0, i);
				formula = formula.substr(i + 1);
				temp.name = name;
				break;
			}
		formula += '#';
		op.push('#');
		for (int i = 0; i < formula.size(); ++i)
		{
			if (formula[i] >= '0' && formula[i] <= '9')
			{
				insertNum(formula, i, rpn);
				last_state = isNum;
			}
			else if (formula[i] >= 'a' && formula[i] <= 'z' || formula[i] >= 'A' && formula[i] <= 'Z')
			{
				insertVariable(formula, i, rpn);
				last_state = isNum;
			}
			else
			{
				int col = getIndex(formula[i]);
				int row = getIndex(op.top());
				if (col == 1)
				{
					if (last_state == isOperator || last_state == isLeftBracket)
					{
						insertNum(formula, i, rpn);
						if (rpn.top() == "-")
						{
							cout << "error." << endl;
							goto end;
						}
						else
							last_state = isNum;
						continue;
					}
				}
				if (col == 6)
				{
					if (last_state == isNum || last_state == isRightBracket)
					{
						cout << "error." << endl;
						goto end;
					}
					if (!((formula[i + 1] >= '0' && formula[i + 1] <= '9') || formula[i + 1] >= 'a' && formula[i + 1] <= 'z' || formula[i + 1] >= 'A' && formula[i + 1] <= 'Z' || formula[i + 1] == '-' || formula[i + 1] == '('))
					{
						cout << "error." << endl;
						goto end;
					}
				}
				if (col == 7)
				{
					if (last_state == isOperator || last_state == isLeftBracket)
					{
						cout << "error." << endl;
						goto end;
					}
					if ((formula[i + 1] >= '0' && formula[i + 1] <= '9') || formula[i + 1] >= 'a' && formula[i + 1] <= 'z' || formula[i + 1] >= 'A' && formula[i + 1] <= 'Z' || formula[i + 1] == '(')
					{
						cout << "error." << endl;
						goto end;
					}
				}
				switch (priority_table[row][col])
				{
				case -1:
					op.push(formula[i]);
					break;
				case 0:
					op.pop();
					break;
				case 1:
					while (priority_table[getIndex(op.top())][col] == 1)
					{
						rpn.push(string(1, op.top()));
						op.pop();
					}
					if (priority_table[getIndex(op.top())][col] == 0)
						op.pop();
					else if (priority_table[getIndex(op.top())][col] == -1)
						op.push(formula[i]);
					else if (priority_table[getIndex(op.top())][col] == -2)
					{
						cout << "error." << endl;
						goto end;
					}
					break;
				case -2:
					cout << "error." << endl;
					goto end;
					break;
				}
				if (col == 6)
					last_state = isLeftBracket;
				else if (col == 7)
					last_state = isRightBracket;
				else
					last_state = isOperator;
			}
		}
		if (!op.empty() && op.top() == '#')
		{
			cout << "error." << endl;
			continue;
		}
		re_rpn = reverse(rpn);
		while (!re_rpn.empty())
		{
			if (re_rpn.top() == "+" || re_rpn.top() == "-" || re_rpn.top() == "*" || re_rpn.top() == "/" || re_rpn.top() == "%" || re_rpn.top() == "^")
			{
				int num2 = num.top();
				num.pop();
				int num1 = num.top();
				num.pop();
				if (re_rpn.top() == "+")
					num.push(num1 + num2);
				else if (re_rpn.top() == "-")
					num.push(num1 - num2);
				else if (re_rpn.top() == "*")
					num.push(num1 * num2);
				else if (re_rpn.top() == "/")
				{
					if (num2 == 0)
					{
						cout << "Divide 0." << endl;
                        exit(0);
					}
					num.push(num1 / num2);
				}
				else if (re_rpn.top() == "%")
					num.push(num1 % num2);
				else if (re_rpn.top() == "^")
				{
					if (num2 < 0)
					{
						cout << "error." << endl;
						goto end;
					}
					num.push(pow(num1, num2));
				}
			}
			else
				num.push(stoi(re_rpn.top()));
			re_rpn.pop();
		}
		//cout << num.top() << endl;
		temp.value = num.top();
		updateVariable(temp);
		num.pop();
	end:;
	}
	return 0;
}

void searchForVariable(string name)
{
	for (int i = 0; i < variables.size(); ++i)
		if (variables[i].name == name)
		{
			cout << name << "=" << variables[i].value << endl;
			return;
		}
	cout << "error." << endl;
}

int getIndex(char op)
{
	int index;
	switch (op)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '%':
		index = 4;
		break;
	case '^':
		index = 5;
		break;
	case '(':
		index = 6;
		break;
	case ')':
		index = 7;
		break;
	case '#':
		index = 8;
		break;
	}
	return index;
}

void insertNum(string& formula, int& i, stack<string>& rpn)
{
	string num;
	do
	{
		num += formula[i];
		++i;
	} while (formula[i] >= '0' && formula[i] <= '9');
	rpn.push(num);
	--i;
}

void insertVariable(string& formula, int& i, stack<string>& rpn)
{
	string name;
	do
	{
		name += formula[i];
		++i;
	} while (formula[i] >= 'a' && formula[i] <= 'z' || formula[i] >= 'A' && formula[i] <= 'Z');
	for (int j = 0; j < variables.size(); ++j)
		if (variables[j].name == name)
		{
			rpn.push(to_string(variables[j].value));
			--i;
			return;
		}
	cout << "error." << endl;
}

stack<string> reverse(stack<string>& rpn)
{
	stack<string> temp;
	while (!rpn.empty())
	{
		temp.push(rpn.top());
		rpn.pop();
	}
	return temp;
}

void updateVariable(Variable temp)
{
	for(int i = 0; i < variables.size(); ++i)
		if (variables[i].name == temp.name)
		{
			variables[i].value = temp.value;
			return;
		}
	variables.push_back(temp);
}

/*
* ˼·���������ȼ�������׺���ʽת��Ϊ��׺���ʽ���ټ����׺���ʽ��ֵ������������£�
* 1. ������ʽ�������ʽĩβ����'#'��ͬʱ����׺���ʽת��׺���ʽ��Ҫ����ջ��������ջop���沨�����ʽջrpn(δ��ת����)��
* 2. ������ʽ��ÿһ���ַ���
*    1. ���ֿ����ж�λ�����ѭ��������ֱ����һ���ַ��������֣���numѹ��rpnջ��ע����Ҫ���ǵ����������������insertNum������Ҫ�õ�do-whileѭ������Ϊ��һ���ַ��Ǹ��ţ�
*    2. ���������������һ��ͬ��
* 3. Ϊ�˴��������������Ҫ�Ǹ������������ţ���Ҫ����last_state��������¼��һ���ַ���״̬��ͬʱ��Ҫ�ж������ұߵ��ַ��Ƿ�Ϸ���
*
* ����������沨�����ʽ��ֵ������������£�
* 1. �沨�����ʽջ��Ҫ��ת�����⻹Ҫ������һ��ջnum�����ڴ洢���֣�
* 2. �����沨�����ʽջ��
*    1. ����ǲ��������򵯳��������֣������ѹ��numջ��
*    2. ��������֣���ѹ��numջ��
* 3. ���numջ�е����ּ�Ϊ���ʽ��ֵ��
* ע�⣺����������Ҫ�жϳ����Ƿ�Ϊ0����������Ҫ�ж�ָ���Ƿ�Ϊ������
* 
* ˼·2������չ�˱���֮����ʵ����ֻ��Ҫ����һ����Ԫ�飬�洢��������ֵ���˺�ͨ���ö�Ԫ����������������ֵ��ӳ�伴�ɡ��������ݺ���һ�������ͬ��
* 
* �ջ�1������ʹ��cin.get(string)��cin.getline(string)����ȡ�ո�ע����߻Ὣ���з���Ϊ'\0'����ǰ�߲��᣻ͬʱע��ǰ���ڶ�ȡ���е�ʱ����Ҫ�ڵ�һ�к����cin.get()����Ϊcin.get(string)�������з���ֹͣ��ȡ�������з����ᱻ��ȡ������������з�ȥ�����ͻ�һֱ�޷����У��������cin.get()���Ƕ�ȡ��һ���ַ����������з���
* �ջ�2�������������ѭ������Ȼ��Ҷ�����ʹ��һ��bool�����������ѭ�����жϣ���������ΪgotoҲ���ԣ���Ϊ��������ֱ����������ѭ����Ч����ߣ�ͬʱע��labelð�ź���������Ҫһ����䣬������Ч������ʹ�ÿ������ʵ�֣�
*/