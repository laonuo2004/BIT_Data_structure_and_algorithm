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
* 思路：关于稀疏矩阵的乘法，要求使用带行表的三元组来存储，计算过程如下：
* 1. 基本思路是遍历A的每一行，对于该行中非零的元素，用该元素的列去找到B中对应的行，并继续遍历B中该行的非零元素，乘积结果累加到一个临时数组当中，下标为B中选定非零元素的列。该数组即为结果矩阵的一行，行数即为A中选定的行。(因此A、B的行与列都用上了！)
* 2. 一个注意点：对A与B进行遍历的时候，需要考虑边界问题，即A的最后一行与B的最后一列，因为在计算的时候，需要用到下一个行表的起始位置，但已经没有下一个行表了，所以需要特殊处理。(即终止条件为i < A.nums)
* 
* 错误1：建议下标从1开始！原先从0开始，导致了一些错误！最后还是改成了从1开始；
* 错误2：在遍历之前没有判断有没有找到对应的行，导致越界。需要判断rowTails[...].start != -1；
*/