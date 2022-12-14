#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 22;
static const int version_build = 11;
static const char* version = "0.2.22";
static const char* version_hash = "5ed714b";
static const char* build_version = "0.2.22.11-debug-5ed714b";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 22;
static const int version_build = 11;
static const char* version = "0.2.22";
static const char* version_hash = "5ed714b";
static const char* build_version = "0.2.22.11-master-5ed714b";
#endif
}
//该文件自动生成，无需更改 
