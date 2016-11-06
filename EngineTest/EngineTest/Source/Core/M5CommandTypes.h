/******************************************************************************/ 
/*! 
\file   M5CommmandTypes.h 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the commands in the 
current project.  PreBuild.bat looks for files of the type *Command.h 
and creates an enumeration value of CMD_*Command. 
*/ 
/******************************************************************************/ 
#ifndef M5COMMAND_TYPE_H 
#define M5COMMAND_TYPE_H 
#include <string> 
 
 
//! AutoGenerated enum based on command file names  
enum M5CommandTypes {  
CMD_ChangeStageCommand, 
CMD_PauseStageCommand, 
CMD_QuitCommand, 
CMD_ResumeStageCommand, 
CMD_INVALID 
}; 
 
 
//! AutoGenerated function to convert strings to our M5CommandTypes type 
inline M5CommandTypes StringToCommand(const std::string& string) { 
if(string == "ChangeStageCommand") return CMD_ChangeStageCommand; 
if(string == "PauseStageCommand") return CMD_PauseStageCommand; 
if(string == "QuitCommand") return CMD_QuitCommand; 
if(string == "ResumeStageCommand") return CMD_ResumeStageCommand; 
return CMD_INVALID; 
} 
#endif //M5COMMAND_TYPE_H 
