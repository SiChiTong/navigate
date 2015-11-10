﻿#ifndef PROCESSROADPOINT_H
#define PROCESSROADPOINT_H

#include "location_defines.h"
#include "navigate_defines.h"

#include "navigate.h"

#include <map>
#include <list>
#include <iostream>
using namespace std;

/**
 *使用模板做数据点的处理，防止日后对数据结构进行修改
 *而造成程序适配复杂
 */

template<typename ElemType>

class ProcessRoadPoint
{
    friend class Navigate;
public:
    //寻找点的依据，离起点近 or 离终点近
    enum  FindType{ Start, End};
    explicit ProcessRoadPoint( map<int,ElemType*> &data ,vector<ElemType*> &pts)
        :__points(pts),_id2points(data)
    {

    }

    explicit ProcessRoadPoint(ProcessRoadPoint &p)
    {
        __points = p.__points;
        _id2points = p._id2points;
    }

    ProcessRoadPoint& operator = ( ProcessRoadPoint &p)
    {
        __points = p.__points;
        _id2points = p._id2points;
        return *this;
    }

    list<ElemType*> Process(list<ElemType*> &result)
    {
        list<ElemType*> finalResult;
        typename list<ElemType*>::iterator riter = result.begin();
        ++riter;
        finalResult.push_back(*result.begin());

        while ( riter != result.end())
        {
            ElemType *cur = *riter;
            ElemType *pre = *(--riter);
            //
            //扫描所有点，邻域点中同时包含pre和cur的点被添加进路径中
            //
            list<ElemType>   midpts;
            typename vector<ElemType*> ::iterator viter = __points.begin();
            while( viter != __points.end() )
            {
                if ( isInVector(pre->id,(*viter)->neigbours)
                     && isInVector(cur->id,(*viter)->neigbours))
                {
                    ElemType *nd = (*viter);
                    nd->g = Distance(nd,pre);
                    midpts.push_back(*(_id2points[(*viter)->id]));
                }
                ++viter;
            }

            if ( midpts.size() > 0)
            {
                midpts.sort();
                typename list<ElemType>::iterator it = midpts.begin();
                while( it != midpts.end())
                {
                    finalResult.push_back(_id2points[(*it).id]);
                    ++it;
                }
            }

            finalResult.push_back(cur);
            ++riter;
            ++riter;
        }
        return finalResult;
    }
    ElemType *findNearTagPoint(ElemType *start,ElemType *end,FindType tp)
    {

        ElemType    *res = NULL;
        int     floor;
        typename vector<ElemType*>::iterator piter = __points.begin();
        real    mindis = INVALID;
        ElemType    *dest = (tp == Start? start : end);
        bool    flag = (INVALID_ID == dest->id);

        if ( flag )
        {
            floor = dest->floor;
            while ( piter != __points.end() )
            {
                if ( FloorFromID((*piter)->id) != floor )
                {
                    ++piter;
                    continue;
                }
                real dis = Distance(dest,*piter) ;//+ Distance(start,end);
                if ( dis < mindis )
                {
                    mindis = dis;
                    res = (*piter);
                }
                ++piter;
            }

        }else
        {
            res = _id2points[dest->id];
        }
        return res;

    }
//    ElemType *findNearTagPoint_End(ElemType *start,ElemType *end)
//    {

//        ElemType    *res = NULL;
//        int     floor;
//        vector<ElemType*>::iterator piter = __points.begin();
//        real    mindis = INVALID;

//        if ( INVALID_ID == end->id )
//        {
//            floor = end->floor;
//            while ( piter != __points.end() )
//            {
//                if ( FloorFromID((*piter)->id) != floor )
//                {
//                    ++piter;
//                    continue;
//                }
//                real dis = Distance(end,*piter);// + Distance(start,end);
//                if ( dis < mindis )
//                {
//                    mindis = dis;
//                    res = (*piter);
//                }
//                ++piter;
//            }

//        }else
//        {
//            res = _id2points[start->id];
//        }
//        return res;

//    }

    ~ProcessRoadPoint()
    {

    }

private:

    vector<ElemType*>  &__points;

    //ID --Points对应表
    map<int,ElemType*> &_id2points;
};

#endif // PROCESSROADPOINT_H
