#include "CopyFileAction.h"

#include <sstream>
#include <iostream>

#include "ActionInput.h"

CopyFileAction::CopyFileAction(std::string in, std::string out)
{
   // Add inputs
   ActionInput inputFnInput("Input File Name");
   inputFnInput.set(in);
   add_input(inputFnInput);
   ActionInput outputFnInput("Destination File Name");
   outputFnInput.set(out);
   add_input(outputFnInput);
   // Add outputs
   ActionInput copiedFnOutput("Copied File Path");
   add_output(outputFnInput);
}

void CopyFileAction::run()
{
   const std::string output_file_name = m_inputs[1].get<std::string>();
   const std::string input_file_name = m_inputs[0].get<std::string>();
   std::stringstream ss;
   std::cout << "Copying " << input_file_name << " to " << output_file_name << std::endl;
   ss << "copy \"" << input_file_name << "\" \"" << output_file_name << "\"";
   std::system(ss.str().c_str());
   std::cout << "Copy to " << output_file_name << " complete!" << std::endl;
   m_outputs[0].set(output_file_name);
}