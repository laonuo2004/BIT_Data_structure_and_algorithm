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
		while (!endTimes.empty() && endTimes.top() <= activities[i].start) // 加入活动前先把能结束的活动结束掉
			endTimes.pop();
		endTimes.push(activities[i].end); // 加入当前活动
		count = max(count, (int)endTimes.size()); // 更新count
	}

	cout << count << endl;
	return 0;
}

/*
* 思路：多教室活动调度问题，基本思想是贪心算法：将活动按照开始时间从小到大排序，然后遍历。使用优先队列维护各个活动的结束时间，其实就相当于目前有多少个活动在进行。随时更新count表示最小需要的教室数。
* 遍历到一个活动的时候，先把能结束的活动结束掉，然后把当前活动加入，更新count。
* 
* 注意1：最开始的思路是以时间为横轴，活动为纵轴，然后遍历每个时间点，统计每个时间点的活动数，但是这样的时间复杂度是O(n * maxTime)，不可取。其实只需要遍历活动即可，而且也不需要等活动全部结束，只需要加入完所有活动就能知道最大值了。
*/