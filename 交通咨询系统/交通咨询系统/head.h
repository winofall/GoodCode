#pragma once
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
  string start;
  string end;
  InfoCar infoCar;
  InfoTrain infoTrain;
}Info;
typedef struct node{
  Info info;
  Node *next;
  Node *pre;
}Node;
Node *InitNode();
void CheckNode(Node* head,string start,string end);
void CheckList(Node* head,int start,int end);
void DeleteNode(Node* head,string start,string end);
void CreateNode(Node* head,string start,string end);
