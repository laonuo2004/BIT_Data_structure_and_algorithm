#include <bits/stdc++.h>

using namespace std;

int main()
{
	int m;
	cin >> m;
	while (m--)
	{
		string s;
		cin >> s;
		int current = 0, Min = 0, Max = 0;
		for(int i = 0; i < s.size(); i++)
			if (s[i] == '+')
			{
				current++;
				Max = max(Max, current);
			}
			else if (s[i] == '-')
			{
				current--;
				Min = min(Min, current);
			}
		cout << Max - Min << endl;
	}
	return 0;
}