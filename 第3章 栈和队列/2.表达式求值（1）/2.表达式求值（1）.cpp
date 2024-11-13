#include <iostream>
#include <stack>
#include <string>
#include <cmath>
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

int getIndex(char);
void insertNum(string&, int&, stack<string>&);
stack<string> reverse(stack<string>&);

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string formula;
		cin >> formula;
		formula += '#';
		stack<char> op;
		stack<string> rpn;
		stack<string> re_rpn;
		stack<int> num;
		op.push('#');
		int last_state = isOperator;
		for (int i = 0; i < formula.size(); ++i)
		{
			if (formula[i] >= '0' && formula[i] <= '9')
			{
				insertNum(formula, i, rpn);
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
							cout << "error.";
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
						cout << "error.";
						goto end;
					}
					if(!((formula[i + 1] >= '0' && formula[i + 1] <= '9') || formula[i + 1] == '-' || formula[i + 1] == '('))
					{
						cout << "error.";
						goto end;
					}
				}
				if (col == 7)
				{
					if (last_state == isOperator || last_state == isLeftBracket)
					{
						cout << "error.";
						goto end;
					}
					if((formula[i + 1] >= '0' && formula[i + 1] <= '9') || formula[i + 1] == '(')
					{
						cout << "error.";
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
						cout << "error.";
						goto end;
					}
					break;
				case -2:
					cout << "error.";
					goto end;
					break;
				}
				if(col == 6)
					last_state = isLeftBracket;
				else if(col == 7)
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
		while(!re_rpn.empty())
		{
			if(re_rpn.top() == "+" || re_rpn.top() == "-" || re_rpn.top() == "*" || re_rpn.top() == "/" || re_rpn.top() == "%" || re_rpn.top() == "^")
			{
				int num2 = num.top();
				num.pop();
				int num1 = num.top();
				num.pop();
				if(re_rpn.top() == "+")
					num.push(num1 + num2);
				else if(re_rpn.top() == "-")
					num.push(num1 - num2);
				else if(re_rpn.top() == "*")
					num.push(num1 * num2);
				else if (re_rpn.top() == "/")
				{
					if (num2 == 0)
					{
						cout << "Divide 0.";
						goto end;
					}
					num.push(num1 / num2);
				}
				else if(re_rpn.top() == "%")
					num.push(num1 % num2);
				else if (re_rpn.top() == "^")
				{
					if(num2 < 0)
					{
						cout << "error.";
						goto end;
					}
					num.push(pow(num1, num2));
				}
			}
			else
				num.push(stoi(re_rpn.top()));
			re_rpn.pop();
		}
		cout << num.top();
		num.pop();
	end:
		cout << endl;
	}
	return 0;
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

/*
* 思路：根据优先级表，将中缀表达式转换为后缀表达式，再计算后缀表达式的值。具体过程如下：
* 1. 读入表达式，将表达式末尾加上'#'。同时，中缀表达式转后缀表达式需要两个栈：操作符栈op，逆波兰表达式栈rpn(未翻转过的)；
* 2. 读入表达式的每一个字符：
*    1. 数字可能有多位，因此循环遍历，直到下一个字符不是数字，将num压入rpn栈；注意需要考虑到负数的情况，于是insertNum函数需要用到do-while循环，因为第一个字符是负号；
*    2. 遇到操作符，与第一题同理；
* 3. 为了处理特殊情况，主要是负数与左右括号，需要增加last_state变量，记录上一个字符的状态，同时需要判断括号右边的字符是否合法；
* 
* 随后，我们求逆波兰表达式的值。具体过程如下：
* 1. 逆波兰表达式栈需要翻转，此外还要再增加一个栈num，用于存储数字；
* 2. 遍历逆波兰表达式栈：
*    1. 如果是操作符，则弹出两个数字，计算后压入num栈；
*    2. 如果是数字，则压入num栈；
* 3. 最后num栈中的数字即为表达式的值。
* 注意：除法运算需要判断除数是否为0，幂运算需要判断指数是否为负数。
*/