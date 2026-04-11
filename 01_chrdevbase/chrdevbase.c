#include <linux/types.h>
#include <linux/module.h>   // 模块支持
#include <linux/fs.h>       // file_operations 结构体
#include <linux/cdev.h>     // cdev 字符设备结构
#include <linux/slab.h>     // 内存分配
#include <linux/uaccess.h>  // copy_to/from_user
#include <linux/init.h>     // __init, __exit 宏

#define CHRDEVBASE_MAJOR	200				/* 主设备号 */
#define CHRDEVBASE_NAME		"chrdevbase" 	/* 设备名     */

static char readbuf[100];		/* 读缓冲区 */
static char writebuf[100];		/* 写缓冲区 */
static char kerneldata[] = {"kernel data!"};

/*
 * @description		: 打开设备
 * @param - inode 	: 传递给驱动的inode
 * @param - filp 	: 设备文件，file结构体有个叫做private_data的成员变量
 * 					  一般在open的时候将private_data指向设备结构体。
 * @return 			: 0 成功;其他 失败
 */
static int chrdevbase_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "chrdevbase open!\r\n");
	return 0;
}

/*
 * @description		: 从设备读取数据 
 * @param - filp 	: 要打开的设备文件(文件描述符)
 * @param - buf 	: 返回给用户空间的数据缓冲区
 * @param - cnt 	: 要读取的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 读取的字节数，如果为负值，表示读取失败
 */
static ssize_t chrdevbase_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
	int retvalue = 0;
	
	/* 向用户空间发送数据 */
	memcpy(readbuf, kerneldata, sizeof(kerneldata));
	retvalue = copy_to_user(buf, readbuf, cnt);
	       if(retvalue == 0){
		       printk(KERN_INFO "kernel senddata ok!\r\n");
	       }else{
		       printk(KERN_INFO "kernel senddata failed!\r\n");
	       }
       
		printk(KERN_INFO "chrdevbase read!\r\n");
	       return 0;
}

/*
 * @description		: 向设备写数据 
 * @param - filp 	: 设备文件，表示打开的文件描述符
 * @param - buf 	: 要写给设备写入的数据
 * @param - cnt 	: 要写入的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 写入的字节数，如果为负值，表示写入失败
 */
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
	int retvalue = 0;
	printk(KERN_INFO "ENTER chrdevbase write!\r\n");
	/* 接收用户空间传递给内核的数据并且打印出来 */
// 	copy_from_user 函数定义在 Linux 内核的 include/linux/uaccess.h 头文件中，
// 	并在内核源码的 arch 相关目录（如 arch/arm/lib/uaccess_with_memcpy.c 或 arch/x86/lib/usercopy_64.c 等）实现。
// 	作用：用于从用户空间拷贝数据到内核空间，常用于驱动开发中安全地接收用户数据。
	retvalue = copy_from_user(writebuf, buf, cnt);
	       if(retvalue == 0){
		       printk(KERN_INFO "kernel recevdata:%s\r\n", writebuf);
	       }else{
		       printk(KERN_INFO "kernel recevdata failed!\r\n");
	       }
       
	       //printk(KERN_INFO "chrdevbase write!\r\n");
	       return 0;
}

/*
 * @description		: 关闭/释放设备
 * @param - filp 	: 要关闭的设备文件(文件描述符)
 * @return 			: 0 成功;其他 失败
 */
static int chrdevbase_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "chrdevbase release！\r\n");
	return 0;
}

/*
 * 设备操作函数结构体
 */
static struct file_operations chrdevbase_fops = {
	.owner = THIS_MODULE,	
	.open = chrdevbase_open,
	.read = chrdevbase_read,
	.write = chrdevbase_write,
	.release = chrdevbase_release,
};

/*
 * @description	: 驱动入口函数 
 * @param 		: 无
 * @return 		: 0 成功;其他 失败
 */
static int __init chrdevbase_init(void)
{
	int retvalue = 0;

	/* 注册字符设备驱动 */
	retvalue = register_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME, &chrdevbase_fops);
	       if(retvalue < 0){
		       printk(KERN_INFO "chrdevbase driver register failed\r\n");
	       }
	       printk(KERN_INFO "chrdevbase init!\r\n");
	       return 0;
}

/*
 * @description	: 驱动出口函数
 * @param 		: 无
 * @return 		: 无
 */
static void __exit chrdevbase_exit(void)
{
	/* 注销字符设备驱动 */
	unregister_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME);
	printk(KERN_INFO "chrdevbase exit!\r\n");
}

/* 
 * 将上面两个函数指定为驱动的入口和出口函数 
 */
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);

/* 
 * LICENSE和作者信息
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("lhb");

