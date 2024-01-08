#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "head.h"

int main()
{
    char password[100] = { '6', '6', '6', '6' }, Up[100];
    char fileName[100];
    printf("请输入读入的文本文件名:");
    scanf("%s", fileName);
    int n = 1;
    Node* head = InitNode();
    MGraph m;
    m.nums = 1;
    m.head = head;
    Node** h =&m.head;
    while (!CreateNode(&m, h, fileName)) {
        printf("请重新输入读入的文本文件名:");
        scanf("%s", fileName);
    };
    char start[20], end[20];
    double CarDis, CarCost, CarTime, TrainCost, TrainTime;
    printf("--------欢迎使用交通资讯系统--------\n");
    while (n)
    {
        printf("-----------请选择以下功能-----------\n");
        printf("-------------0.退出系统-------------\n");
        printf("-----------1.查询最短路径-----------\n");
        printf("-----------2.查询最少金额-----------\n");
        printf("-----------3.查询最短时间-----------\n");
        printf("----------4.进入管理员系统----------\n");
        scanf("%d", &n);
        switch (n)
        {
        case 0:
            printf("退出成功\n");
            break;
        case 1: // 查询最短路径;
            printf("请输入起点:");
            scanf("%s", start);
            printf("请输入终点:");
            scanf("%s", end);
            GetDis(&m, &start, &end);
            break;
        case 2: // 查询最少金额;
            printf("请输入起点:");
            scanf("%s", start);
            printf("请输入终点:");
            scanf("%s", end);
            GetMoney(&m, start, end);
            break;
        case 3: // 查询最短时间;
            printf("请输入起点:");
            scanf("%s", start);
            printf("请输入终点:");
            scanf("%s", end);
            GetTime(&m, start, end);
            break;
        case 4: // 进入管理员系统;
            printf("请输入密码:");
            scanf("%s", Up);
            if (strcmp(Up, password) == 0)
            {
                n = 1;
                printf("进入成功\n");
                while (n && n != 4)
                {
                    printf("-----------请选择以下功能-----------\n");
                    printf("-------------0.退出系统-------------\n");
                    printf("-------------1.增加信息-------------\n");
                    printf("-----------2.查询所有信息-----------\n");
                    printf("-------------3.减少信息-------------\n");
                    printf("----------4.退出管理员系统----------\n");
                    scanf("%d", &n);
                    switch (n)
                    {
                    case 0:
                        printf("退出模式成功\n");
                        break;
                    case 1:scanf("%s%s%lf%lf%lf%lf%lf", start, end, &CarDis, &CarCost, &CarTime, &TrainCost, &TrainTime);
                        AddNode(m,h, fileName, start, end, CarDis, CarCost, CarTime, TrainCost, TrainTime);  // 增加信息;
                        break;
                    case 2:CheckAllNode(head);// 查询所有信息;
                        break;
                    case 3:scanf("%s%s", start, end);
                        DeleteNode(h, start, end, fileName);// 减少信息;
                        break;
                    case 4: // 退出管理员系统;
                        printf("退出模式成功\n");
                        break;
                    default:
                        printf("输入错误\n");
                        break;
                    }
                }
            }
            else
            {
                printf("密码错误\n");
            }
            break;
        default:
            printf("输入错误");
            break;
        }
    }
    free(head);
    system("pause");
    return 0;
}
