drawRect:	
;; Draws a rectangle
;; 
;; Expects: AL = ASCII to print, DH = starting row, DL = starting col, CL = height, CH = width, BH = Page number, BL = Text Attribute
;; Returns: None
	
	call	placeCursorAt	; Place cursor at initial position

	mov	ah, ch
	xor	ch, ch
.loop:
;; Write the character
	push	ax
	push	cx

	xor	cx, cx

	mov	cl, ah		; Set repeat count
	mov	ah, 09h		; Service: Write character
	int	10h

	mov	cl, 1
	call	moveCursorVertically

	pop	cx
	pop	ax

	dec	cx
	jnz	.loop

	ret

drawBorder:
;; Draws a border
;; 
;; Expects: AL = ASCII to print, DH = starting row, DL = starting col, CL = height, CH = width, BH = Page number, BL = Text Attribute
;; Returns: None

	call	placeCursorAt	; Place cursor at initial position

	mov	ah, ch		; We save the width for future use
	mov	dx, cx
	xor	ch, ch
.loop:
	cmp	dh, ah
	jz	.writeCharacter ; If this is the first column, write character

	cmp	dl, ah
	jz	.writeCharacter ; If this is the first row, write character

	cmp	dh, 1		
	jz	.writeCharacter	; If this is the last column, write character

	cmp	dl, 1
	jz	.writeCharacter	; If this is the last row, write character
	
	jmp	.endWriteCharacter

.writeCharacter:
;; Write character
	push	ax
	
	mov	cx, 1		; Set repeat count
	mov	ah, 09h		; Service: Write character
	int	10h

	pop	ax
.endWriteCharacter:

;; Move right
	mov	cl, 1
	mov	bh, 0
	call	moveCursorHorizontally

	dec	dh		; Decrement col counter
	jnz	.loop		; if col counter is not yet zero, go back to start

;; Move one row
	mov	cl, 1
	call	moveCursorVertically

	dec	dl	        ; Decrement row counter
	jz	.endLoop	; if row counter is zero, go to end of loop 

;; Move back to the first column
	mov	cl, ah		
	neg	cl
	call	moveCursorHorizontally

	mov	dh, ah		; We reset the column counter
	
	jmp	.loop
.endLoop:	
	
	ret

%include "powerkit/cursor.inc"	
%include "powerkit/random.inc"
%include "powerkit/debug.inc"
