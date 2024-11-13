#include <bits/stdc++.h>
#define OK 1
#define ERROR 0
#define StringError "ERROR"
using namespace std;

typedef char elemType;
typedef bool Status;

typedef struct genericList
{
	bool tag;
	union
	{
		elemType data;
		struct
		{
			struct genericList* headLink, * tailLink;
		};
	};
}GList;

GList glist;

Status CreateGList(GList&, string);
GList GetHead(GList);
GList GetTail(GList);
void DestroyGList(GList&);
void PrintGList(GList);
void PrintGListWithoutBracket(GList);
Status IsAtom(GList);
Status IsEmpty(GList);
string getHeadString(string);
string getTailString(string);
int countElement(string);

int main()
{
	string genericList;
	cin >> genericList;
	CreateGList(glist, genericList);
	cout << "generic list: ";
	PrintGList(glist);
	cout << endl;
	int operation;
	//GList* temp_1, * temp_2;
	//GList glist_temp_1, glist_temp_2;
	while(!(IsAtom(glist) || IsEmpty(glist)))
	{
		cin >> operation;
		switch (operation)
		{
		case 1:
			if(glist.tailLink)
				DestroyGList(*glist.tailLink);
			//temp_1 = &glist;
			cout << "destroy tail" << endl << "free list node" << endl << "generic list: ";
			//glist_temp_1 = GetHead(glist);
			//delete temp_1;
			//glist = glist_temp_1;
			glist = GetHead(glist);
			PrintGList(glist);
			cout << endl;
			break;
		case 2:
			if(glist.headLink)
				DestroyGList(*glist.headLink);
			//temp_2 = &glist;
			cout << "free head node" << endl << "free list node" << endl;
			//glist_temp_2 = GetTail(glist);
			//delete temp_2;
			//glist = glist_temp_2;
			if (glist.tailLink)
			{
				glist = GetTail(glist);
				if (!(glist.tag == 1 && glist.headLink == NULL && glist.tailLink == NULL))
				{
					cout << "generic list: ";
					PrintGList(glist);
					cout << endl;
				}
			}
			else
			{
				cout << "generic list: ()" << endl;
				exit(0);
			}
			break;
		}
	}
	return 0;
}

Status CreateGList(GList& L, string s)
{
	if (s == "()")
	{
		L.tag = 1;
		L.headLink = NULL;
		L.tailLink = NULL;
		return OK;
	}
	else if (s.length() == 1)
	{
		L.tag = 0;
		L.data = s[0];
		return OK;
	}
	else
	{
		L.tag = 1;
		string head = getHeadString(s);
		string tail = getTailString(s);
		if (!(head == StringError))
		{
			L.headLink = new GList;
			CreateGList(*L.headLink, head);
		}
		else
			L.headLink = NULL;
		if(!(tail == StringError) && !(tail == "()"))
		{
			L.tailLink = new GList;
			CreateGList(*L.tailLink, tail);
		}
		else
			L.tailLink = NULL;
		return OK;
	}
}

GList GetHead(GList L)
{
	return *L.headLink;
}

GList GetTail(GList L)
{
	return *L.tailLink;
}

void DestroyGList(GList& L)
{
	if (L.tag == 1)
	{
		if (L.headLink)
			DestroyGList(*L.headLink);
		if (L.tailLink)
			DestroyGList(*L.tailLink);
		//delete &L.headLink;
		//delete &L.tailLink;
		delete &L;
	}
}

void PrintGList(GList L)
{
	if (L.tag == 1)
	{
		cout << "(";
		if (L.headLink)
			PrintGList(*L.headLink);
		if (L.tailLink)
		{
			cout << ",";
			PrintGListWithoutBracket(*L.tailLink);
		}
		cout << ")";
	}
	else
		cout << L.data;
}

void PrintGListWithoutBracket(GList L)
{
	if (L.tag == 1)
	{
		if (L.headLink)
			PrintGList(*L.headLink);
		if (L.tailLink)
		{
			cout << ",";
			PrintGListWithoutBracket(*L.tailLink);
		}
	}
	else
		cout << L.data;
}

Status IsAtom(GList L)
{
	if(L.tag == 0)
		return OK;
	else
		return ERROR;

}

Status IsEmpty(GList L)
{
	if (L.tag == 1 && L.headLink == NULL && L.tailLink == NULL)
		return OK;
	else
		return ERROR;
}

string getHeadString(string s)
{
	if(s[0] != '(')
		return StringError;
	string str = "";
	int count = 0, i = 1;
	while (!(count == 0 && (s[i] == ',' || s[i] == ')')) && i < s.length())
	{
		if (s[i] == '(')
			count++;
		else if (s[i] == ')')
			count--;
		str += s[i];
		i++;
	}
	return str;
}

string getTailString(string s)
{
	if (s[0] != '(')
		return StringError;
	//int count = 0, i = 1;
	//while(!(count == 0 && s[i] == ',') && i < s.length())
	//{
	//	if (i == s.length() - 1)
	//		return StringError;
	//	i++;
	//}
	//i++;
	//string str = "(";
	//count = 0;
	//while (!(count == 0 && s[i] == ')') && i < s.length())
	//{
	//	if (s[i] == '(')
	//		count++;
	//	else if (s[i] == ')')
	//		count--;
	//	str += s[i];
	//	i++;
	//}
	//str += ")";
	//return str;)
	if(countElement(s) == 1)
		return "()";
	string headString = getHeadString(s);
	int startToErase = s.find(headString);
	string str = s.erase(startToErase, headString.length() + 1);
	return str;
}

int countElement(string s)
{
	if (s[0] != '(')
		return ERROR;
	int count = 0, i = 1, element = 1;
	while (!(count == 0 && s[i] == ')') && i < s.length())
	{
		if (s[i] == '(')
			count++;
		else if (s[i] == ')')
			count--;
		else if (s[i] == ',' && count == 0)
			element++;
		i++;
	}
	return element;
}