	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenControl
	.global redControl
	.extern P1OUT

;;  green controls
greenControl:
	cmp #0, r12
	jz greenOff
	bis #64, &P1OUT		;or
	pop r0
greenOff:
	and #~64, &P1OUT
	pop r0

	;; red controls
redControl:
	cmp #0,r12
	jz redOff
	bis #1, &P1OUT
	pop r0
redOff:
	and #~1, &P1OUT
	pop r0
