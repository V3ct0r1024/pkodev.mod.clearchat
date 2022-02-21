#pragma once
#include "structure.h"

namespace pkodev
{
	namespace hook
	{
		// void CCozeForm::OnSystemMsg(string strMsg)
		void __fastcall CCozeForm__OnSystemMsg(void *This, void *NotUsed, unsigned int a0, unsigned int a1, unsigned int a2,
			unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6);
	}
}