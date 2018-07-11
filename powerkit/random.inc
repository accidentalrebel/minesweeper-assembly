generateRandomNumber:
;; Generates a random number from 0 to 65534.
;;
;; Uses the Xorshfit algorithm by George Marsaglia.
;;
;; The algorithm is shown below:
;; xs ^= xs << 7;
;; xs ^= xs >> 9;
;; xs ^= xs << 8;
;;
;; More info here: http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html
;;
;; Expects: AX = The seed
;; Returns: AX = The randomly generated number

	push	bx
	push	cx
	push	dx

	mov	dx, ax

;; XOR shift left by 7
	shl	ax, 7	
	xor	ax, dx

	mov	dx, ax
;; XOR shift right by 9
	shr	ax, 9
	xor	ax, dx

	mov	dx, ax
;; XOR shift left by 8
	shl	ax, 8
	xor	ax, dx

	pop	dx
	pop	cx
	pop	bx
	
	ret

convertRandomNumberToPercent:
;; Converts a given random number from 0 to 99.
;;
;; Expects: AX = The random number input
;; Returns: AX = A random number from 0 to 99.

	push	bx
	push	cx
	push	dx

	xor	dx, dx

	mov	cx, 100		; We multiply by 100 to accomadete the decimal point
	mul	cx

	mov	cx, 65535	; We set the highest possible value as the divisor
	div	cx		; We do the division

	pop	dx
	pop	cx
	pop	bx
	
	ret	

convertRandomNumberToRange:
;; Converts a random number into the given range.
;;
;; Expects: AX = The random number, BX = The smallest range, DX = The highest range
;; Returs: AX = The randomly generated number

	push	bx
	push	cx
	push	dx

	push	bx		; We will use this at the end
	
	call	convertRandomNumberToPercent

	sub	dx, bx		; We get the range size
	mul	dx		; We multiply
	
	xor	dx, dx
	mov	cx, 100		
	div	cx		; We then divide by 100

	pop	bx
	add	ax, bx		; We add the smallest range to the result

	pop	dx
	pop	cx
	pop	bx

	ret

testGenerateRandomNumber:
	push	ax
	push	bx
	push	cx
	push	dx

	mov	dh, 0
	mov	dl, 0
	mov	bl, 0
	call	placeCursorAt

;; Test generateRandomNumber
	mov	ax, 1
	call	generateRandomNumber
	mov	dx, 33153
	call	debugAssertLog

	mov	ax, 2
	call	generateRandomNumber
	mov	dx, 770
	call	debugAssertLog

	mov	ax, 3
	call	generateRandomNumber
	mov	dx, 33411
	call	debugAssertLog

	mov	ax, 50
	call	generateRandomNumber
	mov	dx, 10046
	call	debugAssertLog

	mov	ax, 100
	call	generateRandomNumber
	mov	dx, 20349
	call	debugAssertLog

	mov	ax, 255
	call	generateRandomNumber
	mov	dx, 16192
	call	debugAssertLog

	mov	ax, 256
	call	generateRandomNumber
	mov	dx, 49472
	call	debugAssertLog

	mov	ax, 33153
	call	generateRandomNumber
	mov	dx, 24609
	call	debugAssertLog

	mov	ax, 65535
	call	generateRandomNumber
	mov	dx, 32639
	call	debugAssertLog

;; Test generate random percent
	mov	ax, 1
	call	generateRandomNumber
	call	convertRandomNumberToPercent
	mov	dx, 50
	call	debugAssertLog

	mov	ax, 50
	call	generateRandomNumber
	call	convertRandomNumberToPercent
	mov	dx, 15
	call	debugAssertLog

	mov	ax, 74
	call	generateRandomNumber
	call	convertRandomNumberToPercent	
	mov	dx, 48
	call	debugAssertLog

;; Test generateRandomRange
	mov	ax, 1
	mov	bx, 0
	mov	dx, 10
	call	generateRandomNumber
	call	convertRandomNumberToRange
	mov	dx, ax
	add	dx, 30h
	call	debugLogChar
	
	mov	ax, 1
	mov	bx, 10
	mov	dx, 20
	call	generateRandomNumber
	call	convertRandomNumberToRange	
	mov	dx, 15
	call	debugAssertLog

	mov	ax, 50
	mov	bx, 10
	mov	dx, 20
	call	generateRandomNumber
	call	convertRandomNumberToRange	
	mov	dx, 11
	call	debugAssertLog

;; Tests linear random generation
	mov	dh, 1
	mov	dl, 0
	mov	bl, 0
	call	placeCursorAt
	
	mov	ax, 35654
	mov	cx, 20
	
.loopRandomization:
	call	generateRandomNumber
	call	convertRandomNumberToPercent

	mov	dl, al
	call	debugLogChar

	mov	dl, cl
	add	dl, 30h
	call	debugLogChar
	
	dec	cx
	jnz	.loopRandomization

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret
