==========================================================================
程序说明：
（1）程序摘要：彩灯传感器测试程序
（2）运行芯片：本工程在KL36芯片运行
（3）软件环境：AHL-GEC-IDE，兼容KDS3.2
（4）硬件环境：嵌入式系统实验套件（AHL-MCU-KL36）
（5）硬件连接：见"..\05_UserBoard\user.h"文件
（6）功能简述：① 蓝灯闪烁
          ② UART_Debug串口（波特率115200），输出彩灯提示信息
   
============================================================================
版权所有：SD-Arm(sumcu.suda.edu.cn)
版本更新：20190906-20200318 
特别声明：
         ① 本代码在所提供硬件系统测试通过，真诚奉献给社会，不足之处，欢迎指正。
         ② 若使用其他硬件系统，移植代码时，请仔细根据自己的硬件匹配。
=============================================================================   
原理概述：
彩灯的控制电路与 RGB 芯片集成在一个 5050 封装的元器件中，构成了一个完整的外控
像素点，每个像素点的三基色颜色可实现 256 级亮度显示。像素点内部包含了智能数字
接口数据锁存信号整形放大驱动电路、高精度的内部振荡器和可编程定电流控制部分，
有效保证了像素点颜色的高度一致。数据协议采用单线归零码的通信方式，通过发送具有
特定占空比的高电平和低电平来控制彩灯的亮暗。


【20200812】
不同芯片User
02_CPU cpu.h 变动（1）~（2），根据MCU型号变动，且BIOS工程与User工程同
03_MCU mcu.h 变动（1）、（3）,根据MCU型号变动，且BIOS工程与User工程同
             在该文件中修改MCU型号及BIOS版本号
       .ld文件：BIOS与User不同，根据MCU型号变动
       .s文件：BIOS与User不同，改动类似BSS处
04_GEC 各芯片的gec.h仅改动一处，注意BIOS工程与User工程不同
05_UserBoard User.h根据MCU型号变动
06、07文件夹：各芯片User程序，这两个文件夹要相同

【20200326】WYH改，..\startup\.S文件，误中断，回原处
【20200430】V2.8 WYH改，..\startup\.c，不对看门狗操作，留给main操作














