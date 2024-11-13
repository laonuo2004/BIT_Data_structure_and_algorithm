#include <iostream>
#include <tuple>
#include <algorithm>
#define StillLeft 1
#define Deleted 0
using namespace std;

typedef int Id, Count, Select;
typedef bool Status;

Id order = 0;

typedef struct LNode
{
	Id orderId;
	Count price;
	Count quantity;
	struct LNode *next;
}Stock;

typedef struct HeadNode
{
	Id stockId;
	Stock* buyList;
	Stock* sellList;
	struct HeadNode* next;
}StockHead;

StockHead *head;

void createStock();
Status trade(Stock*, Stock*, char);
void printTrade(Stock*, Stock*, char);
void insertWithPriceDown(Stock*, Stock*);
void insertWithPriceUp(Stock*, Stock*);
StockHead* searchStock(Id);
tuple<Stock*, StockHead*, char> deleteStock(Id);

int main()
{
	head = new StockHead;
	head->stockId = 0;
	head->next = NULL;
	head->buyList = NULL;
	head->sellList = NULL;
	Select n;
	while (cin >> n, n)
	{
		StockHead* selectedStock;
		switch (n)
		{
		case 1:
			createStock();
			break;
		case 2:
			Select stockId;
			cin >> stockId;
			selectedStock = searchStock(stockId);
			cout << "buy orders:" << endl;
			if(selectedStock)
			{
				Stock* buy = selectedStock->buyList->next;
				while (buy != NULL)
				{
					printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n", buy->orderId, stockId, (double)buy->price, buy->quantity);
					buy = buy->next;
				}
			}
			cout << "sell orders:" << endl;
			if(selectedStock)
			{
				Stock* sell = selectedStock->sellList->next;
				while (sell != NULL)
				{
					printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n", sell->orderId, stockId, (double)sell->price, sell->quantity);
					sell = sell->next;
				}
			}
			break;
		case 3:
			Select orderId;
			cin >> orderId;
			tuple<Stock*, StockHead*, char> deletedStock = deleteStock(orderId);
			if (get<0>(deletedStock))
				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", get<0>(deletedStock)->orderId, get<1>(deletedStock)->stockId, (double)get<0>(deletedStock)->price, get<0>(deletedStock)->quantity, get<2>(deletedStock));
			else
				cout << "not found" << endl;
			break;
		}
	}
	return 0;
}

void createStock()
{
	Id stockId;
	cin >> stockId;
	StockHead* currentStockHead = head->next;
	while (currentStockHead != NULL)
	{
		if (currentStockHead->stockId == stockId)
			break;
		currentStockHead = currentStockHead->next;
	}
	if (currentStockHead == NULL)
	{
		StockHead* newStockHead = new StockHead;
		newStockHead->stockId = stockId;
		newStockHead->buyList = new Stock;
		newStockHead->buyList->next = NULL;
		newStockHead->sellList = new Stock;
		newStockHead->sellList->next = NULL;
		newStockHead->next = head->next;
		head->next = newStockHead;
		currentStockHead = newStockHead;
	}
	Stock* newStock = new Stock;
	newStock->orderId = ++order;
	printf("orderid: %04d\n", order);
	newStock->next = NULL;
	cin >> newStock->price >> newStock->quantity;
	char buyOrSell;
	cin >> buyOrSell;
	if (buyOrSell == 'b')
	{
		Status ifDeleted = trade(currentStockHead->sellList, newStock, 'b');
		if (ifDeleted == StillLeft && newStock->quantity != 0)
			insertWithPriceDown(currentStockHead->buyList, newStock);
	}
	else
	{
		Status ifDeleted = trade(currentStockHead->buyList, newStock, 's');
		if (ifDeleted == StillLeft && newStock->quantity != 0)
			insertWithPriceUp(currentStockHead->sellList, newStock);
	}
}

