/**
 * @file
 *
 * @brief
 *
 * @date 04.07.2012
 * @author Anton Bondarev
 */

#ifndef MIPSREGS_H_
#define MIPSREGS_H_


/*
 * Coprocessor 0 registers.
 */
#define CP0_CONTEXT   4    /* The Pointer to an entry in (PTE) array */
#define CP0_BADVADDR  8    /* Virtual address of last exception */
#define CP0_COUNT     9    /* Processor cycle count */
#define CP0_COMPARE  11    /* Comparator value to generate timer IRQ7 */
#define CP0_STATUS   12    /* select 0 Processor status and control */
#define CP0_INTCTL   12    /* select 1 Interrupt control */
#define CP0_CAUSE    13    /* Cause of last exception */
#define CP0_EPC      14    /* Program counter at last exception */
#define CP0_PRID     15    /* Processor identification (read only) */
#define CP0_EBASE    15    /* select 1 exception base */
#define CP0_CONFIG   16    /* select 0 Configuration */
#define CP0_CONFIG1  16    /* select 1 configuration */
#define CP0_CONFIG2  16    /* select 2 Configuration */
#define CP0_CONFIG3  16    /* select 3 configuration */
#define CP0_CONFIG4  16    /* select 4 configuration */
#define CP0_CONFIG5  16    /* select 5 Configuration */
#define CP0_CONFIG6  16    /* select 6 configuration */
#define CP0_CONFIG7  16    /* select 7 configuration */
#define CP0_DEBUG    23    /* Debug control and status */
#define CP0_DEPC     24    /* Program counter at last debug exception */
#define CP0_ERROREPC 30    /* Program counter at last error */
#define CP0_DESAVE   31    /* Debug handler scratchpad register */


#define MIPS_IRQN_TIMER     7 /* timer interrupt number */

#define ST0_IRQ_MASK_OFFSET 0x8 /* interrupt mask offset in status and cause registers */
#define ST0_SOFTIRQ_NUM     0x2

#define ST0_IM     0x0000ff00
#define ST0_IP0   (1 << (ST0_IRQ_MASK_OFFSET + 0))    /* soft interrupt 0 */
#define ST0_IP1   (1 << (ST0_IRQ_MASK_OFFSET + 1))    /* soft interrupt 1 */
#define ST0_IP2   (1 << (ST0_IRQ_MASK_OFFSET + 2))    /* UART1 interrupt flag */
#define ST0_IP3   (1 << (ST0_IRQ_MASK_OFFSET + 3))    /* UART2 interrupt flag */
#define ST0_IP6   (1 << (ST0_IRQ_MASK_OFFSET + 6))    /* RTC interrupt flag */
#define ST0_IP7   (0x1 << (ST0_IRQ_MASK_OFFSET + MIPS_IRQN_TIMER))  /* timer interrupt flag */


#define ST0_IE       0x00000001                     /* interrupts enable mask */
#define ST0_EXL      0x00000002                     /* exception level mask */
#define ST0_ERL      0x00000004                     /* error level mask */
#define ST0_BEV      1 << 22                        /* Boot exception vectors */

#define CAUSE_IV     1 << 23   /* vectored interrupt table */
#define CAUSE_PCI    1 << 26   /* performance counter interrupt */
#define CAUSE_DC     1 << 27   /* stop counter */
#define CAUSE_TI     1 << 30   /* timer interrupt */
#define CAUSE_BD     1 << 31   /* branch delay */
#define CAUSE_IM     0x0000ff00 /* interrupts mask */

#define INTCTL_VS    0x000003E0

#define CONFIG3_VEXIC 1 << 6  /* Support for an external interrupt controller. */
#define CONFIG3_VINT  1 << 5  /* Vectored interrupts implemented. */

/* helpers for access to MIPS co-processor 0 registers */
#define __read_32bit_c0_register(source, sel)				\
({ int __res;								\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			"mfc0\t%0, " #source "\n\t  ehb"			\
			: "=r" (__res));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mfc0\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
})

#define __write_32bit_c0_register(register, sel, value)			\
do {									\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			"mtc0\t%z0, " #register "\n\t ehb"			\
			: : "Jr" ((unsigned int)(value)));		\
	else								\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mtc0\t%z0, " #register ", " #sel "\n\t"	\
			".set\tmips0"					\
			: : "Jr" ((unsigned int)(value)));		\
} while (0)


/* read/write mips status register */
#define mips_read_c0_status()	__read_32bit_c0_register($12, 0)
#define mips_write_c0_status(val)	__write_32bit_c0_register($12, 0, val)

/* read/write mips cause register */
#define mips_read_c0_cause()		__read_32bit_c0_register($13, 0)
#define mips_write_c0_cause(val)	__write_32bit_c0_register($13, 0, val)

/* read/write mips compare register */
#define mips_read_c0_compare()		__read_32bit_c0_register($11, 0)
#define mips_write_c0_compare(val)	__write_32bit_c0_register($11, 0, val)

/* read/write mips count register */
#define mips_read_c0_count()		__read_32bit_c0_register($9, 0)
#define mips_write_c0_count(val)	__write_32bit_c0_register($9, 0, val)

/* read/write mips interrupt control register */
#define mips_read_c0_intctl()		__read_32bit_c0_register($12, 1)
#define mips_write_c0_intctl(val)	__write_32bit_c0_register($12, 1, val)

/* read/write mips exception base register */
#define mips_read_c0_ebase()		__read_32bit_c0_register($15, 1)
#define mips_write_c0_ebase(val)	__write_32bit_c0_register($15, 1, val)

/* read/write mips config register */
#define mips_read_c0_congig()		__read_32bit_c0_register($16, 0)
#define mips_write_c0_config(val)	__write_32bit_c0_register($16, 0, val)

/* read/write mips config1 register */
#define mips_read_c0_congig1()		__read_32bit_c0_register($16, 1)
#define mips_write_c0_config1(val)	__write_32bit_c0_register($16, 1, val)

/* read/write mips config2 register */
#define mips_read_c0_congig2()		__read_32bit_c0_register($16, 2)
#define mips_write_c0_config2(val)	__write_32bit_c0_register($16, 2, val)

/* read/write mips config3 register */
#define mips_read_c0_congig3()		__read_32bit_c0_register($16, 3)
#define mips_write_c0_config3(val)	__write_32bit_c0_register($16, 3, val)

/* read/write mips config4 register */
#define mips_read_c0_congig4()		__read_32bit_c0_register($16, 4)
#define mips_write_c0_config4(val)	__write_32bit_c0_register($16, 4, val)

/* read/write mips config5 register */
#define mips_read_c0_congig5()		__read_32bit_c0_register($16, 5)
#define mips_write_c0_config5(val)	__write_32bit_c0_register($16, 5, val)

/* read/write mips config6 register */
#define mips_read_c0_congig6()		__read_32bit_c0_register($16, 6)
#define mips_write_c0_config6(val)	__write_32bit_c0_register($16, 6, val)

/* read/write mips config7 register */
#define mips_read_c0_congig7()		__read_32bit_c0_register($16, 7)
#define mips_write_c0_config7(val)	__write_32bit_c0_register($16, 7, val)

#endif /* MIPSREGS_H_ */
