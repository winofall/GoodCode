#pragma once
#difine V 10
typedef struct infoCar{
  double distance;
  double cost;
  double time;
}InfoCar;
typedef struct infoTrain{
  double cost;
  double time;
}InfoTrain;
typedef struct info{
  char start[V];
  char end[V];
  InfoCar infoCar;
  InfoTrain infoTrain;
}Info;
typedef struct node{
  Info info;
  Node *next;
  Node *pre;
}Node;
Node *InitNode();
void CheckNode(Node* head,char start[],char end[]);
void CheckList(Node* head,int start,int end);
void DeleteNode(Node* head,char start[],char end[]);
void CreateNode(Node* head,char start[],char end[]);
