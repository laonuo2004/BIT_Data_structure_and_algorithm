#include <iostream>
#include <stack>
#include <string>
using namespace std;

const int priority_table[8][8] = {
	{1,1,-1,-1,-1,-1,1,1},
	{1,1,-1,-1,-1,-1,1,1},
	{1,1,1,1,-1,-1,1,1},
	{1,1,1,1,-1,-1,1,1},
	{1,1,1,1,-1,-1,1,1},
	{-1,-1,-1,-1,-1,-1,0,-2},
	{1,1,1,1,1,-2,1,1},
	{-1,-1,-1,-1,-1,-1,-2,0}
};

int getIndex(char);

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string formula;
		cin >> formula;
		stack<char> op;
		op.push('#');
		for (int i = 0; i < formula.size(); ++i)
		{
			if ((formula[i] >= 'A' && formula[i] <= 'Z') || (formula[i] >= 'a' && formula[i] <= 'z'))
				cout << formula[i];
			else
			{
				int col = getIndex(formula[i]);
				int row = getIndex(op.top());
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
						cout << op.top();
						op.pop();
					}
					if (priority_table[getIndex(op.top())][col] == 0)
						op.pop();
					else
						op.push(formula[i]);
					break;
				case -2:
					break;
				}
			}
		}
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
	case '^':
		index = 4;
		break;
	case '(':
		index = 5;
		break;
	case ')':
		index = 6;
		break;
	case '#':
		index = 7;
		break;
	}
	return index;
}

/*
* 思路：中缀表达式转后缀表达式，对于数，直接输出，对于操作符，专门开一个栈，根据优先级进行操作。
* 关于优先级，首先定义一个优先级表，然后再定义函数getIndex()，根据操作符返回对应的下标。这样就可以获取两个操作符的优先级。
* 各优先级的处理：
* 1. 优先级为-1，直接入栈
* 2. 优先级为0，弹出栈顶元素
* 3. 优先级为1，弹出栈顶元素，直到栈顶元素优先级小于当前操作符，然后再根据优先级是否相等进行操作：相等则弹出栈顶元素，不等则入栈
* 4. 优先级为-2，错误
*/