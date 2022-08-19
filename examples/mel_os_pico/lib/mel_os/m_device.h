//
// Created by 22012 on 2022/8/19.
//

#ifndef MEL_OS_PICO_M_DEVICE_H
#define MEL_OS_PICO_M_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif

/*链表节点 - 设备*/
/* type : struct_t */
typedef struct device_ops device_ops_t;
typedef struct device device_t;
/*struct*/
struct device
{
    const char *name;
    struct device_ops *dops;
    struct device_ops *next; /*下一个操作节点*/
};

/*链表节点 - 设备操作结构体节点*/
struct device_ops
{
    /*函数指针*/
    int (*init)(device_t *dev);

    int (*open)(device_t *dev, int oflag);

    int (*close)(device_t *dev);

    int (*read)(device_t *dev, int pos, const void *buffer, int size);

    int (*write)(device_t *dev, int pos, void *buffer, int size);

    int (*control)(device_t *dev, int cmd, void *args);
};


int device_register(device_t *dev);

device_t *device_find(const char *name);

int device_read(device_t *dev, int pos, void *buffer, int size);

int device_write(device_t *dev, int pos, void *buffer, int size);

int device_control(device_t *dev, int cmd, void *arg);

#ifdef __cplusplus
}// extern "C"
#endif


#endif //MEL_OS_PICO_M_DEVICE_H
