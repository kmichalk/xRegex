option casemap:none

include SectionStack.inc

.code

x_SectionStack@end proc
	mov rax, [rcx].SectionStack._top
	mov [rax].Section._end, rdx
	mov rbx, [rax].Section._parent
	mov [rcx].SectionStack._top, rbx
	ret
x_SectionStack@end endp

end