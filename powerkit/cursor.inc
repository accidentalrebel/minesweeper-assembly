moveCursorHorizontally:
;; Moves the cursor to the right
;;
;; Expects: CL = Times to move. Positive to go right. Negative to go left, BH = Page number
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx
	
	xor	ch, ch
	push	cx

;; Get the current cursor position. Row is placed in DH		
	mov	ah, 03h		; Service: Get cursor position 
	int	10h
	pop	cx

;; Set the cursor position
	mov	ah, 02h		; Service: Set cursor position
	add	dl, cl

	int	10h

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret

moveCursorVertically:
;; Moves the cursor vertically
;;
;; Expects: CL = Times to move. Positive to go down. Negative to go up, BH = Page number
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx
	
	xor	ch, ch
	push	cx

;; Get the current cursor position. Row is placed in DH	
	mov	ah, 03h		; Service: Get cursor position
	int	10h

	pop	cx
	
;; Increment DH depending on the number of times to do it	
	mov	ah, 02h		; Service: Set cursor position
	mov	bh, 0		; Set page number
	add	dh, cl
	int	10h

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret
	
placeCursorAt:
;; Places the cursor at position
;;
;; Expects: DH = ROW, DL = COL, BL = Page number
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx

	mov	ah, 02h
	int	10h

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret

testCursorMovementFunctions:
;; Series of tests to test cursor movements
;;
;; Expects: None
;; Returns: None
	push	ax
	push	bx
	push	cx
	push	dx

	mov	bh, 0
	mov	dh, 2
	mov	dl, 5
	call	placeCursorAt

	mov	cl, 1
	call	moveCursorVertically

	mov	ah, 0ah		; Service: Write character
	mov	al, 53h		; Set the character to display
	mov	cx, 1		; Set repeat count
	int	10h

	mov	cl, 1
	call	moveCursorHorizontally
	mov	cl, -1
	call	moveCursorVertically

	mov	ah, 0ah		; Service: Write character
	mov	al, 45h		; Set the character to display
	mov	cl, 1		; Set repeat count
	int	10h

	mov	cl, -2
	call	moveCursorHorizontally

	mov	ah, 0ah		; Service: Write character
	mov	al, 57h		; Set the character to display
	mov	cl, 1		; Set repeat count
	int	10h

	mov	cl, 1
	call	moveCursorHorizontally
	mov	cl, -1
	call	moveCursorVertically

	mov	ah, 0ah		; Service: Write character
	mov	al, 4eh		; Set the character to display
	mov	cl, 1		; Set repeat count
	int	10h


	pop	dx
	pop	cx
	pop	bx
	pop	ax
	
	ret

