/* 神秘点灯仪式 */
.global _start @全局标号

/*
IMX6ULL汇编点灯程序
1：配置CCM_CCGR1寄存器20C_406Ch
2: 配置IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03寄存器20E_0068h
3: 配置IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03寄存器20E_02F4h
4: 配置GPIO1_DR寄存器0209_C000h
5: 配置GPIO1_GDIR寄存器0209_C004h
6: LED闪烁
*/

_start :
    /* 配置 CCM_CCGR0-6 时钟寄存器 */
    LDR R0, =0x020C4068   @ CCM_CCGR0 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR0

    LDR R0, =0x020C406C   @ CCM_CCGR1 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR1

    LDR R0, =0x020C4070   @ CCM_CCGR2 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR2

    LDR R0, =0x020C4074   @ CCM_CCGR3 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR3

    LDR R0, =0x020C4078   @ CCM_CCGR4 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR4

    LDR R0, =0x020C407C   @ CCM_CCGR5 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR5

    LDR R0, =0x020C4080   @ CCM_CCGR6 register address
    LDR R1, =0xFFFFFFFF   
    STR R1, [R0]          @ Write configuration to CCM_CCGR6

    /* 配置IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03寄存器 */
    /* 设置MUX_MODE为GPIO，0101 ALT5 — Select mux mode: ALT5 mux port: GPIO1_IO03 of instance: gpio1 */
    LDR R0, =0x020E0068   @ IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 address
    LDR R1, =0x5          @ MUX_MODE = ALT5 (
    STR R1, [R0]          @ Write to IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03

    /* 配置IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03寄存器 */
    /* 电气属性寄存器定义参考IMX6ULL参考手册1793页 */
    LDR R0, =0x020E02F4   @ IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 address
    LDR R1, =0x10B0       @ 设置驱动能力，上拉使能等属性
    STR R1, [R0]          @ Write to IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03

    /* 配置GPIO1_GDIR寄存器 */
    LDR R0, =0x0209C004   @ GPIO1_GDIR register address
    LDR R1, =0x8          @ 设置GPIO1_IO03为输出
    STR R1, [R0]          @ Write to GPIO1_GDIR

loop:
    /* 设置GPIO1_DR寄存器为低电平，点亮LED */
    LDR R0, =0x0209C000   @ GPIO1_DR register address
    LDR R1, =0x0          @ 设置GPIO1_IO03输出低电平
    STR R1, [R0]          @ Write to GPIO1_DR

    /* 延时 */
    LDR R2, =0xFFFFF     @ 使用LDR指令加载延时计数器值
1:  SUBS R2, R2, #1       @ 递减计数器
    BNE 1b                @ 如果计数器未到0，继续循环

    /* 设置GPIO1_DR寄存器为高电平，熄灭LED */
    LDR R1, =0x8          @ 设置GPIO1_IO03输出高电平
    STR R1, [R0]          @ Write to GPIO1_DR

    /* 延时 */
    LDR R2, =0xFFFFF     @ 使用LDR指令加载延时计数器值
2:  SUBS R2, R2, #1       @ 递减计数器
    BNE 2b                @ 如果计数器未到0，继续循环

    B loop                @ 无限循环，保持闪烁
