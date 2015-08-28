// vs2015_navigate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include "../src/navigatelib.h"
#include "../src/defines.h"

using namespace std;

string parseAtrr(int arrt) {

	/*
	#define     TurnLeft                3   //��ת
	#define     TurnRight               4   //��ת
	#define     WalkDirect              5   //ֱ��
	#define     WalkAlong               6   //����·����ǰ��
	#define     Arrive                  11  //����

	#define     UpStairs                12  //��¥��
	#define     DownStairs              -12  //��¥��
	*/

	switch (arrt)
	{
	case TurnLeft:
		return "��ת";
	case TurnRight:
		return "��ת";
	case WalkDirect:
		return "ֱ��";
	case WalkAlong:
		return  "����·����ǰ��";
	case Arrive:
		return "����";
	case UpStairs:
		return "��¥";
	case DownStairs:
		return "��¥";
	default:
		return "�����";
	}
}


int main()
{
	PointArray pointarr = loadPathInfo("e:\\mg.i2");
	int num = pointarr.num;
	/*NavPoint  *p = pointarr.pts;
	for (int i = 0; i < num; i++)
	{
		printf("i=%d, x=%f, y=%f, attr=%d, id=%d, type=%d\n", i, p->x, p->y, p->attr, p->id, p->type);
		p++;
	}
	getchar();*/

	while (1)
	{
		cout << "------------------------------------" << endl;
		int sid;
		int eid;
		cout << "input start id: ";
		cin >> sid;
		cout << "input end id: ";
		cin >> eid;

		NavPoint start;
		NavPoint end;

		start.id = sid;
		end.id = eid;

		PointArray path = getBestPath(&start, &end);
		num = path.num;
		NavPoint *p = path.pts;
		for (int i = 0; i < num; i++)
		{
			printf("i=%d, x=%f, y=%f, attr=%d, id=%d, type=%d\n", i, p->x, p->y, p->attr, p->id, p->type);
			p++;
		}
		cout << "==========" << endl;
		p = path.pts;
		for (int i = 0; i < num; i++)
		{
			cout << i << ". " << "�ڵ�" << p->id << parseAtrr(p->attr) << endl;
			p++;
		}

		cout << "input 1 fot continue, 0 to exit: ";
		int q;
		cin >> q;
		if (q == 0)
		{
			break;
		}
	}
	return 0;
}


