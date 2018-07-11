	bits	16
org	100h
	
section .text
	
start:
;; set as text mode
	mov 	ax, 0003h
	int 	10h

	;call	testGenerateRandomNumber
	call	drawBoard
	call	populateBoard

;; exit
	mov 	ah, 4ch
	mov 	al, 0
	int	21h

%include "powerkit/powerkit.inc"
%include "board.inc"

section .data

	windowWidth equ 80
	windowHeight equ 25
	boardDimensions equ 20
	shelloworld db "hello world!$"
	
section .bss
	


