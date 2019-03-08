option casemap:none

include RegexParser.inc
include NFA.inc

$this equ [rsp+08h]
$sptr equ [rsp+10h]
$setptr equ [rsp+18h]

;///////////////////////////////////////////////////////////////////

extern ESCAPE_SET: qword

x_SectionStack@finish_inline macro thisreg:req, endreg:req, bufreg:=<r15>
	lea bufreg, [thisreg].RegexParser._sections.SectionStack._top
	mov [bufreg].Section._end, endreg
	mov [endreg].NFA_Node._accepting, 1
endm


StoreThis macro reg:=<rcx>
	mov [rsp + 08h], reg
endm

StoreSptr macro reg:=<rdx>
	mov [rsp + 10h], reg
endm

RestoreThis macro reg:=<rcx>
	mov reg, [rsp + 08h]
endm

RestoreSptr macro reg:=<rdx>
	mov reg, [rsp + 10h]
endm

StoreThisOff macro reg, off
	mov [rsp + 08h+off], reg
endm

StoreSptrOff macro reg, off
	mov [rsp + 10h+off], reg
endm

RestoreThisOff macro reg, off
	mov reg, [rsp + 08h+off]
endm

RestoreSptrOff macro reg, off
	mov reg, [rsp + 10h+off]
endm


GetEscapeSet macro destreg:req, symbol:req
	lea destreg, ESCAPE_SET
	mov destreg, [destreg + symbol*8]
endm

GuardReturnValue macro
	cmp rax, 0
	je FAIL
endm

CallParseFunction macro func
	call func
	GuardReturnValue
	RestoreThisOff rcx, 20h
	RestoreSptrOff rdx, 20h
endm

JmpAlign8 macro dest
	jmp near ptr dest
	nop
	nop
	nop
endm

.data

.code

x_RegexParser@_parse proc
	xor rax, rax
	StoreThis
	StoreSptr
	sub rsp, 20h
LOOP_BEGIN:
	mov al, byte ptr[rdx]
	add rdx, 1
	lea rbx, CASES
	lea rbx, [rbx+rax*8]
	jmp rbx
