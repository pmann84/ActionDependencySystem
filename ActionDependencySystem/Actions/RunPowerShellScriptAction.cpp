#include "RunPowerShellScriptAction.h"

#include "../ActionInput.h"
#include <iostream>
#include <sstream>

RunPowershellScriptAction::RunPowershellScriptAction(std::string scriptPath)
{
   // Add inputs
   std::unique_ptr<IActionInput> scriptPathInput = std::make_unique<ActionInput>("Script File Path");
   scriptPathInput->set(std::make_any<std::string>(scriptPath));
   add_input(std::move(scriptPathInput));
   // Add outputs
   std::unique_ptr<IActionInput> scriptOutput = std::make_unique<ActionInput>("Script Output");
   add_output(std::move(scriptOutput));
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