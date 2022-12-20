#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 77;
static const int version_build = 64;
static const char* version = "0.2.77";
static const char* version_hash = "8856aeb";
static const char* build_version = "0.2.77.64-debug-8856aeb";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 77;
static const int version_build = 64;
static const char* version = "0.2.77";
static const char* version_hash = "8856aeb";
static const char* build_version = "0.2.77.64-master-8856aeb";
#endif
}
//该文件自动生成，无需更改 