CASES:
	JmpAlign8 FINISH	; \0
	JmpAlign8 FAIL	; 0x01
	JmpAlign8 FAIL	; 0x02
	JmpAlign8 FAIL	; 0x03
	JmpAlign8 FAIL	; 0x04
	JmpAlign8 FAIL	; 0x05
	JmpAlign8 FAIL	; 0x06
	JmpAlign8 FAIL	; 0x07
	JmpAlign8 FAIL	; 0x08
	JmpAlign8 LOOP_BEGIN	; \t
	JmpAlign8 LOOP_BEGIN	; \n
	JmpAlign8 LOOP_BEGIN	; \v
	JmpAlign8 LOOP_BEGIN	; \f
	JmpAlign8 LOOP_BEGIN	; \r
	JmpAlign8 FAIL	; 0x0E
	JmpAlign8 FAIL	; 0x0F
	JmpAlign8 FAIL	; 0x10
	JmpAlign8 FAIL	; 0x11
	JmpAlign8 FAIL	; 0x12
	JmpAlign8 FAIL	; 0x13
	JmpAlign8 FAIL	; 0x14
	JmpAlign8 FAIL	; 0x15
	JmpAlign8 FAIL	; 0x16
	JmpAlign8 FAIL	; 0x17
	JmpAlign8 FAIL	; 0x18
	JmpAlign8 FAIL	; 0x19
	JmpAlign8 FAIL	; 0x1A
	JmpAlign8 FAIL	; 0x1B
	JmpAlign8 FAIL	; 0x1C
	JmpAlign8 FAIL	; 0x1D
	JmpAlign8 FAIL	; 0x1E
	JmpAlign8 FAIL	; 0x1F
	JmpAlign8 APPLY	; ' '
	JmpAlign8 APPLY	; !
	JmpAlign8 APPLY	; "
	JmpAlign8 PROCESS_SYMBOL_NUMBER	; #
	JmpAlign8 FAIL	; $
	JmpAlign8 PARSE_COMMENT ; %
	JmpAlign8 APPLY	; &
	JmpAlign8 APPLY	; '
	JmpAlign8 PARSE_SECTION ; (
	JmpAlign8 FAIL
	JmpAlign8 PROCESS_ZERO_OR_MORE	; *
	JmpAlign8 PROCESS_ONE_OR_MORE		;+
	JmpAlign8 APPLY	; ,
	JmpAlign8 APPLY	; -
	JmpAlign8 APPLY_DOT	; .
	JmpAlign8 APPLY	; /
	JmpAlign8 APPLY	; 0
	JmpAlign8 APPLY	; 1
	JmpAlign8 APPLY	; 2
	JmpAlign8 APPLY	; 3
	JmpAlign8 APPLY	; 4
	JmpAlign8 APPLY	; 5
	JmpAlign8 APPLY	; 6
	JmpAlign8 APPLY	; 7
	JmpAlign8 APPLY	; 8
	JmpAlign8 APPLY	; 9
	JmpAlign8 APPLY	; :
	JmpAlign8 APPLY	; ;
	JmpAlign8 APPLY	; <
	JmpAlign8 APPLY	; =
	JmpAlign8 APPLY	; >
	JmpAlign8 PROCESS_ZERO_OR_ONE ; ?
	JmpAlign8 APPLY	; @
	JmpAlign8 APPLY	; A
	JmpAlign8 APPLY	; B
	JmpAlign8 APPLY	; C
	JmpAlign8 APPLY	; D
	JmpAlign8 APPLY	; E
	JmpAlign8 APPLY	; F
	JmpAlign8 APPLY	; G
	JmpAlign8 APPLY	; H
	JmpAlign8 APPLY	; I
	JmpAlign8 APPLY	; J
	JmpAlign8 APPLY	; K
	JmpAlign8 APPLY	; L
	JmpAlign8 APPLY	; M
	JmpAlign8 APPLY	; N
	JmpAlign8 APPLY	; O
	JmpAlign8 APPLY	; P
	JmpAlign8 APPLY	; Q
	JmpAlign8 APPLY	; R
	JmpAlign8 APPLY	; S
	JmpAlign8 APPLY	; T
	JmpAlign8 APPLY	; U
	JmpAlign8 APPLY	; V
	JmpAlign8 APPLY	; W
	JmpAlign8 APPLY	; X
	JmpAlign8 APPLY	; Y
	JmpAlign8 APPLY	; Z
	JmpAlign8 PARSE_SET		; [
	JmpAlign8 PARSE_ESCAPE	; \
	JmpAlign8 FAIL	; ]
	JmpAlign8 FAIL	; ^
	JmpAlign8 APPLY	; _
	JmpAlign8 PARSE_EXACT	; `
	JmpAlign8 APPLY	; a
	JmpAlign8 APPLY	; b
	JmpAlign8 APPLY	; c
	JmpAlign8 APPLY	; d
	JmpAlign8 APPLY	; e
	JmpAlign8 APPLY	; f
	JmpAlign8 APPLY	; g
	JmpAlign8 APPLY	; h
	JmpAlign8 APPLY	; i
	JmpAlign8 APPLY	; j
	JmpAlign8 APPLY	; k
	JmpAlign8 APPLY	; l
	JmpAlign8 APPLY	; m
	JmpAlign8 APPLY	; n
	JmpAlign8 APPLY	; o
	JmpAlign8 APPLY	; p
	JmpAlign8 APPLY	; q
	JmpAlign8 APPLY	; r
	JmpAlign8 APPLY	; s
	JmpAlign8 APPLY	; t
	JmpAlign8 APPLY	; u
	JmpAlign8 APPLY	; v
	JmpAlign8 APPLY	; w
	JmpAlign8 APPLY	; x
	JmpAlign8 APPLY	; y
	JmpAlign8 APPLY	; z
	JmpAlign8 PARSE_REPETITIONS	; {
	JmpAlign8 PARSE_ALTERNATIVE	; |
	JmpAlign8 FAIL
	JmpAlign8 APPLY	; ~
	JmpAlign8 FAIL	; 0x7F	
FINISH:
	mov rbx, [rcx].RegexParser._lastNode
	x_SectionStack@finish_inline rcx, rbx
	mov rax, rdx
	jmp RETURN
APPLY:	
	StoreSptrOff rdx, 20h
	call x_RegexParser@_addNode
	RestoreThisOff rcx, 20h
	RestoreSptrOff rdx, 20h
	mov dl, [rdx]
	call x_RegexParser@_connectLast@ch
	RestoreThisOff rcx, 20h
	RestoreSptrOff rdx, 20h
	jmp LOOP_BEGIN
APPLY_DOT:
	call x_RegexParser@_addNode
	RestoreThisOff rcx, 20h
	RestoreSptrOff rdx, 20h
	xor rax, rax
	mov al, [rdx]
	GetEscapeSet rdx, rax
	call x_RegexParser@_connectLast@chs
	RestoreThisOff rcx, 20h
	RestoreSptrOff rdx, 20h
	jmp LOOP_BEGIN
PROCESS_SYMBOL_NUMBER:
	CallParseFunction x_RegexParser@_processSymbolNumber
	jmp LOOP_BEGIN
PARSE_COMMENT:
	CallParseFunction x_RegexParser@_parseComment
	jmp LOOP_BEGIN
PARSE_SECTION:
	CallParseFunction x_RegexParser@_parseSection
	jmp LOOP_BEGIN
PROCESS_ONE_OR_MORE:
	CallParseFunction x_RegexParser@_processOneOrMore
	jmp LOOP_BEGIN
PROCESS_ZERO_OR_MORE:
	CallParseFunction x_RegexParser@_processZeroOrMore
	jmp LOOP_BEGIN
PROCESS_ZERO_OR_ONE:
	CallParseFunction x_RegexParser@_processZeroOrOne
	jmp LOOP_BEGIN
PARSE_SET:
	CallParseFunction x_RegexParser@_parseSet
	jmp LOOP_BEGIN
PARSE_ESCAPE:
	CallParseFunction x_RegexParser@_parseEscape
	jmp LOOP_BEGIN
PARSE_EXACT:
	CallParseFunction x_RegexParser@_parseExact
	jmp LOOP_BEGIN
PARSE_REPETITIONS:
	CallParseFunction x_RegexParser@_parseRepetitions
	jmp LOOP_BEGIN
PARSE_ALTERNATIVE:

FAIL:
	xor rax, rax
RETURN:
	add rsp, 20h
	ret
x_RegexParser@_parse endp

;///////////////////////////////////////////////////////////////////

x_RegexParser@_parseDecimal proc
	mov r9, rdx
	xor rdx, rdx
	;first symbol
	mov bl, byte ptr[r9]
	;fail if not digit
	cmp bl, 30h
	jl FAIL
	cmp bl, 39h
	jg FAIL
	;init result
	xor rax, rax
	and bl, 0Fh
	mov al, bl
	;store 10 in r10 for mul
	mov r10, 10
LOOP_BEGIN:
	;next symbol
	add r9, 1
	mov bl, byte ptr[r9]
	;end if not digit
	cmp bl, 30h
	jl SUCCESS
	cmp bl, 39h
	jg SUCCESS
	;process symbol
	and bl, 0Fh
	mul r10
	add eax, ebx
	jmp LOOP_BEGIN
SUCCESS:
	mov dword ptr[r8], eax
	mov rax, r9
	ret
FAIL:
	xor rax, rax
	ret
x_RegexParser@_parseDecimal endp

;///////////////////////////////////////////////////////////////////

x_RegexParser@_parseComment proc
	;first symbol
	mov al, byte ptr[rdx]
	;end if null or lf
	cmp al, 00h
	je RETURN
	cmp al, 0Ah
	je RETURN
LOOP_BEGIN:
	;next symbol
	add rdx, 1
	mov al, byte ptr[rdx]
	;loop if not null nor lf
	cmp al, 00h
	je RETURN
	cmp al, 0Ah
	jne LOOP_BEGIN
RETURN:
	;return current str ptr
	mov rax, rdx
	ret
x_RegexParser@_parseComment endp

;///////////////////////////////////////////////////////////////////

x_RegexParser@_parseEscape proc
	lea rsi, ESCAPE_SET			;get address of ESCAPE_SET table
	xor rbx, rbx				;clear rbx
	mov bl, [rdx]				;get current symbol
	mov rax, [rsi+rbx*8]		;get pointer to escape set for symbol
	cmp rax, 0					;fail if nullptr
	je FAIL_RAX_0
	mov [rsp+08h], rcx			;save this ptr on stack
	mov [rsp+10h], rdx			;save str ptr on stack
	mov [rsp+18h], rax			;save escape set ptr on stack
	sub rsp, 20h				;reserve shadow space
	call x_RegexParser@_addNode
	mov rcx, [rsp+28h]			;restore this ptr
	mov rdx, [rsp+38h]			;restore escape set ptr
	call x_RegexParser@_connectLast@chs
	add rsp, 20h				;free shadow space
	mov rax, [rsp+10h]			;retrun str ptr + 1
	add rax, 1
	ret
FAIL_RAX_0:
	ret
x_RegexParser@_parseEscape endp

end