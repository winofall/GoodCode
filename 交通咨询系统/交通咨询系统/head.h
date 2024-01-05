#pragma once
#define V 20
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
	int nums;
	int path[100];
}MGraph;
Node* InitNode();
void CheckNode(Node* head, char start[], char end[]);//查询该结点信息
void CheckAllNode(Node* head);//查询所有结点信息
void CheckList(Node* head, int start, int end);
void DeleteNode(Node* head, char start[], char end[],const char* filename);//删除信息
void CreateNode(Node* head,  const char* filename);//从文件中获取信息，建立结点
void GetMoney(Node* head, char start[], char end[]);//从给的起始点，在链表中找出cost最小的路径
void GetDis(Node* head, char start[], char end[]);//从给的起始点，在链表中找出distance最小的路径
void GetTime(Node* head, char start[], char end[]);//从给的起始点，在链表中找出time最小的路径
void AddNode(const char* filename, const char* start, const char* end, double CarDistance, double CarCost, double Cartime, double TrainCost, double TrainTime)//更新文件
