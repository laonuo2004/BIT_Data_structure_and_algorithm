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
* ˼·����׺���ʽת��׺���ʽ����������ֱ����������ڲ�������ר�ſ�һ��ջ���������ȼ����в�����
* �������ȼ������ȶ���һ�����ȼ���Ȼ���ٶ��庯��getIndex()�����ݲ��������ض�Ӧ���±ꡣ�����Ϳ��Ի�ȡ���������������ȼ���
* �����ȼ��Ĵ���
* 1. ���ȼ�Ϊ-1��ֱ����ջ
* 2. ���ȼ�Ϊ0������ջ��Ԫ��
* 3. ���ȼ�Ϊ1������ջ��Ԫ�أ�ֱ��ջ��Ԫ�����ȼ�С�ڵ�ǰ��������Ȼ���ٸ������ȼ��Ƿ���Ƚ��в���������򵯳�ջ��Ԫ�أ���������ջ
* 4. ���ȼ�Ϊ-2������
*/