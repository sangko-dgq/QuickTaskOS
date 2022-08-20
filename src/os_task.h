/**
 * @file    OSTask.h
 * ref:https://github.com/FASTSHIFT/X-TRACK/tree/main/Software/X-Track/Libraries/MillisTaskManager
 * @brief   Ultra -lightweight time -sharing collaborative task scheduler can
 *          replace the old Millis () rotation scheme, not relying on Arduinoapi
 */

#ifndef _OSTASK_
#define _OSTASK_

#define MTM_USE_CPU_USAGE 0

#include <cstdint>

#ifndef uint32_t
#include "stdint.h"
#endif // !Uint32_t

class OSTask {
public:
  typedef void (*TaskFunction_t)(); //任务回调函数的函数指针
  struct Task {
    bool State;              //任务状态
    TaskFunction_t Function; //任务函数指针
    uint32_t Time;           //任务时间
    uint32_t TimePrev;       //任务上一次触发时间
    uint32_t TimeCost;       //任务时间开销(us)
    uint32_t TimeError;      //误差时间
    struct Task *Next;       //下一个节点
  };
  typedef struct Task Task_t; //任务类型定义

  explicit OSTask(bool priorityEnable = false);
  ~OSTask();

  Task_t *Register(TaskFunction_t func, uint32_t timeMs, bool state = true);
  Task_t *Find(TaskFunction_t func);
  Task_t *GetPrev(Task_t *task);
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
  Task_t *Head;        //任务链表头
  Task_t *Tail;        //任务链表尾
  bool PriorityEnable; //优先级使能
};

#endif