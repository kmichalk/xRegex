#ifndef _X_BITSTR_H_
#define _X_BITSTR_H_

#include "bytebitsmap.h"
#include "bitliteral.h"
#include <string>

namespace x 
{
	inline void __declspec(noinline) bitstr(char* _str, void const* _data, size_t _size) {
		#if _MSC_VER && defined _M_X86
		_asm {
			mov ecx, _str
			mov edx, _data
			mov esi, edx
			lea ebx, x::BITCHARS
			add edx, _size
			xor eax, eax
			LOOP_BEGIN :
			dec edx
				cmp edx, esi
				jb LOOP_END
				mov al, byte ptr[edx]
				mov edi, dword ptr[ebx + eax * 8]
				mov dword ptr[ecx], edi
				mov edi, dword ptr[ebx + eax * 8 + 4]
				mov dword ptr[ecx + 4], edi
				add ecx, 8
				jmp LOOP_BEGIN
				LOOP_END :
			mov	byte ptr[ecx], '\0'
		}
		#else
		//TODO: DEFAULT IMPLEMENTATION
		#endif
	}

	template<class _Type>
	__forceinline void bitstr(char* str, _Type const& value) {
		bitstr(str, &value, sizeof(_Type));
	}

	template<class _Type>
	__forceinline std::string bitstr(_Type const& value) {
		std::string str(bitsizeof(_Type), '\0');
		bitstr(const_cast<char*>(str.c_str()), &value, sizeof(_Type));
		return str;
	}

	__forceinline std::string bitstr(void* data, size_t size) {
		std::string str(size, '\0');
		bitstr(const_cast<char*>(str.c_str()), data, size);
		return str;
	}
}

#endif
