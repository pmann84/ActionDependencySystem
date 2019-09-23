#ifndef __POWERSHELLSCRIPT_ACTION_H__
#define __POWERSHELLSCRIPT_ACTION_H__

#include "../BaseAction.h"

#include <string>

class ACTION_DEPENDENCY_SYSTEM_API RunPowershellScriptAction : public BaseAction
{
public:
   RunPowershellScriptAction();
   RunPowershellScriptAction(std::string);
   ~RunPowershellScriptAction() = default;

   void run() override;
};

#endif // __POWERSHELLSCRIPT_ACTION_H__