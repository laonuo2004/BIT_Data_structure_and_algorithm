// ʵ�ʣ����ڽ��������
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;

typedef struct
{
	int id;
	ll x, y;
}Point;

ll calculateTwoPoints(Point a, Point b)
{
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2); // ע�ⷵ�ص��Ǿ����ƽ��
}

ll calculateThreePoints(vector<Point> pointX, int size)
{
	if (size < 2)
		return LLONG_MAX;
	ll min = calculateTwoPoints(pointX[0], pointX[1]);
	if(size == 3)
	{
		ll temp = calculateTwoPoints(pointX[0], pointX[2]);
		if(temp < min)
			min = temp;
		temp = calculateTwoPoints(pointX[1], pointX[2]);
		if(temp < min)
			min = temp;
	}
	return min;
}

ll merge(vector<Point>& pointX, vector<Point>& pointY, int size, int mid, ll Min)
{
	// �ҳ��м�����ĵ�
	vector<Point> strip;
	for(int i = 0; i < size; i++)
		if(pow(pointY[i].x - pointX[mid - 1].x, 2) < Min)
			strip.push_back(pointY[i]);

	// �볲ԭ�����ֻ��Ƚ�7����
	for(int i = 0; i < strip.size(); i++)
		for(int j = i + 1; j < strip.size() && j < i + 8; j++)
		{
			ll temp = calculateTwoPoints(strip[i], strip[j]);
			if(temp < Min)
				Min = temp;
		}

	return Min;
}

ll devide(vector<Point>& pointX, vector<Point>& pointY, int size)
{
	// С�ڵ���3����ʱֱ�Ӽ���
	if (size <= 3)
		return calculateThreePoints(pointX, size);

	// ���Ϊ������������
	int mid = size / 2;
	vector<Point> leftX(pointX.begin(), pointX.begin() + mid);
	vector<Point> rightX(pointX.begin() + mid, pointX.end());

	// ��¼��Щ�������������
	vector<int> leftPointId(n);
	for(int i = 0; i < leftX.size(); i++)
		leftPointId[leftX[i].id] = 1;

	vector<Point> leftY, rightY;
	for (int i = 0; i < size; i++)
		if (leftPointId[pointY[i].id])
			leftY.push_back(pointY[i]);
		else
			rightY.push_back(pointY[i]);

	//sort(leftY.begin(), leftY.end(), [](Point a, Point b) { return a.y < b.y; });
	//sort(rightY.begin(), rightY.end(), [](Point a, Point b) { return a.y < b.y; });

	//for (int i = 0; i < size; i++)
	//	if (pointY[i].x <= pointX[mid - 1].x && leftY.size() < mid)
	//		leftY.push_back(pointY[i]);
	//	else
	//		rightY.push_back(pointY[i]);

	//vector<Point> leftX1(leftX), leftY1(leftY);
    //sort(leftY1.begin(), leftY1.end(), [](Point a, Point b) { return a.x < b.x; }); // debug
    //// ɾ��leftX1��leftY1�е��ظ�Ԫ��
	//for (int i = 0; i < leftX1.size(); i++)
	//{
	//	for (int j = 0; j < leftY1.size(); j++)
	//	{
	//		if (leftX1[i].x == leftY1[j].x && leftX1[i].y == leftY1[j].y)
	//		{
	//			leftX1.erase(leftX1.begin() + i);
	//			leftY1.erase(leftY1.begin() + j);
	//			i--;
	//			j--;
	//			break;
	//		}
	//	}
	//}

	// �ݹ����������������ڽ���Եľ����ƽ��
	ll leftMin = devide(leftX, leftY, leftX.size());
	ll rightMin = devide(rightX, rightY, rightX.size());
	ll Min = min(leftMin, rightMin); // ע����ƽ��

	// �ϲ�������������ڽ����
	return merge(pointX, pointY, size, mid, Min);
}

