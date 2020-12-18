/* ################################################################### */
/*##
/*##     该文件为工具产生，不要修改 */
/*##                                   */
/*##                                   */
/*##     Processor : MKL25Z128VLK4     */
/*##                                   */
/*##     Compiler  : GNU C Compiler    */
/*##                                   */
/*##     Date/Time : 2012-08-23, 07:09, # CodeGen: 0 */
/*##                                   */
/*##     Abstract  :                   */
/*##                                   */
/*##     该文件为链接文件。该文件描述了文件如何被链接，以及内存范围，栈大小。详见compiler文档。 */
/*##     可以通过设置属性Generate linker file 为no关闭自动产生该文件 */
/*##                                    */
/*##
/*##                                   */
/*## ###################################################################*/


/* 程序开始点 */
/*进入startup*/
ENTRY(startup)

/* 用户模式栈的最高地址 */
_estack = 0x20003000;    /* end of m_data */
__SP_INIT = _estack;
__BOOT_STACK_ADDRESS = _estack;

/* 如果栈和堆未适应RAM，会产生链接错误 */
__heap_size = 0x00;;                   /* 需要的堆的大小  */
__stack_size = 0x0400;                 /* 栈大小 */


MEMORY {
  m_interrupts (RX) : ORIGIN = 0x00000000, LENGTH = 0x000000C0
 /* m_text      (RX) : ORIGIN = 0x00000410, LENGTH = 0x0001FBF0 */
  m_text      (RX) : ORIGIN = 0x00000800, LENGTH = 0x0001FBF0
  
 /* m_data_1FFFF000 (RW) : ORIGIN = 0x1FFFF000, LENGTH = 0x00001000*/
    m_data_1FFFF000 (RW) : ORIGIN = 0x1FFFF410, LENGTH = 0x00000BF0
    m_data      (RW) : ORIGIN = 0x20000410, LENGTH = 0x00002BF0
 /* m_data      (RW) : ORIGIN = 0x20000000, LENGTH = 0x00003000*/
  m_cfmprotrom  (RX) : ORIGIN = 0x00000400, LENGTH = 0x00000010
}

/* 对各个块的内容的定义 */
SECTIONS
{
  __VECTOR_RAM       = 0x1FFFF000;    /*中断向量表在RAM中的位置*/
  
  /*先加载中断向量，第一个为startup  */
  .interrupts :
  {
    __vector_table = .;
    . = ALIGN(4);
    KEEP(*(.vectortable)) /* Startup 代码 */
    . = ALIGN(4);
  } > m_interrupts

  .cfmprotect :
  {
    . = ALIGN(4);
        KEEP(*(.cfmconfig))     /* Flash 配置域(FCF) */
        . = ALIGN(4);
  } > m_cfmprotrom

  /* 程序代码和其他数据放入内部flash */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);

    _etext = .;        /* 定义一个全局的symbol在代码末端 */
    __START_DATA_ROM = _etext;  /* 初始化变量值 */
    
  } > m_text

   .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > m_text
    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
  } > m_text

 .ctors :
  {
    __CTOR_LIST__ = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text

  .dtors :
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);

        ___ROM_AT = .;
  } > m_text

  /* 已赋值变量复制到RAM，加载LMA */
  .data : AT(___ROM_AT)
  {
    . = ALIGN(4);
    _sdata = .;        /* 数据开始处产生一个全局的标记 */
    __START_DATA = _sdata; /* 初始化DATA段开始 */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    /* # 结束处标记 */

    _edata = .;        /* 定义全局标记量 */
    __END_DATA = _edata; /* 初始化DATA段结束 */
  } > m_data

  ___data_size = _edata - _sdata;
/* RAM中存放数据 */
  ___m_data_1FFFF000_ROMStart = ___ROM_AT + SIZEOF(.data);
  .m_data_1FFFF000 : AT(___m_data_1FFFF000_ROMStart)
  {
     . = ALIGN(4);
     ___m_data_1FFFF000_RAMStart = .;
     *(.m_data_1FFFF000) /* 用户定义区 */
     ___m_data_1FFFF000_RAMEnd = .;
     . = ALIGN(4);
  } > m_data_1FFFF000
  ___m_data_1FFFF000_ROMSize = ___m_data_1FFFF000_RAMEnd - ___m_data_1FFFF000_RAMStart;



  /* 未初始化数据部分 */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    __START_BSS = .;
    __bss_start__ = __START_BSS;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    __END_BSS = .;
    __bss_end__ = __END_BSS;
  } > m_data

  /*用户堆栈部分，用来检查是否有足够的RAM  */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    __heap_addr = .;
    . = . + __heap_size;
    . = . + __stack_size;
    . = ALIGN(4);
  } > m_data

  _romp_at = ___ROM_AT + SIZEOF(.data) +SIZEOF(.m_data_1FFFF000);
  .romp : AT(_romp_at)
  {
    __S_romp = _romp_at;
    LONG(___ROM_AT);
    LONG(_sdata);
    LONG(___data_size);
    LONG(___m_data_1FFFF000_ROMStart);
    LONG(___m_data_1FFFF000_RAMStart);
    LONG(___m_data_1FFFF000_ROMSize);
    LONG(0);
    LONG(0);
    LONG(0);
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}


