set PATH=D:\Qt\Qt5.3.2\5.3\msvc2012_opengl\bin
set TarPath=GeneratedFiles/Debug/
set PreCompile=-b stdafx.h
::moc EObjectListSheet.h -o %TarPath%moc_EObjectListSheet.cpp %PreCompile%
::/f 打开其后的文件
for /f %%i in (mocgenList.txt) do moc %%i.h -o %TarPath%moc_%%i.cpp %PreCompile%


