#pragma once

// ?묒꽦??: ?μ꽭??//?꾪꽣留곸슜!  ?묒꽦???욎뿉 # @ !! ?뚯궗留덈떎! ?ㅻⅤ??! ?좊땲?곕뒗 @ ?곕뒗?? ?대뜑?뚯씪???묒꽦?섏뼱 ?덈뒗寃쎌슦 ?덉쓬
// - 寃쎄퀬瑜??쇰?濡?臾댁떆 ?쒖섟湲??뚮Ц?? 臾몄젣媛 ?쒕떎硫?怨좎퀜????
#pragma warning (disable : 4172)

#include "Core.h"

// ?곸냽 愿怨꾩뿉 ?덈뒗 ?대옒??媛꾩쓽
// ?숈쟻(?ㅽ뻾以묒뿉) ?뺣??섏쓣 鍮좊Ⅴ寃??섍린 ?꾪빐 ?ъ슜?섎뒗 ?대옒??
// RunTime-Type-Information.
class ENGINE_API RTTI
{
public:
	virtual const size_t& TypeIdInstance() const = 0;

	virtual bool Is(const size_t id) const
	{
		return false;
	}

	template<typename T>
	T* As()
	{
		if(Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}

	template<typename T>
	const T* As() const
	{
		if(Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}
};

#define RTTI_DECLARATIONS(Type, ParentType)												\
public:																					\
	using Super = ParentType;															\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
	static const size_t TypeIdClass()													\
	{																					\
		static int runTimeTypeId = 0;													\
		return reinterpret_cast<size_t>(&runTimeTypeId);								\
	}																					\
	virtual bool Is(const size_t id) const												\
	{																					\
		if (id == TypeIdClass())														\
		{																				\
			return true;																\
		}																				\
		else																			\
		{																				\
			return Super::Is(id);														\
		}																				\
	}
