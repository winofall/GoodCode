#pragma once
#define V 10
typedef struct node Node;
typedef struct infoCar {
	double distance;
	double cost;
	double time;
}InfoCar;
typedef struct infoTrain {
	double cost;
	double time;
}InfoTrain;
typedef struct info {
	char start[V];
	char end[V];
	InfoCar infoCar;
	InfoTrain infoTrain;
}Info;
typedef struct node {
	Info info;
	Node* next;
	Node* pre;
}Node;
typedef struct graph {
	Node* head;
	double value[100][100];
	char place[100][20];
}MGraph;
Node* InitNode();
void CheckNode(Node* head, char start[], char end[]);//查询该结点信息
void CheckList(Node* head, int start, int end);
void DeleteNode(Node* head, char start[], char end[],const char* filename);//删除信息
void CreateNode(Node* head,  const char* filename);//从文件中获取信息，建立结点
void GetMoney(Node* head, char start[], char end[]);//从给的起始点，在链表中找出cost最小的路径
void GetDis(Node* head, char start[], char end[]);//从给的起始点，在链表中找出distance最小的路径
void GetTime(Node* head, char start[], char end[]);//从给的起始点，在链表中找出time最小的路径
void AddNode(Node* head, char start[], char end[], double CarDistance, double CarCost, double Cartime, double TrainCost, double TrainTime);//更新与start，end的结点的数据
