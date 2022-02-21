#pragma once
#include "address.h"
#include "structure.h"

namespace pkodev
{
	namespace pointer
	{
		// void CCozeForm::OnSystemMsg(string strMsg)
		typedef void(__thiscall* CCozeForm__OnSystemMsg__Ptr)(void*, unsigned int, unsigned int, unsigned int,
			unsigned int, unsigned int, unsigned int, unsigned int);
		CCozeForm__OnSystemMsg__Ptr CCozeForm__OnSystemMsg = (CCozeForm__OnSystemMsg__Ptr)(void*)(pkodev::address::MOD_EXE_VERSION::CCozeForm__OnSystemMsg);
	
		// void CListItems::Clear()
		typedef void(__thiscall* CListItems__Clear__Ptr)(void*);
		CListItems__Clear__Ptr CListItems__Clear = (CListItems__Clear__Ptr)(void*)(pkodev::address::MOD_EXE_VERSION::CListItems__Clear);
		
		// void CCharMsg::ClearAllMsg()
		typedef void(__cdecl* CCharMsg__ClearAllMsg__Ptr)();
		CCharMsg__ClearAllMsg__Ptr CCharMsg__ClearAllMsg = (CCharMsg__ClearAllMsg__Ptr)(void*)(pkodev::address::MOD_EXE_VERSION::CCharMsg__ClearAllMsg);
	}
}