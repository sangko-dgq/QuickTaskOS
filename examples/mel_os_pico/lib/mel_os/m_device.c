//
// Created by 22012 on 2022/8/19.
//
#include <stdbool.h>
#include "stdlib.h"
#include "string.h"

#include "m_device.h"

/*全局设备链表*/
device_t *device_list = NULL;

/*遍历链表，查询是否存在该设备*/
static bool device_is_exists(device_t *dev)
{
    /*创建一个局部变量，用来临时操作，不破坏实际链表数据*/
    device_t *dl = device_list;
    while (dl != NULL)
    {
        if (strcmp(dl->name, dev->name) == 0) return true;
        /*指向下一个节点继续查找*/
        dl = (device_t *) dl->next;
    }
    return false;
}

/*插入链表，向链表插入设备*/
static int device_list_inster(device_t *dev)
{
    device_t *dl = device_list;

    /*如果链表为空*/
    if (NULL == device_list)
    {
        device_list = dev;
        dev->next = NULL;
    }
        /*链表上有节点*/
    else
    {
        /*如果链表下一个节点不为空(有设备)*/
        /*直到下一节点为空（来到链表末尾）*/
        while (NULL != dl->next) dl = (device_t *) dl->next;

        /*在末尾将该设备插入*/
        dl->next = (struct device_ops *) dev;
        dl->next = NULL;
    }
    return 1;
}


/*设备注册*/
int device_register(device_t *dev)
{
    /*如果设备为空,或设备名字为空或设备操作为空，或者链表上已存在该设备*/
    if (NULL == dev || device_is_exists(dev) || NULL == dev->name || NULL == dev->dops) return 0;
    /*否则，向链表插入设备*/
    return device_list_inster(dev);
}

/*设备查*/
device_t *device_find(const char *name)
{
    device_t *dl = device_list;
    /*遍历检索，找到就返回*/
    while (dl != NULL)
    {
        if (strcmp(dl->name, name) == 0) return dl;
        dl = (device_t *) dl->next;
    }
    /*遍历完，还未找到*/
    return NULL;
}

/*设备读*/
int device_read(device_t *dev, int pos, void *buffer, int size)
{
    /*传入为空*/
    if (!dev || !(dev->dops->read)) return 0;
    /*传入设备不为空*/
    return dev->dops->read(dev, pos, buffer, size);
}

/*设备写*/
int device_write(device_t *dev, int pos, void *buffer, int size)
{
    if (!dev || !(dev->dops->write)) return 0;
    return dev->dops->write(dev, pos, buffer, size);
}

/*设备控制*/
int device_control(device_t *dev, int cmd, void *arg)
{
    if (!dev || !(dev->dops->control)) return 0;
    return dev->dops->control(dev, cmd, arg);
}




