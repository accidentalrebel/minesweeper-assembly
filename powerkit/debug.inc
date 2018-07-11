
debugLogChar:
;; Logs the character to the screen to standard output.
;;
;; Expects: dl = The character to display
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx

;; We handle the special characters
	cmp	dl, 27		; Escape charater
	jne	.check1
	mov	dl, 174		; Change it to a <<
	jmp	.endSpecialHandling
.check1:
	cmp	dl, 10		; Line feed character
	jne	.check2
	mov	dl, 175		; Change it to a >>
	jmp	.endSpecialHandling
.check2:
	cmp	dl, 7		; Line feed character
	jne	.check3
	mov	dl, 239		; Change it to the intersection character
	jmp	.endSpecialHandling
.check3:
	cmp	dl, 8		; Backspace character
	jne	.check4
	mov	dl, 243		; Change it to the less than equal to character
	jmp	.endSpecialHandling
.check4:
	cmp	dl, 9		; Tab character
	jne	.check5
	mov	dl, 242		; Change it to the greater than equal to character
	jmp	.endSpecialHandling
.check5:
	
	cmp	dl, 13		; Carriage return character
	jne	.endSpecialHandling
	mov	dl, 251		; Change to squareroot character
	
.endSpecialHandling:
	
	mov	ah, 02h
	int	21h

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	ret

debugAssertLog:
;; Checks if the content of AX is equal to DX.
;; Writes result to standard output. Y = Equal, N = Not Equal
;; This is a quick and dirty solution for debugging purposes only.
;;
;; Expects: AX = To compare, DX = To compare with
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx

	cmp	ax, dx
	jne	.notEqual
;; Print Y
	mov	dl, 59h

	call	debugLogChar
	jmp	.end
.notEqual:
;; Print N	
	mov	dl, 4Eh
	call	debugLogChar
.end:
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret

testDebug:
;; Tests the various debug functions.
	mov	dh, 0
	mov	dl, 0
	mov	bl, 0
	call	placeCursorAt

;; We test the special characters and replace them with a different character.	
	mov	dl, 176
	call	debugLogChar	; Print a bookend character for easy debugging
	
	mov	dl, 0		; Null character
	call	debugLogChar
	
	mov	dl, 255		; No break space character
	call	debugLogChar

	mov	dl, 10		; Line feed character
	call	debugLogChar
	
	mov	dl, 13		; Carriage return character
	call	debugLogChar

	mov	dl, 27		; Escape character
	call	debugLogChar

	mov	dl, 7		; Bell character
	call	debugLogChar

	mov	dl, 8		; Backspace character
	call	debugLogChar

	mov	dl, 9		; Tab character
	call	debugLogChar
	
	mov	dl, 176
	call	debugLogChar	; Print a bookend character for easy debugging

	mov	dh, 1
	mov	dl, 0
	mov	bl, 0
	call	placeCursorAt

;; We print all the ASCII characters from 0 to 255 onto the screen.	
	mov	cx, 255

.loop:
	mov	dl, cl
	mov	al, 255
	sub	al, dl
	mov	dl, al
	call	debugLogChar	
	
	dec	cx
	jnz	.loop

	ret
