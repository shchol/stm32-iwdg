/*
 * pin.h
 *
 *  Created on: 15 èþë. 2022 ã.
 *      Author: user
 */

#ifndef SRC_INC_PIN_H_
#define SRC_INC_PIN_H_



/* Port identifiers */
#define PORT_NUM	15
#define PORT_1		(1 << 3)
#define PORT_2		(2 << 3)
#define PORT_3		(3 << 3)
#define PORT_4		(4 << 3)
#define PORT_5		(5 << 3)
#define PORT_6		(6 << 3)
#define PORT_7		(7 << 3)
#define PORT_8		(8 << 3)
#define PORT_9		(9 << 3)
#define PORT_A		(10 << 3)
#define PORT_B		(11 << 3)
#define PORT_C		(12 << 3)
#define PORT_D		(13 << 3)
#define PORT_E		(14 << 3)
#define PORT_F		(15 << 3)
#define	PORT_MASK	(15 << 3)
#define PORT_SHIFT	3

/* Pin identifiers */
#define PIN_0		(0 << 0)
#define PIN_1		(1 << 0)
#define PIN_2		(2 << 0)
#define PIN_3		(3 << 0)
#define PIN_4		(4 << 0)
#define PIN_5		(5 << 0)
#define PIN_6		(6 << 0)
#define PIN_7		(7 << 0)
#define PIN_MASK	(7 << 0)

/* Pin direction (input/output) */
#define DIR_IN		0
#define DIR_OUT		1

/* Pin/port macros */
#define P(port,pin)	(cat2(PORT_,port) | cat2(PIN_,pin))
#define p(port)		(cat2(PORT_,port))

#define PIN_INVALID	0x7f

#ifndef __ASSEMBLY__

/* External interfaces */
//extern void pin_conf(unsigned char pin, char dir);
//extern void port_conf(unsigned char port, unsigned char dir);
//extern void pin_set(unsigned char pin, unsigned char val);
//extern unsigned char pin_get(unsigned char pin);
//extern unsigned char port_get(unsigned char port);
//extern void pin_pullup(unsigned char pin, unsigned char enable);
//extern void pin_unused_pollup_on(void);
//
//extern char pin_set_ex(unsigned char pin, unsigned char val);
//extern char pin_get_ex(unsigned char pin, unsigned char *sig_value);

#endif /* __ASSEMBLY__ */


#endif /* SRC_INC_PIN_H_ */
