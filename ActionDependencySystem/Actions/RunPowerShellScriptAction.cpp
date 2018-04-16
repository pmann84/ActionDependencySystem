#include "RunPowerShellScriptAction.h"

#include "../ActionInput.h"
#include <iostream>
#include <sstream>

RunPowershellScriptAction::RunPowershellScriptAction()
{
   // Add inputs
   std::shared_ptr<ActionInput> scriptPathInput = std::make_shared<ActionInput>("Script File Path");
   add_input(scriptPathInput);

   // Add outputs
   std::shared_ptr<ActionInput> scriptOutput = std::make_shared<ActionInput>("Script Output");
   add_output(scriptOutput);
}

RunPowershellScriptAction::RunPowershellScriptAction(std::string scriptPath)
{
   set_input(0, std::make_any<std::string>(scriptPath));
}

void RunPowershellScriptAction::run()
{
   const std::string script_path = std::any_cast<std::string>(m_inputs[0]->get());
   std::stringstream ss;
   std::cout << "Running " << script_path << "..." << std::endl;
   ss << "start powershell.exe -ExecutionPolicy RemoteSigned \"" << script_path << "\"";
   std::cout << "Command: " << ss.str() << std::endl;
   std::system(ss.str().c_str());
   std::cout << "Script Complete!" << std::endl;
   // Need to figure out how to get stdout and stderr outputs!!!!
   //m_outputs[0]->set(std::make_any<std::string>(output_file_name));
}