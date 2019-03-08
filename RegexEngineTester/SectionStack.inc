
x_SectionStack@end equ ?end@SectionStack@x@@QEAAXPEAUNode@NFA@2@@Z
x_SectionStack@push@N equ ?push@SectionStack@x@@QEAAXPEAUNode@NFA@2@@Z
x_SectionStack@finish equ ?finish@SectionStack@x@@QEAAXPEAUNode@NFA@2@@Z

SectionStack struct
	_root		qword	?
	_top		qword	?
	_stored		qword	?
	_lastId		qword	?
SectionStack ends

Section struct
	_parent		qword	?
	_next		qword	?
	_sub		qword	?
	_begin		qword	?
	_end		qword	?
	_id			word	?
	_looped		byte	?
	_optional	byte	?
Section ends