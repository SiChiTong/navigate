// vs2015_navigate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "../src/navigatelib.h"
int main()
{
	PointArray pointarr = loadPathInfo("e:\\mg.i2");
	int num = pointarr.num;
	for (int i = 0; i < num; i++)
	{
		NavPoint  *p = pointarr.pts;
		printf("x=%f, y=%f, attr=%d, id=%d, type=%d\n", p->x, p->y, p->attr, p->id, p->type);
		++p;
	}
	getchar();
    return 0;
}

