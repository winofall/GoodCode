#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <head.h>
#include "function.c"
int main()
{
  char password[100]={'6','6','6','6'},Up[100];
  int n;
  printf("--------欢迎使用交通资讯系统--------\n");
while(n){
  printf("-----------请选择以下功能-----------\n");
  printf("-------------0.退出系统-------------\n");
  printf("-----------1.查询最短路径-----------\n");
  printf("-----------2.查询最少金额-----------\n");
  printf("-----------3.查询最短时间-----------\n");
  printf("----------4.进入管理员系统----------\n");
  scanf("%d",&n);
  switch(n){
    case 0:printf("退出成功\n");
    case 1://查询最短路径;
    case 2://查询最少金额;
    case 3://查询最短时间;
    case 4://进入管理员系统;
    scanf("%s",Up);
    if(strcmp(Up,password)){
      printf("进入成功\n");
      while(n){
          printf("-----------请选择以下功能-----------\n");
          printf("-------------1.增加信息-------------\n");
          printf("-----------2.查询所有信息-----------\n");
          printf("-------------3.减少信息-------------\n");
          printf("----------4.退出管理员系统----------\n");
          scanf("%d",&n);
          switch(n){
            case 0:printf("退出模式成功\n");
            case 1://增加信息;
            case 2://查询所有信息;
            case 3://减少信息;
            case 4://退出管理员系统;    
            }
    }
    else{
      printf("密码错误\n");
    }
  }
}
system("pause");
return 0;
}
