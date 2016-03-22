
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include"lib_time.h"


#define MAX 600
unsigned short g_resultTemp[MAX];
unsigned short g_result[MAX];
unsigned long  g_cost;
unsigned short g_stepNumTemp;
unsigned short g_stepNum=0;
bool g_timeUp=false;
bool g_found=false;
unsigned short forcePoint[50]={0};
unsigned short head,tail,FPnum=0,vertNum=0;
GraphVertex *pVertex[MAX+1]={NULL};
bool isOK();
void saveResult();
void compareResult();


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
	myTime();
	//获取起点终点、必须通过的点
	getCommand(demand,&head,&tail,&FPnum,forcePoint);	
	//获取topo，构建图
	vertNum=getGraphic(topo,edge_num,pVertex);
	//寻找路径
	depth_visit(pVertex[head],tail);	
	//保存到文件
	saveResult();
}

unsigned long getNewCost(){
	unsigned long allCost=0;
		unsigned short vIndex,nvIndex;
   		 for (int i = 0; i < g_stepNumTemp-1; i++){
			vIndex=g_resultTemp[i];
			nvIndex=g_resultTemp[i+1];
			allCost+=pVertex[vIndex]->getEdgeCost(nvIndex);
		 }
	return allCost;
}

void compareResult(){
	unsigned long newCost=getNewCost();
	if(g_cost==0 || newCost<g_cost){
		for(int i=0;i<g_stepNumTemp;i++)
			g_result[i]=g_resultTemp[i];
		g_cost=newCost;
		g_stepNum=g_stepNumTemp;
//	printf("\nreplace:");
//	for(int i=0;i<g_stepNum;i++)
//		printf("%hu->",g_result[i]);
		if(myTime()>=5)g_timeUp=true;
	}
}


void saveResult(){
	if(g_found){
	printf("\n\n");
	for(int i=0;i<g_stepNum;i++)
		printf("%hu->",g_result[i]);
		printf("\n\n");
		unsigned short path;
		unsigned short vIndex,nvIndex;
   		 for (int i = 0; i < g_stepNum-1; i++){
			vIndex=g_result[i];
			nvIndex=g_result[i+1];
			path=pVertex[vIndex]->getEdgeIndex(nvIndex);
        	record_result(path);
			printf("%hu|",path);
		 }
		printf("\n\n");
	}

}

bool isOK(){
	bool result;
	//是否通过所有要求的点
	for(int i=0;i<FPnum;i++){
		result=false;
		for(int j=0;j<g_stepNumTemp;j++){
			if(forcePoint[i]==g_resultTemp[j]){
				result=true;
			}
		}
		if(!result)return false;
	}
	return true;

}

//递归调用
bool depth_visit(GraphVertex *v,unsigned short tail){
	g_resultTemp[g_stepNumTemp++]=v->index;	
	//v->print();
	if(v->index==tail){
	//	printf("now time:%u  ",myTime());
		
		if(isOK()){
			g_found=true;
			compareResult();
			g_stepNumTemp--;
			return true;
		}
		else{
			g_stepNumTemp--;
			return false;
		}
	}
	v->color=1;
	for(int i=0;v->edges[i].nextVertex!=NULL;i++){
		if(g_timeUp)return true;
		if(v->edges[i].nextVertex->color==0)
			depth_visit(v->edges[i].nextVertex,tail);
		
	}
	v->color=0;
//	if(!g_found)
		g_stepNumTemp--;
}

//从topo中提取数据，建立图
unsigned short getGraphic(char* topo[],int edge_num,GraphVertex* pVertex[]){
	unsigned short vertexNum=0;
	for(int index=0;index<edge_num;index++){
		unsigned short from,to,temp,cost;
		//printf("sscanfing %s\n",topo[index]);
		sscanf(*(topo+index),"%hu,%hu,%hu,%hu",&temp,&from,&to,&cost);
		//printf("after sscanfing %s\n",topo[index]);
		if(pVertex[from]==NULL){
			pVertex[from]=new GraphVertex(from);
			vertexNum++;
		}
		if(pVertex[to]==NULL){
			pVertex[to]=new GraphVertex(to);
			vertexNum++;
		}
		pVertex[from]->connectTo(pVertex[to],cost,index);
		//printf("%hu,%hu,%hu\n",temp,from,to);
	}
	return vertexNum;

}




//获取条件
void getCommand(char* demand,unsigned short* head,unsigned short* tail,unsigned short *FPnum,unsigned short forcePoint[]){
	sscanf(demand,"%hu,%hu,%hu",head,tail,&forcePoint[0]);
	printf("head is %hu,tail is %hu\nforcePoint:%hu",*head,*tail,forcePoint[0]);
	char* p=demand;
	*FPnum=1;
	while(*p!='\0'){
		if(*p!='|')p++;
		else{
			sscanf(p,"|%hu",&forcePoint[(*FPnum)++]);
			p++;
			printf("-%hu",forcePoint[(*FPnum)-1]);
		}
	}

}




    /*unsigned short result[] = {2, 6, 3};//示例中的一个解
    for (int i = 0; i < 3; i++)
        record_result(result[i]);*/
