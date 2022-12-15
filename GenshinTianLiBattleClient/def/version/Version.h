#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 25;
static const int version_build = 13;
static const char* version = "0.2.25";
static const char* version_hash = "ef4ebed";
static const char* build_version = "0.2.25.13-debug-ef4ebed";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 25;
static const int version_build = 13;
static const char* version = "0.2.25";
static const char* version_hash = "ef4ebed";
static const char* build_version = "0.2.25.13-master-ef4ebed";
#endif
}
//该文件自动生成，无需更改 
