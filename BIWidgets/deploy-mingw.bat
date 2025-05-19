@echo off
copy /Y release\BIWidgets.dll d:\Qt\6.8.0\mingw_64\plugins\designer\BIWidgets.dll
copy /Y debug\BIWidgetsd.dll d:\Qt\6.8.0\mingw_64\plugins\designer\BIWidgetsd.dll
copy /Y release\BIWidgets.dll d:\Qt\qtcreator-15.0.0\bin\plugins\designer\BIWidgets.dll
copy /Y debug\BIWidgetsd.dll d:\Qt\qtcreator-15.0.0\bin\plugins\designer\BIWidgetsd.dll
copy /Y release\BIWidgets.dll d:\Qt\Tools\QtCreator\bin\plugins\designer\BIWidgets.dll
copy /Y debug\BIWidgetsd.dll d:\Qt\Tools\QtCreator\bin\plugins\designer\BIWidgetsd.dll