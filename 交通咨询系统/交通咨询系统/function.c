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
        printf("查询结束\n");
    }
}

void DeleteNode(Node** head, char start[], char end[], const char* filename) {
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

    int found = 0;  // 标记是否找到匹配节点

    while (fscanf(file, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &carDistance, &carCost, &carTime, train, &trainCost, &trainTime) == 9) {
        // 第一种格式匹配成功
        if (!(strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0) && !(strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0)) {
            // 不是匹配节点，将信息写入临时文件
            fprintf(temp, "%s %s %s %.2lf %.2lf %.2lf %s %.2lf %.2lf\n", fileStart, fileEnd, car, carDistance, carCost, carTime, train, trainCost, trainTime);
        }
        else {
            // 是匹配节点
            found = 1;  // 找到匹配节点

            // 删除链表中的节点
            Node* current = *head;
            Node* prev = NULL;

            while (current != NULL) {
                if ((strcmp(current->info.start, start) == 0 && strcmp(current->info.end, end) == 0) ||
                    (strcmp(current->info.start, end) == 0 && strcmp(current->info.end, start) == 0)) {
                    if (prev == NULL) {
                        *head = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }
                    free(current);
                    break;
                }

                prev = current;
                current = current->next;
            }
        }
    }

    fclose(file);
    fclose(temp);

    // 删除原始文件并重命名临时文件
    remove(filename);
    rename(tempname, filename);

    // 打印删除成功的信息
    if (found) {
        printf(" '%s' 和 '%s'删除成功\n", start, end);
    }
    else {
        printf("未找到匹配的节点: '%s' 和 '%s'\n", start, end);
    }
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


void AddNode(Node** head, const char* filename, const char* start, const char* end, double CarDistance, double CarCost, double Cartime, double TrainCost, double TrainTime) {

    // 1. 打开文件
    FILE* file = fopen(filename, "r+");  // 以读写模式打开文件
    if (file == NULL) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    // 2. 定义文件和链表相关的变量
    char fileStart[V], fileEnd[V], car[V], train[V];
    double fileCarDistance, fileCarCost, fileCarTime, fileTrainCost, fileTrainTime;

    long currentPosition = 0;  // 记录当前文件位置
    int found = 0;  // 标记是否找到匹配节点

    // 3. 循环读取文件内容，查找匹配节点
    while (fscanf(file, "%s %s %s %lf %lf %lf %s %lf %lf", fileStart, fileEnd, car, &fileCarDistance, &fileCarCost, &fileCarTime, train, &fileTrainCost, &fileTrainTime) == 9) {
        if (strcmp(fileStart, start) == 0 && strcmp(fileEnd, end) == 0 || strcmp(fileStart, end) == 0 && strcmp(fileEnd, start) == 0) {
            // 找到匹配节点，更新其数据
            fseek(file, currentPosition, SEEK_SET);  // 移动文件指针到当前行的开头
            fprintf(file, "%s %s 私家车 %.2f %.2f %.2f 火车 %.2f %.2f\n", start, end, CarDistance, CarCost, Cartime, TrainCost, TrainTime);
            found = 1;  // 找到并更新后标记为true
            break;  // 找到并更新后跳出循环
        }
        currentPosition = ftell(file);  // 记录当前文件位置
    }

    // 4. 如果没有找到匹配节点，追加新节点的数据到文件末尾
    if (!found) {
        // 移动文件指针到文件末尾，获取文件长度
        fseek(file, 0, SEEK_END);
        long fileLength = ftell(file);

        // 如果文件不为空，且最后一个字符不是换行符，则在追加新节点前添加换行符
        if (fileLength > 0) {
            fseek(file, -1, SEEK_END);
            char lastChar = fgetc(file);
            if (lastChar != '\n') {
                fprintf(file, "\n");
            }
        }

        // 再次移动文件指针到文件末尾，准备追加新节点
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s %s 私家车 %.2f %.2f %.2f 火车 %.2f %.2f\n", start, end, CarDistance, CarCost, Cartime, TrainCost, TrainTime);
    }

    // 5. 关闭文件
    fclose(file);

    // 6. 在链表中追加新节点
    Node* newNode = InitNode();  // 创建新节点
    strcpy(newNode->info.start, start);
    strcpy(newNode->info.end, end);
    newNode->info.infoCar.distance = CarDistance;
    newNode->info.infoCar.cost = CarCost;
    newNode->info.infoCar.time = Cartime;
    newNode->info.infoTrain.cost = TrainCost;
    newNode->info.infoTrain.time = TrainTime;

    // 将新节点插入链表
    if (*head == NULL) {
        *head = newNode;  // 如果链表为空，直接将新节点设为头节点
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;  // 移动到链表末尾
        }
        temp->next = newNode;  // 将新节点插入末尾
        newNode->pre = temp;
    }
}
