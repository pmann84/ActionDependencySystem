#include "CopyFileAction.h"

#include <sstream>
#include <iostream>
#include <experimental/filesystem>

#include "../ActionInput.h"

// Sets up the inputs
CopyFileAction::CopyFileAction()
{
   // Add inputs
   std::shared_ptr<IActionInput> inputFnInput = std::make_shared<ActionInput>("Input File Path");
   add_input(inputFnInput);

   std::shared_ptr<IActionInput> outputFnInput = std::make_shared<ActionInput>("Destination File Path");
   add_input(outputFnInput);

   // Add outputs
   std::shared_ptr<IActionInput> copiedFnOutput = std::make_shared<ActionInput>("Copied File Path");
   add_output(copiedFnOutput);
}

// Sets up the inputs then sets values for inputs
CopyFileAction::CopyFileAction(std::string in, std::string out) : CopyFileAction()
{
   set_input(0, std::make_any<std::string>(in));
   set_input(1, std::make_any<std::string>(out));
}

void CopyFileAction::run()
{
   const std::string output_file_name = std::any_cast<std::string>(m_inputs[1]->get());
   const std::string input_file_name = std::any_cast<std::string>(m_inputs[0]->get());

   std::cout << "Copying " << input_file_name << " to " << output_file_name << std::endl;

   std::experimental::filesystem::copy_options copy_options = std::experimental::filesystem::copy_options::overwrite_existing;
   std::experimental::filesystem::copy(input_file_name, output_file_name, copy_options); // copy file

   std::cout << "Copy to " << output_file_name << " complete!" << std::endl;
   m_outputs[0]->set(std::make_any<std::string>(output_file_name));
}
