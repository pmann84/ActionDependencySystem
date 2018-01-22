#include "BaseAction.h"

BaseAction::BaseAction()
{
   // Assign a name here...default to name of class typeid(class).name
   m_name = "BaseAction";
}

void BaseAction::name(std::string name)
{
   m_name = name;
}

void BaseAction::add_input(std::shared_ptr<IActionInput> input)
{
   m_inputs.push_back(input);
}

void BaseAction::add_output(std::shared_ptr<IActionInput> output)
{
   m_outputs.push_back(output);
}

void BaseAction::set_input(int i, std::any value)
{
   m_inputs[i]->set(value);
}

std::shared_ptr<IActionInput> BaseAction::get_output(const int i)
{
   return m_outputs[i];
}

bool BaseAction::validate_inputs()
{
   bool validated = true;
   for (auto input : m_inputs)
   {
      validated = validated && input->is_initialised();
   }
   return validated;
}
