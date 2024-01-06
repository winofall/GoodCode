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
        // 其他初始化工作...
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
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:%lf,时间:%lf.", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
            }
            else {
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf.", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time);
            }
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

void CheckAllNode(Node* head)
{
    Node* p;
    p = head->next;
    while (p != NULL)
    {
        if ((p->info).infoTrain.cost != -1) {
            printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:%lf,时间:%lf\n", (p->info).start, (p->info).end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
        }
        else {
            printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf\n", (p->info).start, (p->info).end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time);
        }
        p = p->next;
    }
    if (p == NULL)
    {
        printf("查询结束");
    }
}

void DeleteNode(Node* head, char start[], char end[], const char* filename) {
    FILE* file = fopen(filename, "r"); // 打开文件
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

    char fileStart[V], fileEnd[V], car[V], train[V];
    double carDistance, carCost, carTime, trainCost, trainTime;

    while (fscanf(file, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime, train, &trainCost, &trainTime) == 9) {
        // 第一种格式匹配成功
        if (!(strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0) && !(strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0)) {
            // 不是匹配节点，将信息写入临时文件
            fprintf(temp, "%s %s %s %.2lf %.2lf %.2lf %s %.2lf %.2lf\n", fileStart, fileEnd, car, carDistance, carCost, carTime, train, trainCost, trainTime);
        }
        else {
            // 是匹配节点
            printf(" '%s' 和 '%s'删除成功\n", start, end);
        }
    }

    fclose(file);
    fclose(temp);

    // 删除原始文件并重命名临时文件
    remove(filename);
    rename(tempname, filename);
}


void CreateNode(Node** head, const char* filename) {
    FILE* file = fopen(filename, "r"); // 使用 fopen 打开文件
    if (file == NULL) {
        printf("无法打开: %s\n", filename);
        return;
    }

    char fileStart[V], fileEnd[V], car[V], train[V];
    double carDistance, carCost, carTime, trainCost, trainTime;

    while (fscanf(file, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime, train, &trainCost, &trainTime) == 9) {
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
        if (*head == NULL) {
            *head = newNode;
        }
        else {
            Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }


    fclose(file);
}


void AddNode(const char* filename, const char* start, const char* end, double CarDistance, double CarCost, double Cartime, double TrainCost, double TrainTime) {
    FILE* file = fopen(filename, "r+");  // 以读写模式打开文件
    if (file == NULL) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    char fileStart[V], fileEnd[V], car[V], train[V];
    double fileCarDistance, fileCarCost, fileCarTime, fileTrainCost, fileTrainTime;

    long currentPosition = 0;  // 记录当前文件位置
    int found = 0;  // 标记是否找到匹配节点

    // 处理第一种格式的输入
    while (fscanf(file, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &fileCarDistance, &fileCarCost, &fileCarTime, train, &fileTrainCost, &fileTrainTime) == 9) {
        if (strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0 || strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0) {
            // 找到匹配节点，更新其数据
            fseek(file, currentPosition, SEEK_SET);  // 移动文件指针到当前行的开头
            fprintf(file, "%s %s 私家车:%.2lf %.2lf %.2lf 火车:%.2lf %.2lf\n", start, end, CarDistance, CarCost, Cartime, TrainCost, TrainTime);
            found = 1;  // 找到并更新后标记为true
            break;  // 找到并更新后跳出循环
        }
        currentPosition = ftell(file);  // 记录当前文件位置
    }

    // 处理第二种格式的输入
    if (!found) {  // 如果第一种格式找到了匹配节点，则不再处理第二种格式
        rewind(file); // 将文件指针重新定位到文件开头
        currentPosition = 0;  // 重新记录当前文件位置

        while (fscanf(file, "%s %s %s %lf %lf %lf", fileStart, fileEnd, car, &fileCarDistance, &fileCarCost, &fileCarTime) == 6) {
            if (strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0 || strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0) {
                // 找到匹配节点，更新其数据
                fseek(file, currentPosition, SEEK_SET);  // 移动文件指针到当前行的开头
                fprintf(file, "%s %s 私家车:%.2lf %.2lf %.2lf\n", start, end, CarDistance, CarCost, Cartime);
                break;  // 找到并更新后跳出循环
            }
            currentPosition = ftell(file);  // 记录当前文件位置
        }
    }

    fclose(file);
}
