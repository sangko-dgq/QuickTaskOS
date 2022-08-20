#include <stdbool.h>
#include "stdlib.h"
#include "string.h"
#include "os_device.h"

/*Global device linked list*/
device_t *device_list = NULL;

/*Links through the linked list, query whether the device exists*/
static bool device_is_exists(device_t *dev)
{
    /*Create a local variable for time to operate without destroying the actual linked list data*/
    device_t *dl = device_list;
    while (dl != NULL)
    {
        if (strcmp(dl->name, dev->name) == 0)
            return true;
        /*Finger to the next node to continue to find*/
        dl = (device_t *)dl->next;
    }
    return false;
}

/*Insert the linked list, insert the device to the linked list*/
static int device_list_inster(device_t *dev)
{
    device_t *dl = device_list;

    /*If the linked list is empty*/
    if (NULL == device_list)
    {
        device_list = dev;
        dev->next = NULL;
    }
    /*The chain list has nodes*/
    else
    {
        /*If the next node of the linked list is not empty (with device)*/
        /*Until the next node is empty (to the end of the linked list)*/
        while (NULL != dl->next)
            dl = (device_t *)dl->next;

        /*Insert the device at the end*/
        dl->next = (struct device_ops *)dev;
        dl->next = NULL;
    }
    return 1;
}

/*device register*/
int device_register(device_t *dev)
{
    /*如果设备为空,或设备名字为空或设备操作为空，或者链表上已存在该设备*/
    if (NULL == dev || device_is_exists(dev) || NULL == dev->name || NULL == dev->dops)
        return 0;
    /*否则，向链表插入设备*/
    return device_list_inster(dev);
}

/*device find*/
device_t *device_find(const char *name)
{
    device_t *dl = device_list;
    /*遍历检索，找到就返回*/
    while (dl != NULL)
    {
        if (strcmp(dl->name, name) == 0)
            return dl;
        dl = (device_t *)dl->next;
    }
    /*遍历完，还未找到*/
    return NULL;
}

/*device read*/
int device_read(device_t *dev, int pos, void *buffer, int size)
{
    /*传入为空*/
    if (!dev || !(dev->dops->read))
        return 0;
    /*传入设备不为空*/
    return dev->dops->read(dev, pos, buffer, size);
}

/*device write*/
int device_write(device_t *dev, int pos, void *buffer, int size)
{
    if (!dev || !(dev->dops->write))
        return 0;
    return dev->dops->write(dev, pos, buffer, size);
}

/*device control*/
int device_control(device_t *dev, int cmd, void *arg)
{
    if (!dev || !(dev->dops->control))
        return 0;
    return dev->dops->control(dev, cmd, arg);
}
