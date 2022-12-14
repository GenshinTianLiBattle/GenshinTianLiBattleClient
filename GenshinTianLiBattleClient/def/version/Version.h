#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 23;
static const int version_build = 12;
static const char* version = "0.2.23";
static const char* version_hash = "0a9a1a2";
static const char* build_version = "0.2.23.12-debug-0a9a1a2";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 23;
static const int version_build = 12;
static const char* version = "0.2.23";
static const char* version_hash = "0a9a1a2";
static const char* build_version = "0.2.23.12-master-0a9a1a2";
#endif
}
//该文件自动生成，无需更改 
