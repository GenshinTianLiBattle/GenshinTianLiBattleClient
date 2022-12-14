#pragma once
namespace tl::battle::client
{
	namespace version
	{
#ifdef _DEBUG
			static const char* version = "0.0.0";
			static int version_major = 0;
			static int version_minor = 0;
			static int version_patch = 0;
#else		
			static const char* version = "0.1.0";
			static int version_major = 0;
			static int version_minor = 1;
			static int version_patch = 0;
#endif // _DEBUG

	}
}