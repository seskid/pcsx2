/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/wrapwin.h
// Purpose:     Wrapper around <windows.h>, to be included instead of it
// Author:      Vaclav Slavik
// Created:     2003/07/22
// Copyright:   (c) 2003 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_WRAPWIN_H_
#define _WX_WRAPWIN_H_

#include "wx/platform.h"

// strict type checking to detect conversion from HFOO to HBAR at compile-time
#ifndef STRICT
    #define STRICT 1
#endif

// this macro tells windows.h to not define min() and max() as macros: we need
// this as otherwise they conflict with standard C++ functions
#ifndef NOMINMAX
    #define NOMINMAX
#endif // NOMINMAX


// before including windows.h, define version macros at (currently) maximal
// values because we do all our checks at run-time anyhow
#ifndef WINVER
    // the only exception to the above is MSVC 6 which has a time bomb in its
    // headers: they warn against using them with WINVER >= 0x0500 as they
    // contain only part of the declarations and they're not always correct, so
    // don't define WINVER for it at all as this allows everything to work as
    // expected both with standard VC6 headers (which define WINVER as 0x0400
    // by default) and headers from a newer SDK (which may define it as 0x0500)
    #if !defined(__VISUALC__) || (__VISUALC__ >= 1300)
        #define WINVER 0x0600
    #endif
#endif

// define _WIN32_WINNT and _WIN32_IE to the highest possible values because we
// always check for the version of installed DLLs at runtime anyway (see
// wxApp::GetComCtl32Version()) unless the user really
// doesn't want to use APIs only available on later OS versions and had defined
// them to (presumably lower) values
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
#endif

#ifndef _WIN32_IE
    #define _WIN32_IE 0x0700
#endif

/* Deal with clash with __WINDOWS__ include guard */
#if defined(__WXWINCE__) && defined(__WINDOWS__)
#undef __WINDOWS__
#endif

// For IPv6 support, we must include winsock2.h before winsock.h, and
// windows.h include winsock.h so do it before including it
#if wxUSE_IPV6
    #include <winsock2.h>
#endif

#include <windows.h>

#if defined(__WXWINCE__) && !defined(__WINDOWS__)
#define __WINDOWS__
#endif

// #undef the macros defined in winsows.h which conflict with code elsewhere
#include "wx/msw/winundef.h"

// Types DWORD_PTR, ULONG_PTR and so on are used for 64-bit compatibility
// in the WINAPI SDK (they are an integral type that is the size of a
// pointer) on MSVC 7 and later. However, they are not available in older
// Platform SDKs, and since they are typedefs and not #defines we simply
// overwrite them if there is a chance that they're not defined
#if (!defined(_MSC_VER) || (_MSC_VER < 1300)) && !defined(__WIN64__)
    #define UINT_PTR unsigned int
    #define INT_PTR int
    #define HANDLE_PTR unsigned long
    #define LONG_PTR long
    #define ULONG_PTR unsigned long
    #define DWORD_PTR unsigned long
#endif // !defined(_MSC_VER) || _MSC_VER < 1300

#endif // _WX_WRAPWIN_H_
