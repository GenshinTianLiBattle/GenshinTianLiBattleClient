#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 49;
static const int version_build = 37;
static const char* version = "0.2.49";
static const char* version_hash = "1de7681";
static const char* build_version = "0.2.49.37-debug-1de7681";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 49;
static const int version_build = 37;
static const char* version = "0.2.49";
static const char* version_hash = "1de7681";
static const char* build_version = "0.2.49.37-master-1de7681";
#endif
}
//该文件自动生成，无需更改 
