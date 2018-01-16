#include "CopyFileAction.h"

#include <sstream>
#include <iostream>

#include "../ActionInput.h"

CopyFileAction::CopyFileAction(std::string in, std::string out)
{
   // Add inputs
   std::unique_ptr<IActionInput> inputFnInput = std::make_unique<ActionInput>("Input File Path");
   inputFnInput->set(std::make_any<std::string>(in));
   add_input(std::move(inputFnInput));

   std::unique_ptr<IActionInput> outputFnInput = std::make_unique<ActionInput>("Destination File Path");
   outputFnInput->set(std::make_any<std::string>(out));
   add_input(std::move(outputFnInput));

   // Add outputs
   std::unique_ptr<IActionInput> copiedFnOutput = std::make_unique<ActionInput>("Copied File Path");
   add_output(std::move(copiedFnOutput));
}

void CopyFileAction::run()
{
   const std::string output_file_name = std::any_cast<std::string>(m_inputs[1]->get());
   const std::string input_file_name = std::any_cast<std::string>(m_inputs[0]->get());
   std::stringstream ss;
   std::cout << "Copying " << input_file_name << " to " << output_file_name << std::endl;
   ss << "copy \"" << input_file_name << "\" \"" << output_file_name << "\"";
   std::system(ss.str().c_str());
   std::cout << "Copy to " << output_file_name << " complete!" << std::endl;
   m_outputs[0]->set(std::make_any<std::string>(output_file_name));
}