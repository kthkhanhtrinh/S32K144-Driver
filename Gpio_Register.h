#ifndef S32K144_H
#define S32K144_H



typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef enum Led_Color{
	BLUE,
	RED, 
	GREEN
} led_color;
extern volatile led_color tmp_color;

typedef enum program{
	NON, 
	PG1,
	PG2
} button_num;

extern volatile button_num tmp_program;


#define PORT_PCR_COUNT	1000


typedef struct{
	volatile uint32 PCR[PORT_PCR_COUNT];
} PORT_Type;

#define PORTD_BASE_ADDRS 0x4004C000
#define PORTD						((PORT_Type *)PORTD_BASE_ADDRS)

#define PORTC_BASE_ADDRS	0x4004B000
#define PORTC						((PORT_Type *)PORTC_BASE_ADDRS)


/* PCC */
typedef struct {
	char dummy[292];
	volatile uint32 PCC_PORTA;
	volatile uint32 PCC_PORTB;
	volatile uint32 PCC_PORTC;
	volatile uint32 PCC_PORTD;
	volatile uint32 PCC_PORTE;	
	
} PCC;

#define PCC_BASE_ADDRS	0x40065000
#define PCC_Reg					((PCC *)PCC_BASE_ADDRS)

/* GPIO */
typedef struct{
	volatile uint32 GPIO_PDOR;
	volatile uint32 GPIO_PSOR;
	volatile uint32 GPIO_PCOR;
	volatile uint32 GPIO_PTOR;
	volatile uint32 GPIO_PDIR;
	volatile uint32 GPIO_PDDR;
	volatile uint32 GPIO_PIDR;
} GPIO_Type;

#define GPIOC_BASE_ADDRS 0x400FF080
#define GPIOC_Reg 				((GPIO_Type *)GPIOC_BASE_ADDRS)

#define GPIOD_BASE_ADDRS 0x400FF0C0
#define GPIOD_Reg 				((GPIO_Type *)GPIOD_BASE_ADDRS)

/* NVIC */

#define ISER_COUNT 8
#define ICER_COUNT 8
#define ISPR_COUNT 8
#define ICPR_COUNT 8
#define IABR_COUNT 8
#define IPR_COUNT  60

typedef struct{
	volatile uint32 NVIC_ISER[ISER_COUNT];
} NVIC;

#define NVIC_BASE_ADDRS 0xE000E100
#define NVIC_Reg				((NVIC*)NVIC_BASE_ADDRS)

/* SYSTEM TICK TIMER */
typedef struct
{
	volatile uint32 STK_CSR;
	volatile uint32 STK_RVR;
	volatile uint32 STK_CVR;
	volatile uint32 STK_CALIB;	
} Systick_Timer;
#define SYSTICK_BASE_ADDRS	0xE000E010
#define STK_Reg							((Systick_Timer *)SYSTICK_BASE_ADDRS)


#endif /* S32K144_H */
