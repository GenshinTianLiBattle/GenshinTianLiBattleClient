#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 54;
static const int version_build = 42;
static const char* version = "0.2.54";
static const char* version_hash = "d873864";
static const char* build_version = "0.2.54.42-debug-d873864";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 54;
static const int version_build = 42;
static const char* version = "0.2.54";
static const char* version_hash = "d873864";
static const char* build_version = "0.2.54.42-master-d873864";
#endif
}
//该文件自动生成，无需更改 
