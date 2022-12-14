for /f %%x in (def\version\version.ver) do (
	set version=%%x
)
for /f  "tokens=1,2,3,4 delims=.-" %%a  in  ("%version%")  do (
	set v1=%%a
	set v2=%%b
	set /a v3=%%c+1
    set /a v4=%%d+1
)

if exist def\version\version.branch (
	del def\version\version.branch
)
if exist def\version\version_hash.hash (
	del def\version\version_hash.hash
)

git rev-parse --abbrev-ref HEAD>>  def\version\version.branch
git log -n1 --format=format:"%%h">> def\version\version_hash.hash

for /f %%x in (def\version\version.branch) do (
	set v5=%%x
)
for /f %%x in (def\version\version_hash.hash) do (
	set v6=%%x
)



set newVersionP1=0
set newVersionP2=0
if exist def\version\version.ver (
	for /f "tokens=1,2 delims=.-" %%a in (def\version\version.ver) do (
		set newVersionP1=%%a
		set newVersionP2=%%b
	)
)

if not "!newVersionP1!"=="" (
	if %newVersionP1% GTR %v1% (
		set /a v1=%newVersionP1%
		set /a v2=0
		set /a v3=0
	)
)
if not "%newVersionP2%"=="" (
	if %newVersionP2% GTR %v2% (
		set /a v2=%newVersionP2%
		set /a v3=0
	)
)

if exist def\version\Version.h (
    del def\version\Version.h
)

echo #pragma once>>def\version\Version.h
echo namespace tl::battle::client::version>>def\version\Version.h
echo {>>def\version\Version.h
echo %#ifdef _DEBUG>>def\version\Version.h
echo static const int version_major = 0;>>def\version\Version.h
echo static const int version_minor = %v2%;>>def\version\Version.h
echo static const int version_patch = %v3%;>>def\version\Version.h
echo static const int version_build = %v4%;>>def\version\Version.h
echo static const char* version = "0.%v2%.%v3%";>>def\version\Version.h
echo static const char* version_hash = "%v6%";>>def\version\Version.h
echo static const char* build_version = "0.%v2%.%v3%.%v4%-debug-%v6%";>>def\version\Version.h
echo %#else>>def\version\Version.h
echo static const int version_major = %v1%;>>def\version\Version.h
echo static const int version_minor = %v2%;>>def\version\Version.h
echo static const int version_patch = %v3%;>>def\version\Version.h
echo static const int version_build = %v4%;>>def\version\Version.h
echo static const char* version = "%v1%.%v2%.%v3%";>>def\version\Version.h
echo static const char* version_hash = "%v6%";>>def\version\Version.h
echo static const char* build_version = "%v1%.%v2%.%v3%.%v4%-%v5%-%v6%";>>def\version\Version.h
echo %#endif>>def\version\Version.h
echo }>>def\version\Version.h
echo //该文件自动生成，无需更改 >>def\version\Version.h

if exist def\version\version.ver (
    del def\version\version.ver
)

echo %v1%.%v2%.%v3%.%v4%>>def\version\version.ver

echo build version : %v1%.%v2%.%v3%.%v4%-%v5%-%v6% 


