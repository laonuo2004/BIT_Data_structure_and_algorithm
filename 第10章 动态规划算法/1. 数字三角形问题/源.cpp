#include <iostream>
using namespace std;
int main()
{
	int n, temp, flag = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> temp;
		if (temp == i)
		{
			flag = 1;
			cout << temp << " ";
		}
	}
	if (!flag)
		cout << "No ";
	cout << endl;
	return 0;
}