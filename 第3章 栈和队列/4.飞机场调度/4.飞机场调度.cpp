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
* ˼·�����ȿ������ݵĴ洢�ṹ��
* 1. �ɻ������ܵ���һ���ṹ�����飬ÿ���ܵ�������ʱ�����ԣ�һ����ʣ��ʱ�䣬һ������ʹ��ʱ�䣻
* 2. �ɻ����ĵȴ�������һ���ṹ�壬��һ�����к�����ʱ�����ԣ�һ���ǵȴ�ʱ�䣬һ�����ܵȴ�ʱ�䣻
* 3. �ɻ�����һ���ṹ�壬���ܵ�����������ȴ����У�
* ȷ�������ݽṹ֮�󣬾Ϳ��Կ�ʼģ��ɻ����������ˡ�����ÿһ���ӣ�
* 1. ���������ǰʱ�䣻
* 2. �����ܵ���ʣ��ʱ�䣬���ʣ��ʱ��Ϊ0������ܵ����У�ͬʱ���¶��е��ܵȴ�ʱ�䣻
* 3. ���뵱ǰʱ��ķɻ����󣬸��µȴ����У�
* 4. �ɻ����ȣ�����зɻ��ڵȴ������п����ܵ������÷ɻ���ɻ��䣬ͬʱ����ɻ�����ɻ�����Ϣ��
* 5. ʹ��airportStatus���жϻ����Ƿ�رգ�ע��ر����������ж��ж�Ϊ�գ��������ܵ������У�������ֻ�Ƕ���Ϊ�գ�
* 6. ���ģ����������ģ��ʱ�䣬ƽ���ȴ�ʱ�䣬ƽ��ʹ���ʵȡ�
*/