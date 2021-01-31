

.cpu cortex-m3
.syntax unified
.thumb
.fpu softvfp



.extern msp
.extern main
.extern vma_data_start
.extern vma_data_end
.extern lma_data_start

.weak nmi_handler
.thumb_set nmi_handler,  default_handler

.weak hf_handler
.thumb_set hf_handler,  default_handler

.weak mmf_handler
.thumb_set mmf_handler,  default_handler

.weak bf_handler
.thumb_set bf_handler,  default_handler

.weak uf_handler
.thumb_set uf_handler,  default_handler

.weak svcall_handler
.thumb_set svcall_handler,  default_handler

.weak pendsv_handler
.thumb_set pendsv_handler,  default_handler

.weak systick_handler
.thumb_set systick_handler,  default_handler

.weak irq0_handler
.thumb_set irq0_handler,  default_handler

.weak irq1_handler
.thumb_set irq1_handler,  default_handler

.weak irq2_handler
.thumb_set irq2_handler,  default_handler





.section .vector_table,"a"
	.word msp
	.word reset_handler
	.word nmi_handler
	.word hf_handler
	.word mmf_handler
	.word bf_handler
	.word uf_handler
	.rept 4
	.word default_handler
	.endr
	.word svcall_handler
	.rept 2
	.word default_handler
	.endr
	.word pendsv_handler
	.word systick_handler
	.word irq0_handler
	.word irq1_handler
	.word irq2_handler




.section .text.reset_handler
	.type reset_handler,%function
	reset_handler:	ldr r0,=lma_data_start
					ldr r1,=vma_data_start
					ldr r2,=vma_data_end

					cmp r1,r2
					beq call_main

	copy_loop1:		ldr r3,[r0],4
					str r3,[r1],4
					cmp r1,r2
					blo copy_loop1
	call_main:	bl main

	loop: b loop






.section .text.default_handler
	.type default_handler,%function
	default_handler: b default_handler









.end


