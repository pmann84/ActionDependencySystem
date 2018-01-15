#include "BaseAction.h"

void BaseAction::add_input(ActionInput input)
{
   m_inputs.push_back(input);
}

void BaseAction::add_output(ActionInput output)
{
   m_outputs.push_back(output);
}
