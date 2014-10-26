set PATH=D:\Qt\Qt5.3.2\5.3\msvc2012_opengl\bin
set TarPath=GeneratedFiles/Debug/
moc EObjectListSheet.h -o %TarPath%moc_EObjectListSheet.cpp
moc EPropertySheet.h -o %TarPath%moc_EPropertySheet.cpp
moc EPropertySheetDelegate.h -o %TarPath%moc_EPropertySheetDelegate.cpp
moc epropertytreeview.h -o %TarPath%moc_epropertytreeview.cpp
moc ESceneframe.h -o %TarPath%moc_ESceneframe.cpp
moc editor.h -o %TarPath%moc_editor.cpp
moc Editorapp.h -o %TarPath%moc_Editorapp.cpp
moc EObjListSheetTreeView.h -o %TarPath%moc_EObjListSheetTreeView.cpp
