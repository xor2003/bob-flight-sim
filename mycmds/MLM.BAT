
@echo off
set SP=%@char[32]
goto %1_a

rem ****************************************
rem * Enters here to write makefile lists
rem ****************************************

:list_a

echo.>> %outfile
echo scale%2 = $(dest)\img%@eval[%2]0000.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0001.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0002.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0003.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0004.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0005.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0006.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0007.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0008.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0009.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0010.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0011.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0012.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0013.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0014.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0015.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0016.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0017.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0018.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0019.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0020.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0021.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0022.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0023.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0024.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0025.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0026.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0027.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0028.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0029.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0030.x8\ >> %outfile
echo           $(dest)\img%@eval[%2]0031.x8 >> %outfile
echo.>> %outfile
goto done

rem ****************************************
rem * Write 8-bit single palette data
rem ****************************************

:sdatasub_a

iff "%2"=="1" then
	echo $(dest)\img%@eval[%2]00%3.x8: $(srcl)\img00%3.pcx \>> %outfile
	echo %SP							\bob\debug\obj\pclust2.x8 >> %outfile
	echo %SP echo -es -r \bob\debug\obj\pclust2.x8 %=> domap.res >> %outfile
	echo %SP echo -r $(srcl)\img00%3.pcx -cw256h256 %=>%=> domap.res >> %outfile
	echo %SP echo -w $(dest)\img%@eval[%2]00%3.x8 %=>%=> domap.res >> %outfile
	echo %SP tt2 -d -r domap.res >> %outfile
elseiff "%2"=="2" then
	echo $(dest)\img%@eval[%2]00%3.x8: $(srcl)\img%@eval[%2]00%3.pcx \>> %outfile
	echo %SP							$(dest)\palclust.x8 >> %outfile
	echo %SP echo -es -r $(palsrc)\palclust.x8 %=> domap.res >> %outfile
	echo %SP echo -r $(srcl)\img%@eval[%2]00%3.pcx -cw256h256 %=>%=> domap.res >> %outfile
	echo %SP echo -w $(dest)\img%@eval[%2]00%3.x8 %=>%=> domap.res >> %outfile
	echo %SP tt2 -d -r domap.res >> %outfile
endiff
echo.>> %outfile

goto done

:sdata_a

for %i in (00 01 02 03 04 05 06 07) do call %0 sdatasub %2 %i
for %i in (08 09 10 11 12 13 14 15) do call %0 sdatasub %2 %i
for %i in (16 17 18 19 20 21 22 23) do call %0 sdatasub %2 %i
for %i in (24 25 26 27 28 29 30 31) do call %0 sdatasub %2 %i

goto done

rem ****************************************
rem First time in goes here
rem ****************************************

:NewPal_a
echo Updating landscape palette

set srcpath=s:\projects\bob\artsrc\
tt2 -r %srcpath\image16\img0000.pcx -w %srcpath\landscap\land.pal
set srcpath=
goto done

:_a

echo Making landscape textures...

del /q ..\game\landmaps\img0*.* >&NUL
del /q ..\game\landmap2\img0*.* >&NUL

rem ****************************************
rem * Write makefile header block
rem ****************************************
set srcpath=s:\projects\bob\artsrc\

set outfile=makefile\mlm.mke
echo ## Auto Generated by mlm.bat > %outfile
echo.>> %outfile
echo ## paths >> %outfile
echo.>> %outfile
echo src = %srcpath%landscap >> %outfile
echo srcl = %srcpath%imagemap >> %outfile
echo palsrc = ..\game\landmaps >> %outfile
rem echo srch = %srcpath%image16 >> %outfile
echo dest = ..\game\landmaps >> %outfile
rem echo dest2 = ..\game\landmap2 >> %outfile
echo.>> %outfile
echo ## utilities >> %outfile
echo.>> %outfile
echo mapmke= tt2 >> %outfile
echo.>> %outfile

rem ****************************************
rem * Write makefile file lists
rem ****************************************

for %i in (1 2) do call %0 list %i

echo.>> %outfile
echo all:  $(scale1)\ >> %outfile
echo       $(scale2) >> %outfile
echo.>> %outfile

rem ****************************************
rem * Write makedata file lists
rem ****************************************

for %i in (1 2) do call %0 sdata %i

echo 8-bit single palette version

:make45 -s -f %outfile

rem ****************************************
rem * Write makefile header block
rem ****************************************

set srcpath=s:\projects\bob\artsrc\

echo ## Auto Generated by mlm.bat > %outfile
echo.>> %outfile
echo ## paths >> %outfile
echo.>> %outfile
echo src = %srcpath%landscap >> %outfile
echo srcl = %srcpath%image16 >> %outfile
echo palsrc = ..\game\landmap2 >> %outfile
echo dest = ..\game\landmap2 >> %outfile
echo.>> %outfile
echo ## utilities >> %outfile
echo.>> %outfile
echo mapmke= tt2 >> %outfile
echo.>> %outfile

rem ****************************************
rem * Write makefile file lists
rem ****************************************

for %i in (1 2) do call %0 list %i

echo.>> %outfile
echo all:  $(scale1)\ >> %outfile
echo       $(scale2) >> %outfile
echo.>> %outfile

rem ****************************************
rem * Write makedata file lists
rem ****************************************

for %i in (1 2) do call %0 sdata %i

echo 16-bit multipalette version

make45 -s -f %outfile

rem del /q %outfile

unset outfile

echo Done.

rem ****************************************
rem * Way out!
rem ****************************************

:done 
set SP=
