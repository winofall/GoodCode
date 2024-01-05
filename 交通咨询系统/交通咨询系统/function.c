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
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:%lf,时间:%lf.\n", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
                break;
            }
            else {
                printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf.\n", start, end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time);
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
void CheckAllNode(Node* head)
{
    Node* p;
    p = head;
    while (p != NULL)
    {
        if ((p->info).infoTrain.cost != -1) {
            printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf;火车:花费:%lf,时间:%lf.\n",(p->info).start, (p->info).end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time, (p->info).infoTrain.cost, (p->info).infoTrain.time);
            break;
        }
        else {
            printf("%s %s 私家车:距离:%lf,花费:%lf,时间:%lf.\n", (p->info).start, (p->info).end, (p->info).infoCar.distance, (p->info).infoCar.cost, (p->info).infoCar.time);
        }
        p = p->next;
    }
    if (p == NULL)
    {
        printf("查询结束");
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
            if ((!(strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0)) || (!(strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0))) {
                // 不是匹配节点，将信息写入临时文件
                fprintf(temp, "%s %s %s %lf %lf %lf %s %lf %lf\n", fileStart, fileEnd, car, carDistance, carCost, carTime, train, trainCost, trainTime);
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
                fprintf(temp, "%s %s %s %lf %lf %lf\n", fileStart, car, fileEnd, carDistance, carCost, carTime);
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
        char fileStart[V], fileEnd[V], car[V], train[V];
        double carDistance, carCost, carTime, trainCost, trainTime;

        int result1 = sscanf(buffer, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime, train, &trainCost, &trainTime);

        int result2 = sscanf(buffer, "%s %s %s %lf %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime);

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
            Node* prev = NULL;

            if (current == NULL) {
                head = newNode;
            }
            else {
                // 遍历链表的代码
                while (current != NULL&&current->next != NULL) {
                    prev = current;
                    current = current->next;
                }

                if (prev != NULL) {
                    prev->next = newNode;
                }
            }
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
            Node* prev = NULL;

            if (current == NULL) {
                head = newNode;
            }
            else {
                // 遍历链表的代码
                while (current != NULL) {
                    prev = current;
                    current = current->next;
                }

                if (prev != NULL) {
                    prev->next = newNode;
                }
            }

        }
        else {
            // 格式不匹配，可能是其他情况
            printf("格式不匹配: %s\n", buffer);
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

    char buffer[256]; // 假设一行不超过 256 个字符
    long currentPosition = 0;  // 记录当前文件位置

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char fileStart[V], fileEnd[V], car[V], train[V];
        double fileCarDistance, fileCarCost, fileCarTime, fileTrainCost, fileTrainTime;

        int result1 = sscanf(buffer, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &fileCarDistance, &fileCarCost, &fileCarTime, train, &fileTrainCost, &fileTrainTime);

        int result2 = sscanf(buffer, "%s %s %s %lf %lf %lf", fileStart, fileEnd, car, &fileCarDistance, &fileCarCost, &fileCarTime);

        if (result1 == 9) {
            // 第一种格式匹配成功
            if (strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0) {
                // 找到匹配节点，更新其数据
                fseek(file, currentPosition, SEEK_SET);  // 移动文件指针到当前行的开头
                fprintf(file, "%s %s 私家车:%.2lf %.2lf %.2lf 火车:%.2lf %.2lf\n", start, end, CarDistance, CarCost, Cartime, TrainCost, TrainTime);
                break;  // 找到并更新后跳出循环
            }
        }
        else if (result2 == 6) {
            // 第二种格式匹配成功
            if (strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0) {
                // 找到匹配节点，更新其数据
                fseek(file, currentPosition, SEEK_SET);  // 移动文件指针到当前行的开头
                fprintf(file, "%s %s 私家车:%.2lf %.2lf %.2lf\n", start, end, CarDistance, CarCost, Cartime);
                break;  // 找到并更新后跳出循环
            }
        }

        currentPosition = ftell(file);  // 记录当前文件位置
    }

    fclose(file);
}
