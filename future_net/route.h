#ifndef __ROUTE_H__
#define __ROUTE_H__

#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;
void search_route(char *graph[5000], int edge_num, char *condition);


class GraphVertex;
class GraphEdge;
void depth_search(GraphVertex *tBegin[]);
bool depth_visit(GraphVertex *v,unsigned short tail);
void getCommand(char* demand,unsigned short* head,unsigned short* tail,unsigned short *FPnum,unsigned short forcePoint[]);
unsigned short getGraphic(char* topo[],int edge_num,GraphVertex* pVertex[]);


class GraphEdge{
public:
	GraphVertex* nextVertex;
	unsigned short cost;
	unsigned short index;

public:
	GraphEdge():nextVertex(NULL){}
	~GraphEdge(){}
};



class GraphVertex{
public:
	unsigned short index;
	int color;
	int edgeNum;
	//int cost;
	//广度遍历父结点
	//GraphVertex* parent;
	//深度优先搜索的开始结束时间 
	int startTime,stopTime;
	//边
	GraphEdge edges[8];

public:
	GraphVertex():color(0),edgeNum(0){}
	GraphVertex(unsigned short n):index(n),color(0),edgeNum(0){}
	~GraphVertex(){};
	void setIndex(unsigned short n){index=n;}
	void setEdge(unsigned short index,GraphVertex* next){
		edges[index].nextVertex=next;
	}
	void print(){
		cout<<index<<"->";
	}
	void connectTo(GraphVertex* to,unsigned short c,unsigned short edgeIndex){
		edges[edgeNum].nextVertex=to;
		edges[edgeNum].cost=c;
		edges[edgeNum].index=edgeIndex;
		edgeNum++;
	}
	unsigned short getEdgeIndex(unsigned short toVertexIndex){
		unsigned short index;
		for(int i=0;i<edgeNum;i++){
			if(edges[i].nextVertex->index == toVertexIndex)
				index=edges[i].index;
		}	
		return index;
	}
};















#endif
