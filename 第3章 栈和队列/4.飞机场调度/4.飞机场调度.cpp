#include <iostream>
#include <queue>
#define OK 1
#define ERROR 0
using namespace std;

typedef bool Status;
typedef int Time, PlaneId, Count;

Time simulationTime = 0;
Time takeoffTime = 0, landingTime = 0;
PlaneId takeoffId = 0, landingId = 5000;
Count runwayCount = 0;
Status airportStatus = OK;

typedef struct waitingQueue
{
	queue<PlaneId> waitingQueue;
	Time waitingTime;
	Time totalWaitingTime;
}waitingQueue;

typedef struct runway
{
	Time timeLeft;
	Time timeUsed;
}runway;

typedef struct airport
{
	runway* runways;
	Count runwayCount;
	waitingQueue takeoffQueue;
	waitingQueue landingQueue;
}airport;

airport* createAirport(Count runwayCount)
{
	airport* ap = new airport;
	ap->runwayCount = runwayCount;
	ap->runways = new runway[runwayCount];
	for (runway* currentRunway = ap->runways; currentRunway < ap->runways + runwayCount; currentRunway++)
	{
		currentRunway->timeLeft = 0;
		currentRunway->timeUsed = 0;
	}
	ap->landingQueue.waitingTime = landingTime;
	ap->landingQueue.totalWaitingTime = 0;
	ap->takeoffQueue.waitingTime = takeoffTime;
	ap->takeoffQueue.totalWaitingTime = 0;
	return ap;
}

void airplaneRequestUpdate(Count takeoff, Count landing, airport* ap)
{
	if (takeoff < 0 && landing < 0)
	{
		airportStatus = ERROR;
		return;
	}
	while (takeoff--)
		ap->takeoffQueue.waitingQueue.push(++takeoffId);
	while (landing--)
		ap->landingQueue.waitingQueue.push(++landingId);
	return;
}

void airplaneDispatch(airport* ap)
{
	runway* currentRunway = ap->runways;
	waitingQueue* currentQueue = &ap->landingQueue;
	while (currentRunway < ap->runways + ap->runwayCount && (!ap->takeoffQueue.waitingQueue.empty() || !ap->landingQueue.waitingQueue.empty()))
	{
		if (currentQueue->waitingQueue.empty())
		{
			currentQueue = &ap->takeoffQueue;
			continue;
		}
		if (currentRunway->timeLeft)
		{
			currentRunway++;
			continue;
		}
		PlaneId currentPlane = currentQueue->waitingQueue.front();
		currentQueue->waitingQueue.pop();
		currentRunway->timeLeft = currentQueue->waitingTime;
		if(currentQueue == &ap->landingQueue)
			printf("airplane %04d is ready to land on runway %02d\n", currentPlane, currentRunway - ap->runways + 1);
		else
			printf("airplane %04d is ready to takeoff on runway %02d\n", currentPlane, currentRunway - ap->runways + 1);
		currentRunway++;
	}
}

void timeUpdate(airport* ap)
{
	for (runway* currentRunway = ap->runways; currentRunway < ap->runways + ap->runwayCount; currentRunway++)
	{
		if (currentRunway->timeLeft)
		{
			currentRunway->timeLeft--;
			currentRunway->timeUsed++;
			if (!currentRunway->timeLeft)
				printf("runway %02d is free\n", currentRunway - ap->runways + 1);
		}
	}
	ap->landingQueue.totalWaitingTime += ap->landingQueue.waitingQueue.size();
	ap->takeoffQueue.totalWaitingTime += ap->takeoffQueue.waitingQueue.size();
}

void outputSimulationResult(airport* ap)
{
	cout << "simulation finished" << endl;
	printf("simulation time: %4d\n", --simulationTime);
	printf("average waiting time of landing: %4.1f\n", (double)ap->landingQueue.totalWaitingTime / (landingId - 5000));
	printf("average waiting time of takeoff: %4.1f\n", (double)ap->takeoffQueue.totalWaitingTime / (takeoffId - 0));
	Time totalUsedTime = 0;
	for (runway* currentRunway = ap->runways; currentRunway < ap->runways + ap->runwayCount; currentRunway++)
	{
		printf("runway %02d busy time: %4d\n", currentRunway - ap->runways + 1, currentRunway->timeUsed);
		totalUsedTime += currentRunway->timeUsed;
	}
	printf("runway average busy time percentage: %4.1f%%\n", (double)totalUsedTime / simulationTime / ap->runwayCount * 100);
}

Status ifEmpty(airport* ap)
{
	if (ap->landingQueue.waitingQueue.empty() && ap->takeoffQueue.waitingQueue.empty())
	{
		for (runway* currentRunway = ap->runways; currentRunway < ap->runways + ap->runwayCount; currentRunway++)
			if (currentRunway->timeLeft)
				return ERROR;
		return OK;
	}
	return ERROR;
}

void Debug(airport* ap)
{
	cout << "Debug" << endl;
	cout << "landingQueue: ";
	queue<PlaneId> temp = ap->landingQueue.waitingQueue;
	while (!temp.empty())
	{
		cout << temp.front() << " ";
		temp.pop();
	}
	cout << endl;
	cout << "totalWaitingTime: " << ap->landingQueue.totalWaitingTime << endl;
	cout << "takeoffQueue: ";
	temp = ap->takeoffQueue.waitingQueue;
	while (!temp.empty())
	{
		cout << temp.front() << " ";
		temp.pop();
	}
	cout << endl;
	cout << "totalWaitingTime: " << ap->takeoffQueue.totalWaitingTime << endl;
	cout << "runways: ";
	for (runway* currentRunway = ap->runways; currentRunway < ap->runways + ap->runwayCount; currentRunway++)
	{
		cout << currentRunway->timeLeft << " ";
	}
	cout << endl;
}

int main()
{
	cin >> runwayCount >> landingTime >> takeoffTime;
	airport* ap = createAirport(runwayCount);
	while (!ifEmpty(ap) || airportStatus)
	{
		printf("Current Time: %4d\n", simulationTime++);
		timeUpdate(ap);
		//Debug(ap);
		Count takeoff, landing;
		if (airportStatus)
		{
			cin >> landing >> takeoff;
			airplaneRequestUpdate(takeoff, landing, ap);
		}
		airplaneDispatch(ap);
	}
	outputSimulationResult(ap);
	return 0;
}

/*
* 思路：首先考虑数据的存储结构：
* 1. 飞机场的跑道是一个结构体数组，每个跑道有两个时间属性，一个是剩余时间，一个是已使用时间；
* 2. 飞机场的等待队列是一个结构体，有一个队列和两个时间属性，一个是等待时间，一个是总等待时间；
* 3. 飞机场是一个结构体，有跑道数组和两个等待队列；
* 确定了数据结构之后，就可以开始模拟飞机场的运行了。对于每一分钟：
* 1. 首先输出当前时间；
* 2. 更新跑道的剩余时间，如果剩余时间为0，输出跑道空闲；同时更新队列的总等待时间；
* 3. 输入当前时间的飞机请求，更新等待队列；
* 4. 飞机调度，如果有飞机在等待，且有空闲跑道，就让飞机起飞或降落，同时输出飞机的起飞或降落信息；
* 5. 使用airportStatus来判断机场是否关闭，注意关闭条件是所有队列都为空，且所有跑道都空闲，不仅仅只是队列为空；
* 6. 输出模拟结果，包括模拟时间，平均等待时间，平均使用率等。
*/