#ifndef _X_RAND32_H_
#define _X_RAND32_H_

#include <chrono>

namespace x
{
	class rand32
	{
		static constexpr uint32_t A_ = 0xAFDC1239;
		static constexpr uint32_t B_ = 0x5667FC17;
		static constexpr uint32_t C_ = 193;
		//static constexpr unsigned C_ = 0x45F02881;
		
		template<class _Void = void>
		struct Engine {
			static rand32 engine_;
		};

		mutable uint32_t seed_;

	public:
		rand32() noexcept:
			seed_((uint32_t)std::chrono::system_clock::now().time_since_epoch().count())
		{
		}

		rand32(uint32_t seed) noexcept:
			seed_(seed)
		{
		}

		rand32(rand32 const&) = delete;
		rand32(rand32&&) = default;

		__inline void seed(uint32_t value) noexcept {
			seed_ = value;
		}

		__inline void seed() {
			seed_ = (uint32_t)std::chrono::system_clock::now().time_since_epoch().count();
		}

		//GOOD
		/*mutable unsigned a = 0xAFDC1239;
		mutable unsigned b = 0x5667FC17;
		mutable unsigned c = 0x45F02880;*/

		uint32_t __declspec(noinline) __thiscall operator()() const {
			#if _MSC_VER && defined _M_X86
			_asm {
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
			}
			#else
			return seed_ = (seed_ ^ A_) * B_;
			#endif
		}

		uint32_t __declspec(noinline) __thiscall operator()(uint32_t n) const {
			#if _MSC_VER && defined _M_X86
			_asm {
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				xor edx, edx
				div n
				mov eax, edx
			}
			#else
			return (seed_ = (seed_ ^ A_) * B_) % n;
			#endif
		}

		uint32_t __declspec(noinline) __thiscall operator()(uint32_t min, uint32_t max) const {
			#if _MSC_VER && defined _M_X86
			_asm {
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				mov ebx, max
				sub ebx, min
				add ebx, 1
				xor edx, edx
				div ebx
				mov eax, edx
				add eax, min
			}
			#else
			return (seed_ = (seed_ ^ A_) * B_) % (max - min + 1) + min;
			#endif
		}

		//uint32_t __declspec(noinline) __thiscall next() const {
		//	//return seed_ = (seed_ ^ A_) * B_;
		//	_asm {
		//		mov eax, dword ptr[ecx]
		//		xor eax, A_
		//		mul B_
		//		mov dword ptr[ecx], eax
		//		add eax, edx
		//	}
		//}

		//uint32_t __declspec(noinline) __thiscall next(uint32_t n, prec) const {
		//	//return (seed_ = (seed_ ^ A_) * B_) % n;
		//	_asm {
		//		mov eax, dword ptr[ecx]
		//		xor eax, A_
		//		mul B_
		//		mov dword ptr[ecx], eax
		//		add eax, edx
		//		xor edx, edx
		//		div n
		//		mov eax, edx
		//	}
		//}

		uint32_t __declspec(noinline) __thiscall next(uint32_t min, uint32_t max, uint32_t prec) const {
			#if _MSC_VER && defined _M_X86
			_asm {
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				mov ebx, max
				sub ebx, min
				add ebx, 1
				xor edx, edx
				div ebx
				mov eax, edx
				xor edx, edx
				div prec
				mul prec
				add eax, min
			}
			#else
			return ((seed_ = (seed_ ^ A_) * B_) % (max - min + 1)) / prec * prec + min;
			#endif
		}

		uint64_t __declspec(noinline) __thiscall next(uint64_t min, uint64_t max, uint64_t prec) const {
			return ((seed_ = (seed_ ^ A_) * B_) % (max - min + 1)) / prec * prec + min;
		}

		#if _MSC_VER && defined _M_X86
		void __declspec(noinline) __thiscall generate(void* data, size_t bytes) const {
			_asm {
				mov esi, data
				mov edi, esi
				add edi, bytes
				_BEGIN_:
				cmp esi, edi
				jge _END_
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				mov [esi], eax
				add esi, 4
				jmp _BEGIN_
				_END_:
			}
		}

		void __declspec(noinline) __thiscall generate(uint32_t n, void* data, size_t bytes) const {
			_asm {
				mov esi, data
				mov edi, esi
				add edi, bytes
				_BEGIN_:
				cmp esi, edi
				jge _END_
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				xor edx, edx
				div n
				mov [esi], edx
				add esi, 4
				jmp _BEGIN_
				_END_:
			}
		}

		void __declspec(noinline) __thiscall generate(uint32_t min, uint32_t max, void* data, size_t bytes) const {
			_asm {
				mov esi, data
				mov edi, esi
				add edi, bytes
				_BEGIN_:
				cmp esi, edi
				jge _END_
				mov eax, dword ptr[ecx]
				xor eax, A_
				mul B_
				mov dword ptr[ecx], eax
				add eax, edx
				mov ebx, max
				sub ebx, min
				add ebx, 1
				xor edx, edx
				div ebx
				mov eax, edx
				add eax, min
				mov [esi], eax
				add esi, 4
				jmp _BEGIN_
				_END_:
			}
		}
		#endif

		/*uint32_t operator()(uint32_t min, uint32_t max) const noexcept {
			return (seed_ *= C_) % (max - min + 1) + min;
		}*/

		/*x::vector<unsigned> test(uint32_t max, size_t n = 100000) {
			x::vector<unsigned> result(max);
			result.enable().fill(0);
			repeat(max*n)
				++result[operator()() % max];
			std::cout<< "min: "<< result.min()<< "\nmax: "<< result.max()<< "\n";
			return result;
		}*/

		friend uint32_t random32();
		friend uint32_t random32(uint32_t n);
		friend uint32_t random32(uint32_t min, uint32_t max);
		friend uint32_t random32(uint32_t min, uint32_t max, uint32_t prec);
		friend uint64_t random64(uint64_t min, uint64_t max, uint64_t prec);
	};

	__forceinline uint32_t random32() {
		return rand32::Engine<>::engine_();
	}

	__forceinline uint32_t random32(uint32_t n) {
		return rand32::Engine<>::engine_(n);
	}

	__forceinline uint32_t random32(uint32_t min, uint32_t max) {
		return rand32::Engine<>::engine_(min, max);
	}

	__forceinline uint32_t random32(uint32_t min, uint32_t max, uint32_t prec) {
		return rand32::Engine<>::engine_.next(min, max, prec);
	}

	__forceinline uint64_t random64(uint64_t min, uint64_t max, uint64_t prec) {
		return rand32::Engine<>::engine_.next(min, max, prec);
	}

	template<class _Void>
	rand32 rand32::Engine<_Void>::engine_ = {};
}

#endif //_X_RAND32_H_