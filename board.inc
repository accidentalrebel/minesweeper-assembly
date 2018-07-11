populateBoard:
;; Populates the board
;; Expects: None
;; Returns: None

	call	setupBombs
	ret

setupBombs:
;; Sets up the bombs
;; Expects: None
;; Returns: None
	
	;; Get the time
	mov	ah, 2ch
	int	21h

;; Do some computations to the returned time to have a more random seed.
	mov	ah, cl
	add	ah, 1		; Add 1 to ensure we never get zero seed
	mul	dh
	mov	al, ch
	add	al, 1		; Add 1 to ensure we never get zero seed
	mul	dh
	add	al, 1		; Add 1 to ensure we never get zero seed

	mov	cx, 10		; Set number of times to generate bombs
	
.loopGenerateBomb:
	push	cx		; Save the counter

;; Generate the row
	call	generateRandomNumber
	push	ax		; Save the generated random number. Will use later as a seed on the next generation.

	mov	bx, 0
	mov	dx, boardDimensions
	call	convertRandomNumberToRange

	mov	bx, ax		; Save the generated row. To be used later.
	pop	ax		; Restore the previous random number to use as seed for the next generation.
	
;; Generate the column. We use the row as the seed for this.

	add	ax, 1
	call	generateRandomNumber
	push	ax		; Save the generated random number. Will use later as a seed on the next loop.
	
	mov	cx, bx		; Move the generated row. To be used later.

	mov	bx, 0	
	mov	dx, boardDimensions
	call	convertRandomNumberToRange

;; Display the character
	mov	dh, cl
	mov	dl, al
	mov	al, 30h
	mov	bl, 34h
	call	putObjectAt

	pop	ax		; Restore the seed for the next round.
	pop	cx		; Restore the remaining bomb counter.

	dec	cx
	jnz	.loopGenerateBomb
	ret

getObjectAt:
;; Gets the character on the board
;; Expects: DH = row, DL = col, BH = Page number
;; Returns: AL = Character, BL = Char attribute	
	push	cx
	push	dx

	mov	cx, dx		; We use CX, for our row and col
   	call	getBoardStartingPositions
	add	dh, ch		; We add our local row to the global row
	add	dl, cl		; We add our local col to the global col
	call	placeCursorAt

	mov	ah, 08h		; Service: Read character and attribute at cursor position
	int	10h

	mov	bl, ah

	pop	dx
	pop	cx
	ret

putObjectAt:
;; Places the character on the board
;;
;; Expects: AL = Char to print, BL = Char attribute, DH = row, DL = col, BH = Page number
;; Returens: None
	push	ax
	push	bx
	push	cx
	push	dx

	mov	cx, dx		; We use CX, for our row and col
   	call	getBoardStartingPositions
	add	dh, ch		; We add our local row to the global row
	add	dl, cl		; We add our local col to the global col
	call	placeCursorAt

	xor	cx, cx
	mov	cl, 1		; Set repeat count
	mov	ah, 09h		; Service: Write character and attribute at cursor position
	int	10h

	pop	dx
	pop	cx
	pop	bx
	pop	ax

	ret

getBoardStartingPositions:
;; Returns the board's global positions
;;
;; Expects: None
;; Returns: DH = row, DL = col
	push	ax
	push	bx
	push	cx
	
	mov	ax, boardDimensions 
	mov	dl, 2		; We get half of the boardDimensions
	div	dl
	mov	bl, al
	
	mov	ax, windowHeight
	div	dl
	mov	dh, al		; Set the starting row
	sub	dh, bl 		; Subtract from row to get the strating row
	
	mov	ax, windowWidth
	div	dl		; We get half af the window width
	mov	bh, al
	mov	dl, bh		; Set starting col
	sub	dl, bl          ; Subtract from the col to get the starting col

	pop	cx
	pop	bx
	pop	ax
	
	ret

drawBoard:
;; Draws the board and it's borders
;;
;; Expects: None
;; Returns: None

;; Draw the back of the board with border
	call	getBoardStartingPositions
	sub	dh, 1 		; Subtract one more to account for the border position
	sub	dl, 1		; Subtract one more to account for the border position
	mov	cl, boardDimensions + 2 ; Set the width
	mov	ch, boardDimensions + 2 ; Set the height
	mov	al, 0f0h		; Set the char to display
	mov	bl, 35h			; Set the text attribute
	mov	bh, 0		; Set the page number
	call	drawBorder

;; Draw the actual board
	call	getBoardStartingPositions
	mov	cl, boardDimensions ; Set the width
	mov	ch, boardDimensions ; Set the height
	mov	al, 0fah	; Set the char to display
	mov	bl, 43h		; Set the text attribute
	mov	bh, 0		; Set the page number
	call	drawRect
	
	ret

testBoardPopulator:
	mov	dh, 0
	mov	dl, 0
	mov	bl, 0
	call	placeCursorAt

	mov	ah, 09h		; Service: Write character
	mov	al, 43h
	mov	cx, 1		; Set repeat count
	mov	bh, 0
	mov	bl, 43h
	int	10h
	
	mov	cx, 10
.randLoop:
	push	cx
	
	;; We get the system time
	mov	ah, 2ch
	int	21h

	add	dh, dl
	mov	al, dh

	add	al, 64		; Convert to ascii

	mov	ah, 09h		; Service: Write character
	;;mov	al, 43h		; TEST
	mov	cx, 1		; Set repeat count
	mov	bh, 0
	mov	bl, 43h
	int	10h

	mov	cl, 1
	call	moveCursorHorizontally

	pop	cx

	dec	cx
	jnz	.randLoop
	ret
