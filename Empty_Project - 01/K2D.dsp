# Microsoft Developer Studio Project File - Name="K2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=K2D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "K2D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "K2D.mak" CFG="K2D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "K2D - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "K2D - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "K2D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "K2D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /NODEFAULTLIB:library /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "K2D - Win32 Release"
# Name "K2D - Win32 Debug"
# Begin Group "K2D_Engine"

# PROP Default_Filter ""
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\K2d\K2D_Collision.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Console.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Effect.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Engine.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Font.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Highscore.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Particle.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Sound.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Sprite.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_State.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Texture.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Tool.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Vector2.h
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Window.h
# End Source File
# Begin Source File

SOURCE=.\K2d\singleton.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\K2d\K2D_Console.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Engine.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Font.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_HighScore.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Particle.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Texture.cpp
# End Source File
# Begin Source File

SOURCE=.\K2d\K2D_Window.cpp
# End Source File
# End Group
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "Header"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CGame.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CGame.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Target
# End Project
