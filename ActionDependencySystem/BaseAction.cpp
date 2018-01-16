#include "BaseAction.h"

void BaseAction::add_input(std::unique_ptr<IActionInput> input)
{
   m_inputs.push_back(std::move(input));
}

void BaseAction::add_output(std::unique_ptr<IActionInput> output)
{
   m_outputs.push_back(std::move(output));
}
