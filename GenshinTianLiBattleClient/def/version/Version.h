#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 125;
static const int version_build = 112;
static const char* version = "0.2.125";
static const char* version_hash = "d1f90cf";
static const char* build_version = "0.2.125.112-debug-d1f90cf";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 125;
static const int version_build = 112;
static const char* version = "0.2.125";
static const char* version_hash = "d1f90cf";
static const char* build_version = "0.2.125.112-master-d1f90cf";
#endif
}
//该文件自动生成，无需更改 
