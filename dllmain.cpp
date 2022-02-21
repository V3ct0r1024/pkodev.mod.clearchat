#include <Windows.h>
#include <detours.h>

#include <cstring>

#include "loader.h"
#include "address.h"
#include "pointer.h"
#include "hook.h"
#include "structure.h"

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CCozeForm__OnSystemMsg, pkodev::hook::CCozeForm__OnSystemMsg);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CCozeForm__OnSystemMsg, pkodev::hook::CCozeForm__OnSystemMsg);
    DetourTransactionCommit();
}

// void CCozeForm::OnSystemMsg(string strMsg)
void __fastcall pkodev::hook::CCozeForm__OnSystemMsg(void* This, void* NotUsed, unsigned int a0, unsigned int a1, unsigned int a2,
    unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6)
{
    // Pointer to the string
    const char* str = nullptr;

    // Build std::string object from stack
    char std__string[0x1C]{0x00};
    *reinterpret_cast<unsigned int*>(std__string + 0x00) = a0;
    *reinterpret_cast<unsigned int*>(std__string + 0x04) = a1;
    *reinterpret_cast<unsigned int*>(std__string + 0x08) = a2;
    *reinterpret_cast<unsigned int*>(std__string + 0x0C) = a3;
    *reinterpret_cast<unsigned int*>(std__string + 0x10) = a4;
    *reinterpret_cast<unsigned int*>(std__string + 0x14) = a5;
    *reinterpret_cast<unsigned int*>(std__string + 0x18) = a6;

    // Get string length
    const unsigned int len = *reinterpret_cast<unsigned int*>(std__string + 0x14);

    // Check string length
    if (len < 15)
    {
        // Get the string from stack
        str = reinterpret_cast<const char*>(std__string + 0x04);
    }
    else
    {
        // Get the string from heap
        str = *reinterpret_cast<const char**>(std__string + 0x04);
    }
    
    // Check message in the system chat
    if (std::strcmp(str, "{system:clearchat}") == 0)
    {
        // Remove messages from GUI list
        pkodev::pointer::CListItems__Clear(
            reinterpret_cast<void *>(
                *reinterpret_cast<unsigned int*>(
                    *reinterpret_cast<unsigned int*>(
                        reinterpret_cast<unsigned int>(This) + 0x18
                    ) + 0xA4
                )
            )
        );

        // Remove messages from message list
        pkodev::pointer::CCharMsg__ClearAllMsg();

        // Do not show the system message
        return;
    }

    // Call the original method void CCozeForm::OnSystemMsg(string strMsg)
    pkodev::pointer::CCozeForm__OnSystemMsg(This, a0, a1, a2, a3, a4, a5, a6);
}