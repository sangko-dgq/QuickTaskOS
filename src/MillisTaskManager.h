/**
  * @file    MillisTaskManager.h
  * @brief   超轻量级分时合作式任务调度器，可以替代旧的millis()轮询方案，不依赖ArduinoAPI
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MILLISTASKMANAGER_H
#define __MILLISTASKMANAGER_H

#define MTM_USE_CPU_USAGE 0

#include <cstdint>

class MillisTaskManager
{
public:
    typedef void(*TaskFunction_t)();//任务回调函数的函数指针
    struct Task
    {
        bool State;                //任务状态
        TaskFunction_t Function;   //任务函数指针
        uint32_t Time;             //任务时间
        uint32_t TimePrev;         //任务上一次触发时间
        uint32_t TimeCost;         //任务时间开销(us)
        uint32_t TimeError;        //误差时间
        struct Task* Next;         //下一个节点
    };
    typedef struct Task Task_t;//任务类型定义

    explicit MillisTaskManager(bool priorityEnable = false);
    ~MillisTaskManager();

    Task_t* Register(TaskFunction_t func, uint32_t timeMs, bool state = true);
    Task_t* Find(TaskFunction_t func);
    Task_t* GetPrev(Task_t* task);
    bool Logout(TaskFunction_t func);
    bool SetState(TaskFunction_t func, bool state);
    bool SetIntervalTime(TaskFunction_t func, uint32_t timeMs);
    uint32_t GetTimeCost(TaskFunction_t func);
    uint32_t GetTickElaps(uint32_t nowTick, uint32_t prevTick);
#if (MTM_USE_CPU_USAGE == 1)
    float GetCPU_Usage();
#endif
    void Running(uint32_t tick);

private:
    Task_t* Head;        //任务链表头
    Task_t* Tail;        //任务链表尾
    bool PriorityEnable; //优先级使能
};

#endif