Status trade(Stock* List, Stock* newStock, char buyOrSell)
{
	Stock* currentStock = List->next, * previousStock = List;
	if (buyOrSell == 'b')
		while (currentStock != NULL)
		{
			if (newStock->price >= currentStock->price)
			{
				if (newStock->quantity > currentStock->quantity)
				{
					printTrade(newStock, currentStock, buyOrSell);
					newStock->quantity -= currentStock->quantity;
					previousStock->next = currentStock->next;
					delete currentStock;
					currentStock = previousStock->next;
				}
				else if (newStock->quantity < currentStock->quantity)
				{
					printTrade(newStock, currentStock, buyOrSell);
					currentStock->quantity -= newStock->quantity;
					delete newStock;
					return Deleted;
				}
				else
				{
					printTrade(newStock, currentStock, buyOrSell);
					previousStock->next = currentStock->next;
					delete currentStock;
					delete newStock;
					return Deleted;
				}
			}
			else
				return StillLeft;
		}
	else
		while (currentStock != NULL)
		{
			if (newStock->price <= currentStock->price)
			{
				if (newStock->quantity > currentStock->quantity)
				{
					printTrade(newStock, currentStock, buyOrSell);
					newStock->quantity -= currentStock->quantity;
					previousStock->next = currentStock->next;
					delete currentStock;
					currentStock = previousStock->next;
				}
				else if (newStock->quantity < currentStock->quantity)
				{
					printTrade(newStock, currentStock, buyOrSell);
					currentStock->quantity -= newStock->quantity;
					delete newStock;
					return Deleted;
				}
				else
				{
					printTrade(newStock, currentStock, buyOrSell);
					previousStock->next = currentStock->next;
					delete currentStock;
					delete newStock;
					return Deleted;
				}
			}
			else
				return StillLeft;
		}
	return StillLeft;
}

void printTrade(Stock* newStock, Stock* currentStock, char buyOrSell)
{
	if (buyOrSell == 'b')
		printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (double)(newStock->price + currentStock->price) / 2, min(newStock->quantity, currentStock->quantity), newStock->orderId, currentStock->orderId);
	else
		printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (double)(newStock->price + currentStock->price) / 2, min(newStock->quantity, currentStock->quantity), newStock->orderId, currentStock->orderId);
}

void insertWithPriceDown(Stock* List, Stock* newStock)
{
	Stock* currentStock = List;
	while (currentStock->next != NULL)
	{
		if (newStock->price > currentStock->next->price)
		{
			newStock->next = currentStock->next;
			currentStock->next = newStock;
			return;
		}
		currentStock = currentStock->next;
	}
	currentStock->next = newStock;
}

void insertWithPriceUp(Stock* List, Stock* newStock)
{
	Stock* currentStock = List;
	while (currentStock->next != NULL)
	{
		if (newStock->price < currentStock->next->price)
		{
			newStock->next = currentStock->next;
			currentStock->next = newStock;
			return;
		}
		currentStock = currentStock->next;
	}
	currentStock->next = newStock;
}

StockHead* searchStock(Id stockId)
{
	StockHead* currentStockHead = head->next;
	while (currentStockHead != NULL)
	{
		if (currentStockHead->stockId == stockId)
			return currentStockHead;
		currentStockHead = currentStockHead->next;
	}
	return NULL;
}

tuple<Stock*, StockHead*, char> deleteStock(Id orderId)
{
	StockHead* currentStockHead = head->next;
	while (currentStockHead != NULL)
	{
		Stock* currentStock = currentStockHead->buyList;
		while (currentStock->next != NULL)
		{
			if (currentStock->next->orderId == orderId)
			{
				Stock* deletedStock = currentStock->next;
				currentStock->next = deletedStock->next;
				return make_tuple(deletedStock, currentStockHead, 'b');
			}
			currentStock = currentStock->next;
		}
		currentStock = currentStockHead->sellList;
		while (currentStock->next != NULL)
		{
			if (currentStock->next->orderId == orderId)
			{
				Stock* deletedStock = currentStock->next;
				currentStock->next = deletedStock->next;
				return make_tuple(deletedStock, currentStockHead, 's');
			}
			currentStock = currentStock->next;
		}
		currentStockHead = currentStockHead->next;
	}
	return make_tuple((Stock*)NULL, (StockHead*)NULL, ' ');
}

/*
* 思路：首先我们需要确定好数据结构，这里我们使用了广义表的思想，即每个股票节点都是一个广义表，包含了股票的信息和买卖队列的信息。
* 随后我们根据题目需求编写相应函数即可。
* 注意：本题十分不合理的地方：委托的quantity = 0的时候，需要进行交易，但是没有交易成功的时候，节点也不能存入买卖链表(所以会有&& quantity != 0的判断条件)。但题目没有提及这一要求，因此花了较多时间在试错。
*/