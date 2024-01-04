#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "head.h"
void CheckNode(Node* head,char start[],char end[])
{
  Node* p;
  p=head;
  while(p!=NULL)
  {
    if(!(strcmp(start,(p->info).start))&&!(strcmp(end,(p->info).end)))
    {
      printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:lf,时间:lf.",start,end,(p->info).infoCar.distance,(p->info).infoCar.cost,(p->info).infoCar.time,(p->info).infoTrain.cost,(p->info).infoTrain.time);
    }
    else
    {
      p=p->next;
    }
  }
  if(p==NULL)
  {
    printf("没有相关记录");
  }  
}
void DeleteNode(Node* head,char start[],char end[])
{
  Node* p;
  p=head;
  while(p!=NULL)
  {
    if(!(strcmp(start,(p->info).start))&&!(strcmp(end,(p->info).end)))
    {
      p->pre->next=p->next;
      p->next->pre=p->pre;
      free(p);
      printf("删除成功");
    }
    else
    {
      p=p->next;
    }
  }
  if(p==NULL)
  {
    printf("没有相关记录");
  }  
}
