#include <bits/stdc++.h>
using namespace std;

typedef int MatrixSizeType;
typedef int DataType;

typedef struct triple
{
	MatrixSizeType row, col;
	DataType value;
}Triple;

typedef struct sparseMatrix
{
	MatrixSizeType rows, cols, nums;
	vector<Triple> data;
}SparseMatrix;

typedef struct rowTails
{
	MatrixSizeType row;
	MatrixSizeType start;
}RowTails;

typedef struct sparseMatrixWithRowTails
{
	MatrixSizeType rows, cols, nums;
	vector<Triple> data;
	vector<RowTails> rowTails;
}SparseMatrixWithRowTails;

SparseMatrix SparseMatrixs[3];

SparseMatrix Multiply(SparseMatrix, SparseMatrix);
SparseMatrixWithRowTails AttachRowTails(SparseMatrix);
void Output(SparseMatrix);

int main()
{
	for (int i = 1; i <= 2; ++i)
	{
		cin >> SparseMatrixs[i].rows >> SparseMatrixs[i].cols >> SparseMatrixs[i].nums;
		Triple temp;
		temp.row = 0;
		temp.col = 0;
		temp.value = 0;
		SparseMatrixs[i].data.push_back(temp);
		for(int j = 1; j <= SparseMatrixs[i].nums; ++j)
		{
			Triple temp;
			cin >> temp.row >> temp.col >> temp.value;
			SparseMatrixs[i].data.push_back(temp);
		}
	}
	SparseMatrix result = Multiply(SparseMatrixs[1], SparseMatrixs[2]);
	Output(result);
	return 0;
}

SparseMatrix Multiply(SparseMatrix A, SparseMatrix B)
{
	SparseMatrixWithRowTails A_with_row_tails = AttachRowTails(A);
	SparseMatrixWithRowTails B_with_row_tails = AttachRowTails(B);
	SparseMatrix result;
	result.rows = A.rows;
	result.cols = B.cols;
	result.nums = 0;
	Triple temp;
	temp.row = 0;
	temp.col = 0;
	temp.value = 0;
	result.data.push_back(temp);
	for (int i = 1; i <= A.rows; ++i)
	{
		vector<DataType> temp(result.cols + 1, 0);
		if (A_with_row_tails.rowTails[i].start != -1)
		{
			for (int j = A_with_row_tails.rowTails[i].start; j <= A.nums && A.data[j].row == i; ++j)
			{
				int A_col = A.data[j].col;
				if (B_with_row_tails.rowTails[A_col].start != -1)
					for (int k = B_with_row_tails.rowTails[A_col].start; k <= B.nums && B.data[k].row == A_col; ++k)
					{
						int B_col = B.data[k].col;
						temp[B_col] += A.data[j].value * B.data[k].value;
					}
			}
			for(int j = 1; j <= result.cols; ++j)
				if (temp[j])
				{
					Triple temp_triple;
					temp_triple.row = i;
					temp_triple.col = j;
					temp_triple.value = temp[j];
					result.data.push_back(temp_triple);
					++result.nums;
				}
		}
	}
	return result;
}

SparseMatrixWithRowTails AttachRowTails(SparseMatrix A)
{
	SparseMatrixWithRowTails A_with_row_tails;
	A_with_row_tails.rows = A.rows;
	A_with_row_tails.cols = A.cols;
	A_with_row_tails.nums = A.nums;
	A_with_row_tails.data = A.data;
	vector<RowTails> row_tails;
	RowTails temp;
	temp.row = 0;
	temp.start = -1;
	row_tails.push_back(temp);
	for (int i = 1; i <= A.rows; ++i)
	{
		RowTails temp;
		temp.row = i;
		temp.start = -1;
		row_tails.push_back(temp);
	}
	for (int i = 1; i <= A.nums; ++i)
		if (row_tails[A.data[i].row].start == -1)
			row_tails[A.data[i].row].start = i;
	A_with_row_tails.rowTails = row_tails;
	return A_with_row_tails;
}

void Output(SparseMatrix A)
{
	cout << A.rows << endl << A.cols << endl << A.nums << endl;
	for (int i = 1; i <= A.nums; ++i)
		cout << A.data[i].row << "," << A.data[i].col << "," << A.data[i].value << endl;
}

/*
* ˼·������ϡ�����ĳ˷���Ҫ��ʹ�ô��б����Ԫ�����洢������������£�
* 1. ����˼·�Ǳ���A��ÿһ�У����ڸ����з����Ԫ�أ��ø�Ԫ�ص���ȥ�ҵ�B�ж�Ӧ���У�����������B�и��еķ���Ԫ�أ��˻�����ۼӵ�һ����ʱ���鵱�У��±�ΪB��ѡ������Ԫ�ص��С������鼴Ϊ��������һ�У�������ΪA��ѡ�����С�(���A��B�������ж������ˣ�)
* 2. һ��ע��㣺��A��B���б�����ʱ����Ҫ���Ǳ߽����⣬��A�����һ����B�����һ�У���Ϊ�ڼ����ʱ����Ҫ�õ���һ���б����ʼλ�ã����Ѿ�û����һ���б��ˣ�������Ҫ���⴦��(����ֹ����Ϊi < A.nums)
* 
* ����1�������±��1��ʼ��ԭ�ȴ�0��ʼ��������һЩ��������Ǹĳ��˴�1��ʼ��
* ����2���ڱ���֮ǰû���ж���û���ҵ���Ӧ���У�����Խ�硣��Ҫ�ж�rowTails[...].start != -1��
*/