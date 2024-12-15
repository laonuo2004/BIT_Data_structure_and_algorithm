#include <bits/stdc++.h>

using namespace std;

typedef struct
{
	int start, end;
}Activity;

int main()
{
	int n;
	cin >> n;
	vector<Activity> activities(n);
	for (int i = 0; i < n; i++)
		cin >> activities[i].start >> activities[i].end;
	sort(activities.begin(), activities.end(), [](Activity a, Activity b) { return a.start < b.start; });

	int count = 1;
	priority_queue<int, vector<int>, greater<int>> endTimes;
	endTimes.push(activities[0].end);

	for (int i = 1; i < n; ++i)
	{
		while (!endTimes.empty() && endTimes.top() <= activities[i].start) // ����ǰ�Ȱ��ܽ����Ļ������
			endTimes.pop();
		endTimes.push(activities[i].end); // ���뵱ǰ�
		count = max(count, (int)endTimes.size()); // ����count
	}

	cout << count << endl;
	return 0;
}

/*
* ˼·������һ�������⣬����˼����̰���㷨��������տ�ʼʱ���С��������Ȼ�������ʹ�����ȶ���ά��������Ľ���ʱ�䣬��ʵ���൱��Ŀǰ�ж��ٸ���ڽ��С���ʱ����count��ʾ��С��Ҫ�Ľ�������
* ������һ�����ʱ���Ȱ��ܽ����Ļ��������Ȼ��ѵ�ǰ����룬����count��
* 
* ע��1���ʼ��˼·����ʱ��Ϊ���ᣬ�Ϊ���ᣬȻ�����ÿ��ʱ��㣬ͳ��ÿ��ʱ���Ļ��������������ʱ�临�Ӷ���O(n * maxTime)������ȡ����ʵֻ��Ҫ��������ɣ�����Ҳ����Ҫ�Ȼȫ��������ֻ��Ҫ���������л����֪�����ֵ�ˡ�
*/