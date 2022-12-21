#pragma once
namespace tl::battle::client::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 83;
static const int version_build = 70;
static const char* version = "0.2.83";
static const char* version_hash = "48a5534";
static const char* build_version = "0.2.83.70-debug-48a5534";
#else
static const int version_major = 0;
static const int version_minor = 2;
static const int version_patch = 83;
static const int version_build = 70;
static const char* version = "0.2.83";
static const char* version_hash = "48a5534";
static const char* build_version = "0.2.83.70-master-48a5534";
#endif
}
//该文件自动生成，无需更改 
