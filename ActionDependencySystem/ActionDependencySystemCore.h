#pragma once

#ifdef ACTION_DEPENDENCY_SYSTEM_BUILD_DLL
   #define ACTION_DEPENDENCY_SYSTEM_API __declspec(dllexport)
#else
   #define ACTION_DEPENDENCY_SYSTEM_API __declspec(dllimport)
#endif
