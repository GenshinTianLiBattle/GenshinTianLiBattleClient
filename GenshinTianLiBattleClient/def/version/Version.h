#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 46;
static const int version_build = 34;
static const char* version = "0.2.46";
static const char* version_hash = "68ad360";
static const char* build_version = "0.2.46.34-debug-68ad360";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 46;
static const int version_build = 34;
static const char* version = "0.2.46";
static const char* version_hash = "68ad360";
static const char* build_version = "0.2.46.34-master-68ad360";
#endif
}
//该文件自动生成，无需更改 
