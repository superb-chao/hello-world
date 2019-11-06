//
//  main.cpp
//  psac
//
//  Created by Pikachu on 2019/10/29.
//  Copyright © 2019 Pikachu. All rights reserved.
//
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
 
static int point = 0;//用于计算进程是否运行完成
struct PCB
{
    int pid;
    int priority;
    int time;
    PCB *next;
};

void tailCreate(PCB *L)
{
    srand((unsigned int)time(0));//以时间为随机数种子，保证每次随机数不一样
    PCB *s, *r = L;
    for (int i = 0; i<5; i++)//生成pcb
    {
        
        //随机时间为1到5
        int number = rand() % 5;
        while (number == 0)
            //如果是0就一直随机，直到出现不是0的为止
            number = rand() % 5;
        //tail_insert用尾插法初始化
        s = new PCB;
        s->pid = i + 1;
        s->priority = rand() % 5 + 1;    //随机优先数
        s->time = number;
        if (s->priority != 5 || r->next == NULL)//如果r->next==NULL表示为队列只有一个头结点，就直接插入
        {
            r->next = s;
            r = s;
        }
        if ((s->priority == 5) && (r->next != NULL))//如果队列不为空，就将它放在头结点后面
        {
            s->next = L->next;
            L->next = s;
        }
    }
    r->next = NULL;
}
 //？？
void run(PCB *L)//运行
{
    PCB *c = L;
    PCB *p = L;
 
    for (; L; L = L->next)
    {
        if (L->next == NULL)
            break;
        //由于存在存在头结点，所以从L->next开始
        L->next->priority = L->next->priority - 1;
        L->next->time = L->next->time - 1;
        if (L->next->time == 0)
            //如果运行时间为0，就将它移除队列中
        {
            cout << "run over" <<"->PID->"<< L->next->pid << endl;
            L->next->time = -1;
            L->next = L->next->next;
            //由于出现了L->next = L->next->next;这步，
            //接着执行for循环的第三个表达式，便跳过了L->next->next这个结点，接着执行L->next->next->next这个结点
            //所以需要判断一下L->next->next这个结点
            if (L->next != NULL&&L->next->time != 0)
            {
                L->next->priority = L->next->priority - 1;
                L->next->time = L->next->time - 1;
            }
 
 
                //如果L->next->next->time的值等于0,便会将它移除队列，接着执行L->next=L->next->next这步
                //所以需要while循环来判断
                while (L->next != NULL&&L->next->time == 0)
                {
                    cout << "run over" <<"->PID->"<< L->next->pid << endl;
                    L->next->time = -1;
                    L->next = L->next->next;
                    point = point + 1;
                    if (L->next != NULL)
                    {
                        L->next->priority = L->next->priority - 1;
                        L->next->time = L->next->time - 1;
                    }
                }
            point = point + 1;
        }
        if (L->next != NULL&&L->next->priority == 0)//如果优先数为0就将它变成0放在队首
        {
            //******
            PCB *q = L->next;
            L->next = L->next->next;
            q->priority = 5;
            q->next = c->next;
            c->next = q;
            //由于执行了L->next=L->next->next
            //所以又会执行上面那步同样地操作
            if (L->next != NULL&&L->next->time != 0)
            {
                L->next->priority = L->next->priority - 1;
                L->next->time = L->next->time - 1;
            }
            while (L->next != NULL&&L->next->time == 0)
            {
                cout << "run over" << "->PID->"<<L->next->pid << endl;
                L->next->time = -1;
                L->next = L->next->next;
                point = point + 1;
                if (L->next != NULL)
                {
                    L->next->priority = L->next->priority - 1;
                    L->next->time = L->next->time - 1;
                }
            }
        }
 
 
    }
    L = p;
}
 
int main()
{
    PCB *L, *m;
    L = new PCB;//初始化头结点
    L->next = NULL;
    tailCreate(L);
    m = L;
    L = L->next;
 
    cout << "=============" << endl;
    cout << "Init" << endl;
    cout << "==============" << endl;
    for (; L; L = L->next)
    {
        cout <<"PID :"<< L->pid << endl;
        cout << "Time :"<<L->time << endl;
        cout << "Priority :"<<L->priority << endl;
        cout << "******* " << endl;
        cout << endl;
    }
    cout << "=============" << endl;
    cout << "Init successful!" << endl;
    cout << "==============" << endl;
    cout << endl;
    cout << "run order!" << endl;
    while (point != 5)
    {
        run(m);
    }
    system("pause");
    return 0;
 
}
