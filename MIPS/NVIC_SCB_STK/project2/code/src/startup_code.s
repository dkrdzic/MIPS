

.cpu cortex-m3
.fpu softvfp
.thumb
.syntax unified

.extern msp
.extern main
.extern vma_data_start
.extern vma_data_end
.extern lma_data_start


.weak pendSV_handler
.thumb_set pendSV_handler,default_handler


.weak systick_handler
.thumb_set systick_handler,default_handler

.weak irq0_handler
.thumb_set irq0_handler,default_handler

.weak irq1_handler
.thumb_set irq1_handler,default_handler

.weak irq2_handler
.thumb_set irq2_handler,default_handler

.section .vector_table, "a"
	.word msp
	.word reset_handler
	.rept 12
	.word default_handler
	.endr
	.word pendSV_handler
	.word systick_handler
	.word irq0_handler
	.word irq1_handler
	.word irq2_handler




.section .text.reset_handler
	.type reset_handler, %function
	reset_handler:	ldr r0,=lma_data_start
					ldr r1,=vma_data_start
					ldr r2,=vma_data_end

					cmp r1,r2
					beq call_main

	loop1:			ldr r3,[r0],4
					str r3,[r1],4
					cmp r1,r2
					blo loop1

	call_main: bl main

	loop2: b loop2



.section .text.default_handler
	.type default_handler,%function
		default_handler: b default_handler






.end










