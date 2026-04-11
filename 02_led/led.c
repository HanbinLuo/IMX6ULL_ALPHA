#include <linux/types.h>
#include <linux/module.h>  // 模块支持
#include <linux/fs.h>      // file_operations 结构体
#include <linux/cdev.h>    // cdev 字符设备结构
#include <linux/slab.h>    // 内存分配
#include <linux/uaccess.h> // copy_to/from_user
#include <linux/init.h>    // __init, __exit 宏
#include <linux/io.h>

#define LED_MAJOR 201  /* 主设备号 */
#define LED_NAME "led" /* 设备名     */

#define LEDOFF 0 /* 关灯 */
#define LEDON 1  /* 开灯 */

#define CCM_CCGR1_BASE (0X020C406C)
#define SW_MUX_GPIO1_IO03_BASE (0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE (0X020E02F4)
#define GPIO1_DR_BASE (0X0209C000)
#define GPIO1_GDIR_BASE (0X0209C004)

static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;

void led_switch(u8 sta)
{
    u32 val = 0;
    if (sta == LEDON)
    {
        val = readl(GPIO1_DR);
        val &= ~(1 << 3);
        writel(val, GPIO1_DR);
    }
    else if (sta == LEDOFF)
    {
        val = readl(GPIO1_DR);
        val |= (1 << 3);
        writel(val, GPIO1_DR);
    }
}

static int led_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int led_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t led_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
    return 0;
}

static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
    int retvalue;
    unsigned char databuf[1];
    unsigned char ledstat;

    retvalue = copy_from_user(databuf, buf, 1);
    if (retvalue < 0)
    {
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }

    if (databuf[0] == '1' || databuf[0] == 1)
        led_switch(LEDON);
    else if (databuf[0] == '0' || databuf[0] == 0)
        led_switch(LEDOFF);

    return 0;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .read = led_read,
    .write = led_write,
};

static int __init led_init(void)
{
    int retvalue = 0;

    /* 1、映射寄存器地址 */
    IMX6U_CCM_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    SW_MUX_GPIO1_IO03 = ioremap(SW_MUX_GPIO1_IO03_BASE, 4);
    SW_PAD_GPIO1_IO03 = ioremap(SW_PAD_GPIO1_IO03_BASE, 4);
    GPIO1_DR = ioremap(GPIO1_DR_BASE, 4);
    GPIO1_GDIR = ioremap(GPIO1_GDIR_BASE, 4);

    /* 2、初始化IO复用 */
    writel(0x5, SW_MUX_GPIO1_IO03); /* 复用为GPIO1_IO03 */

    writel(0X10B0, SW_PAD_GPIO1_IO03);
    /* 4、初始化GPIO */
    writel(0X0000008, GPIO1_GDIR); /* GPIO1_IO03设置为输出 */

    /* 5、设置GPIO1_IO03输出低电平，打开LED0 */
    writel(0X0, GPIO1_DR);

    retvalue = register_chrdev(LED_MAJOR, LED_NAME, &led_fops);
    if (retvalue < 0)
    {
        printk("register chrdev failed!\r\n");
        return -EIO;
    }
    return 0;
}

static void __exit led_exit(void)
{
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    /* 注销字符设备驱动 */
    unregister_chrdev(LED_MAJOR, LED_NAME);
}

module_init(led_init);
module_exit(led_exit);

/*
 * LICENSE和作者信息
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("lhb");
