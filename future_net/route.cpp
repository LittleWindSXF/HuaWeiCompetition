
#include "route.h"
#include "lib_record.h"
#include <stdio.h>

#define MAX 600
unsigned short g_resultTemp[MAX];
unsigned short g_stepNum=0;
bool g_found=false;
unsigned short forcePoint[50]={0};
unsigned short head,tail,FPnum=0,vertNum=0;
bool isOK();



//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{

	getCommand(demand,&head,&tail,&FPnum,forcePoint);	

	GraphVertex *pVertex[MAX+1]={NULL};
	vertNum=getGraphic(topo,edge_num,pVertex);
	depth_visit(pVertex[head],tail);	

	if(g_found){
	unsigned short path;
	unsigned short vIndex,nvIndex;
    for (int i = 0; i < g_stepNum-1; i++){
		vIndex=g_resultTemp[i];
		nvIndex=g_resultTemp[i+1];
		path=pVertex[vIndex]->getEdgeIndex(nvIndex);
        record_result(path);
	}
	//	printf("\nfound!look:-->");
	//	for(int i=0;i<g_stepNum;i++)
	//		printf("%hu-->",g_resultTemp[i]);
	//	printf("\n");
	}
	else
	;//	printf("\n\nNA\n\n");
}


bool isOK(){
	bool result;
	//是否通过所有要求的点
	for(int i=0;i<FPnum;i++){
		result=false;
		for(int j=0;j<g_stepNum;j++){
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
	g_resultTemp[g_stepNum++]=v->index;	
	//v->print();
	if(v->index==tail){
	//	printf("\n stack:%hu members-->",g_stepNum);
	//	for(int i=0;i<g_stepNum;i++)
	//		printf("%hu-->",g_resultTemp[i]);
	//	printf("\n ");
		if(isOK()){
			g_found=true;
			return true;
		}
		else{
			g_stepNum--;
	//		printf("get back\n");
			return false;
		}

	}
	v->color=1;
	for(int i=0;v->edges[i].nextVertex!=NULL;i++){
		if(g_found)return true;
		if(v->edges[i].nextVertex->color==0)
			depth_visit(v->edges[i].nextVertex,tail);
		
	}
	//printf("bk ");
	v->color=0;
	if(!g_found)
		g_stepNum--;
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
