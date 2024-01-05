#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "head.h"
Node* InitNode() {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 分配内存
    if (newNode != NULL) {
        // 初始化结构体成员
        newNode->next = NULL;
        newNode->pre = NULL;
    }
    return newNode;
}
void CheckNode(Node* head, char start[], char end[])
{
    Node* p;
    p = head;
    while (p != NULL)
    {
        if (!(strcmp(start, (p->info).start)) && !(strcmp(end, (p->info).end)))
        {
            if ((p->info).infoTrain.cost != -1) {
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:lf,时间:lf.", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
                break;
            }
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
void DeleteNode(Node* head, char start[], char end[], const char* filename) {
    FILE* file = fopen(filename, "r");//打开文件
    if (file == NULL) {
        printf("无法打开: %s\n", filename);
        return;
    }

    char tempname[] = "temp.txt";
    FILE* temp = fopen(tempname, "w");
    if (temp == NULL) {
        printf("创建出错\n");
        fclose(file);
        return;
    }

    char buffer[256]; // 假设一行不超过 256 个字符
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char fileStart[V], fileEnd[V], car[V], train[V];
        double carDistance, carCost, carTime, trainCost, trainTime;

        int result1 = sscanf(buffer, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime, train, &trainCost, &trainTime);

        int result2 = sscanf(buffer, "%s %s %s %lf %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime);
        if (result1 == 9) {
            // 第一种格式匹配成功
            if ((!(strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0))||(!(strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0))) {
                // 不是匹配节点，将信息写入临时文件
                fprintf(temp, "%s %s %s %lf %lf %lf %s %lf %lf\n", fileStart, fileEnd,car, carDistance, carCost, carTime,train, trainCost, trainTime);
            }
            else {
                // 是匹配节点
                printf(" '%s' 和 '%s'删除成功\n", start, end);
            }
        }
        else if (result2 == 6) {
            // 第二种格式匹配成功
            if (!(strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0)) {
                // 不是匹配节点，将信息写入临时文件
                fprintf(temp, "%s %s %s %lf %lf %lf\n", fileStart,car, fileEnd, carDistance, carCost, carTime);
            }
            else {
                // 是匹配节点
                printf(" '%s'和'%s' 删除成功\n", start, end);
            }
        }
        else {
            // 格式不匹配，可能是其他情况
            printf("格式不匹配 %s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    // 删除原始文件并重命名临时文件
    remove(filename);
    rename(tempname, filename);
}
void CreateNode(Node* head, const char* filename) {
    FILE* file = fopen(filename, "r");//打开文件
    if (file == NULL) {
        printf("无法打开: %s\n", filename);
        return;
    }

    char buffer[256]; // 假设一行不超过 256 个字符
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char fileStart[V], fileEnd[V],car[V],train[V];
        double carDistance, carCost, carTime, trainCost, trainTime;

        int result1 = sscanf(buffer, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car,&carDistance, &carCost, &carTime,train, &trainCost, &trainTime);

        int result2 = sscanf(buffer, "%s %s %s %lf %lf %lf", fileStart, fileEnd,car, &carDistance, &carCost, &carTime);

        if (result1 == 9) {
            // 第一种格式匹配成功
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
        else if (result2 == 6) {
            // 第二种格式匹配成功
            // 创建一个新节点并填充信息
            Node* newNode = InitNode();
            strcpy(newNode->info.start, fileStart);
            strcpy(newNode->info.end, fileEnd);
            newNode->info.infoCar.distance = carDistance;
            newNode->info.infoCar.cost = carCost;
            newNode->info.infoCar.time = carTime;
            newNode->info.infoTrain.cost = -1;  // 设置一个特殊的值表示未使用的字段
            newNode->info.infoTrain.time = -1;
            // 将新节点添加到链表中
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        else {
            // 格式不匹配，可能是其他情况
            printf("格式不匹配: %s\n", buffer);
        }
    }
    fclose(file);
}
void AddNode(Node* head, char start[], char end[], double CarDistance, double CarCost, double Cartime, double TrainCost, double TrainTime) {
    Node* current = head->next;  // 从链表的第一个节点开始
    while (current != NULL) {
        if ((strcmp(current->info.start, start) == 0 && strcmp(current->info.end, end) == 0)||(strcmp(current->info.start, end) == 0 && strcmp(current->info.end, start) == 0)) {
            // 找到匹配节点，更新其数据
            if (current->info.infoTrain.cost != -1) {
                // 第一种格式
                current->info.infoCar.distance = CarDistance;
                current->info.infoCar.cost = CarCost;
                current->info.infoCar.time = Cartime;
                current->info.infoTrain.cost = TrainCost;
                current->info.infoTrain.time = TrainTime;
            }
            else {
                // 第二种格式
                current->info.infoCar.distance = CarDistance;
                current->info.infoCar.cost = CarCost;
                current->info.infoCar.time = Cartime;
            }

            printf(" '%s' 和'%s' 更新成功\n", start, end);
            return;
        }
        current = current->next;
    }

    // 如果未找到匹配的节点，可以选择创建一个新的节点
    Node* newNode = InitNode();
    strcpy(newNode->info.start, start);
    strcpy(newNode->info.end, end);

    if (TrainCost != -1) {
        // 第一种格式
        newNode->info.infoCar.distance = CarDistance;
        newNode->info.infoCar.cost = CarCost;
        newNode->info.infoCar.time = Cartime;
        newNode->info.infoTrain.cost = TrainCost;
        newNode->info.infoTrain.time = TrainTime;
    }
    else {
        // 第二种格式
        newNode->info.infoCar.distance = CarDistance;
        newNode->info.infoCar.cost = CarCost;
        newNode->info.infoCar.time = Cartime;
        newNode->info.infoTrain.cost = -1;  // 设置一个特殊的值表示未使用的字段
        newNode->info.infoTrain.time = -1;
    }

    // 将新节点添加到链表中
    current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    printf("路径 '%s' 和'%s' 增加成功.\n", start, end);
}
