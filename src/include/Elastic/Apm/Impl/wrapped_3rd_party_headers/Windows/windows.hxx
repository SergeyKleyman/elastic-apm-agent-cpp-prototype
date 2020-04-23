#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#ifndef VC_EXTRALEAN
#   define VC_EXTRALEAN
#endif

//
// The problem is caused by conflicting definitions of min and max in Windows.h
// http://support.microsoft.com/kb/143208
//
#ifndef NOMINMAX
#   define NOMINMAX
#endif

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"

#include <windows.h>

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"
