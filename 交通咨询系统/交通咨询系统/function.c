#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "head.h"
void CheckNode(Node* head, char start[], char end[])
{
    Node* p;
    p = head;
    while (p != NULL)
    {
        if (!(strcmp(start, (p->info).start)) && !(strcmp(end, (p->info).end)))
        {
            if ((p->info).infoTrain.cost != 0){
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:lf,时间:lf.", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
                break; }
            else {
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf.", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time);
            }
      }
        else
        {
            p = p->next;
        }
    }
    if (p == NULL)
    {
        printf("没有相关记录");
    }
}
void DeleteNode(Node* head, char start[], char end[])
{
    Node* p;
    p = head;
    while (p != NULL)
    {
        if (!(strcmp(start, (p->info).start)) && !(strcmp(end, (p->info).end)))
        {
            p->pre->next = p->next;
            p->next->pre = p->pre;
            free(p);
            printf("删除成功");
            break;
        }
        else
        {
            p = p->next;
        }
    }
    if (p == NULL)
    {
        printf("没有相关记录");
    }
}
void CreateNode(Node* head, char start[], char end[], const char* filename) {
    FILE* file = fopen(filename, "1.txt");//打开文件
    if (file == NULL) {
        printf("无法打开: %s\n", filename);
        return;
    }

    char buffer[256]; // 假设一行不超过 256 个字符
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // 从文件中读取每一行的信息
        char fileStart[V], fileEnd[V],car[V],train[V];
        double carDistance, carCost, carTime, trainCost, trainTime;

        // 假设文件中的格式为："起始地点 终点地点 私家车距离 私家车费用 私家车时间 火车费用 火车时间"
        if(trainCost!=0){
        sscanf(buffer, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd,car, &carDistance, &carCost, &carTime,train, &trainCost, &trainTime);
        }else{
        sscanf(buffer, "%s %s %s %lf %lf %lf", fileStart, fileEnd,car, &carDistance, &carCost, &carTime);    
        }
        // 创建一个新节点并填充信息
        Node* newNode = InitNode();
        strcpy(newNode->info.start, fileStart);
        strcpy(newNode->info.end, fileEnd);
        newNode->info.infoCar.distance = carDistance;
        newNode->info.infoCar.cost = carCost;
        newNode->info.infoCar.time = carTime;
        newNode->info.infoTrain.cost = trainCost;
        newNode->info.infoTrain.time = trainTime;

        // 将新节点添加到链表中
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    fclose(file);
}
