@echo off
copy /Y release\BIWidgets.dll d:\Qt\6.8.3\msvc2022_64\plugins\designer\BIWidgets.dll
copy /Y debug\BIWidgetsd.dll d:\Qt\6.8.3\msvc2022_64\plugins\designer\BIWidgetsd.dll
copy /Y release\BIWidgets.dll d:\Qt\Tools\QtCreator\bin\plugins\designer\BIWidgets.dll
copy /Y debug\BIWidgetsd.dll d:\Qt\Tools\QtCreator\bin\plugins\designer\BIWidgetsd.dll