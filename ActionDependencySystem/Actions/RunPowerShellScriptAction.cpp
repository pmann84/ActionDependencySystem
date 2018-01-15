#include "RunPowerShellScriptAction.h"

RunPowershellScriptAction::RunPowershellScriptAction(std::string scriptPath)
{
   // Add inputs
   ActionInput scriptPathInput("Script File Path");
   scriptPathInput.set(scriptPath);
   add_input(scriptPathInput);
   // Add outputs
   ActionInput scriptOutput("Output");
   add_output(scriptOutput);
}

void RunPowershellScriptAction::run()
{
}