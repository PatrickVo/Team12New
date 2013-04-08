
#pragma once

#pragma warning(disable: 4251)

#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define DBDLL_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif
