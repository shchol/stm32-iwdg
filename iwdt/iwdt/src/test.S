
	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

.section .data
	.global myconst
myconst:
	.long 4000000

.section .text

	.global Set_KR
Set_KR:
	ldr r1, =0x40003000
	ldr r0, [r1]
	ldr r3, =#0xcccc
	orr.w r0, r3
	str r0, [r1]
	bx lr

	.global Get_SR
Get_SR:
.LOOP:
	ldr r1, =0x4000300c
	ldr r0, [r1]
	and r2, r0, #0x02
	cmp r2, #2
	beq .ENDLOOP
	b .LOOP
.ENDLOOP:
	bx lr



