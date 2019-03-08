
include SectionStack.inc

x_RegexParser@_addNode equ ?_addNode@RegexParser@x@@AEAAXXZ
x_RegexParser@_parseComment equ ?_parseComment@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseDecimal equ ?_parseDecimal@RegexParser@x@@AEAAPEBDPEBDAEAH@Z
x_RegexParser@_cloneLastSection equ ?_cloneLastSection@RegexParser@x@@AEAAPEAUNode@N
x_RegexParser@_processRepetitionsMax equ ?_processRepetitionsMax@RegexParser@x@@AEAAXH@Z
x_RegexParser@_processRepetitionsMin equ ?_processRepetitionsMin@RegexParser@x@@AEAAXH@Z
x_RegexParser@_processRepetitions equ ?_processRepetitions@RegexParser@x@@AEAAXHH@Z
x_RegexParser@_processRepetitionsExact equ ?_processRepetitionsExact@RegexParser@x@@AEAAXH@Z
x_RegexParser@_parseRepetitions equ ?_parseRepetitions@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseExact equ ?_parseExact@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_processSymbolNumber equ ?_processSymbolNumber@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_processOneOrMore equ ?_processOneOrMore@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_processZeroOrMore equ ?_processZeroOrMore@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_processZeroOrOne equ ?_processZeroOrOne@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseNegativeSet equ ?_parseNegativeSet@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parsePositiveSet equ ?_parsePositiveSet@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseAlternative equ ?_parseAlternative@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseSet equ ?_parseSet@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parseSection equ ?_parseSection@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_parse equ ?_parse@RegexParser@x@@AEAAPEBDPEBD@Z
x_RegexParser@_connectLast@chs equ ?_connectLast@RegexParser@x@@AEAAXPEBD@Z
x_RegexParser@_connectLast@ch equ ?_connectLast@RegexParser@x@@AEAAXD@Z
x_RegexParser@_connectLast@map equ ?_connectLast@RegexParser@x@@AEAAXPEB_N@Z
x_RegexParser@_parseEscape equ ?_parseEscape@RegexParser@x@@AEAAPEBDPEBD@Z

x_RegexParser@_addNode proto
x_RegexParser@_parseComment proto
x_RegexParser@_parseDecimal proto
x_RegexParser@_cloneLastSection proto
x_RegexParser@_processRepetitionsMax proto
x_RegexParser@_processRepetitionsMin proto
x_RegexParser@_processRepetitions proto
x_RegexParser@_processRepetitionsExact proto
x_RegexParser@_parseRepetitions proto
x_RegexParser@_parseExact proto
x_RegexParser@_processSymbolNumber proto
x_RegexParser@_processOneOrMore proto
x_RegexParser@_processZeroOrMore proto
x_RegexParser@_processZeroOrOne proto
x_RegexParser@_parseNegativeSet proto
x_RegexParser@_parsePositiveSet proto
x_RegexParser@_parseAlternative proto
x_RegexParser@_parseSet proto
x_RegexParser@_parseSection proto
x_RegexParser@_parse proto
x_RegexParser@_connectLast@chs proto
x_RegexParser@_connectLast@ch proto
x_RegexParser@_connectLast@map proto
x_RegexParser@_parseEscape proto

RegexParser struct
	_setCompl		qword	?
	_setNegation	byte	?
	_quantifiers	byte	?
	_nfa			qword	?
	_sections		SectionStack<?>
	_lastNode		qword	?
RegexParser ends