int main()
{
	//n = 100000;
	while (cin >> n, n)
	//if(1)
	{
		vector<Point> pointX(n);

		ll x, y;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			//x = rand();
			//y = rand();
			pointX[i].id = i;
			pointX[i].x = x;
			pointX[i].y = y;
		}
		vector<Point> pointY(pointX);
		sort(pointX.begin(), pointX.end(), [](Point a, Point b) { return a.x < b.x; });
		sort(pointY.begin(), pointY.end(), [](Point a, Point b) { return a.y < b.y; });

		printf("%.2f\n", sqrt(devide(pointX, pointY, n)) / 2.0); // ע�⿪���ţ��Լ�����2����Ϊ�����ľ����ǰ뾶��2��
		//printf("%.2f\n", devide(pointX, pointY, n) / 2.0); // ע�����2����Ϊ�����ľ�Z�ǰ뾶��2��
	}
	return 0;
}

//-------------------------------------

//#include <bits/stdc++.h>
//#define ll long long
//
//using namespace std;
//
//struct Point {
//    ll x, y;
//};
//
//// ����������ŷ����þ���
//double calculateTwoPoints(Point a, Point b) {
//    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//}
//
//// ��� 2 �� 3 ����ֱ�Ӽ�����С����
//double calculateThreePoints(const vector<Point>& pointX, int size) {
//    if (size < 2) return 0; // �����������ֹԽ��
//    double minDist = calculateTwoPoints(pointX[0], pointX[1]);
//    if (size == 3) {
//        double temp = calculateTwoPoints(pointX[0], pointX[2]);
//        minDist = min(minDist, temp);
//        temp = calculateTwoPoints(pointX[1], pointX[2]);
//        minDist = min(minDist, temp);
//    }
//    return minDist;
//}
//
//// �ϲ���������Ľ��
//double merge(vector<Point>& pointX, vector<Point>& pointY, int size, int mid, double Min) {
//    vector<Point> strip;
//    ll midX = pointX[mid].x; // ����������ʹ�� mid ���� mid-1
//
//    for (int i = 0; i < size; i++) {
//        if (abs(pointY[i].x - midX) < Min) { // �Ż���ʹ�þ���ֵ
//            strip.push_back(pointY[i]);
//        }
//    }
//
//    // ֻ��Ƚ���� 7 ����
//    for (int i = 0; i < strip.size(); i++) {
//        for (int j = i + 1; j < strip.size() && j < i + 8; j++) {
//            double temp = calculateTwoPoints(strip[i], strip[j]);
//            Min = min(Min, temp);
//        }
//    }
//
//    return Min;
//}
//
//// �����㷨������
//double devide(vector<Point>& pointX, vector<Point>& pointY, int size) {
//    if (size <= 3) {
//        return calculateThreePoints(pointX, size); // С��ģֱ�Ӽ���
//    }
//
//    int mid = size / 2;
//    vector<Point> leftX(pointX.begin(), pointX.begin() + mid);
//    vector<Point> rightX(pointX.begin() + mid, pointX.end());
//
//    vector<Point> leftY, rightY;
//    ll midX = pointX[mid].x; // ��������
//
//    for (int i = 0; i < size; i++) {
//        if (pointY[i].x < midX || (pointY[i].x == midX && i < mid)) {
//            leftY.push_back(pointY[i]);
//        }
//        else {
//            rightY.push_back(pointY[i]);
//        }
//    }
//
//    double leftMin = devide(leftX, leftY, mid);
//    double rightMin = devide(rightX, rightY, size - mid);
//
//    double Min = min(leftMin, rightMin);
//    return merge(pointX, pointY, size, mid, Min);
//}
//
//int main() {
//    int n;
//
//    while (cin >> n, n) {
//        vector<Point> pointX(n);
//        for (int i = 0; i < n; i++) {
//            cin >> pointX[i].x >> pointX[i].y;
//        }
//
//        vector<Point> pointY(pointX);
//        sort(pointX.begin(), pointX.end(), [](Point a, Point b) { return a.x < b.x; });
//        sort(pointY.begin(), pointY.end(), [](Point a, Point b) { return a.y < b.y; });
//
//        double minDist = devide(pointX, pointY, n) / 2.0; // ��С�뾶Ϊ�����һ��
//        printf("%.2f\n", minDist);
//    }
//
//    return 0;
//}