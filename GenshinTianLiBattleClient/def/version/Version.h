#pragma once
namespace tl::battle::client
{
	namespace version
	{
#ifdef _DEBUG
			const char* version = "0.0.0";
			int version_major = 0;
			int version_minor = 0;
			int version_patch = 0;
#else
			const char* version = "0.1.0";
			int version_major = 0;
			int version_minor = 1;
			int version_patch = 0;
#endif // _DEBUG

	}
}