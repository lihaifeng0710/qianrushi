#ifndef _TIMESTAMP_H
#define _TIMESTAMP_H

#include "common.h"
#include <time.h>

//=====================================================================
//函数名称：timeChange
//函数返回：无
//参数说明：ticks：时间戳
//       time：解析后的日期，例:19700101000000(1970-01-01 00:00:00)
//功能概要：时间戳转成字符表示日期。
//备注：KDS和KEIL的内部使用函数不一样
//=====================================================================
void timeChange(uint_64 ticks,uint_8 *time);

#endif
