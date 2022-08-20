/**
 * @file os_device.h
 * @brief OS device manager
 * @version 0.1
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) sangko-dgq
 * 
 */
#ifndef _OS_DEVICE_
#define _OS_DEVICE_

#ifdef __cplusplus
extern "C"
{
#endif

    /* type : struct_t */
    typedef struct device_ops device_ops_t;
    typedef struct device device_t;

    /* List node - device */
    struct device
    {
        const char *name;
        struct device_ops *dops;
        struct device_ops *next; /*next node*/
    };

    /*List node - device operations */
    struct device_ops
    {
        /*Function pointer*/
        int (*init)(device_t *dev);
        int (*open)(device_t *dev, int oflag);
        int (*close)(device_t *dev);
        int (*read)(device_t *dev, int pos, const void *buffer, int size);
        int (*write)(device_t *dev, int pos, void *buffer, int size);
        int (*control)(device_t *dev, int cmd, void *args);
    };

    /* External interface function */
    int device_register(device_t *dev);
    device_t *device_find(const char *name);
    int device_read(device_t *dev, int pos, void *buffer, int size);
    int device_write(device_t *dev, int pos, void *buffer, int size);
    int device_control(device_t *dev, int cmd, void *arg);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _OS_DEVICE_
