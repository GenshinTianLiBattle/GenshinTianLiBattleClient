#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 124;
static const int version_build = 111;
static const char* version = "0.2.124";
static const char* version_hash = "d9554a0";
static const char* build_version = "0.2.124.111-debug-d9554a0";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 124;
static const int version_build = 111;
static const char* version = "0.2.124";
static const char* version_hash = "d9554a0";
static const char* build_version = "0.2.124.111-master-d9554a0";
#endif
}
//该文件自动生成，无需更改 
