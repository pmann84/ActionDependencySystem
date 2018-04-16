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

void BaseAction::add_input(std::shared_ptr<ActionInput> input)
{
   m_inputs.push_back(input);
}

void BaseAction::add_output(std::shared_ptr<ActionInput> output)
{
   m_outputs.push_back(output);
}

void BaseAction::set_input(int i, std::any value)
{
   m_inputs[i]->set(value);
}

std::shared_ptr<ActionInput> BaseAction::get_output(const int i)
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

std::vector<std::string> BaseAction::invalid_inputs()
{
   std::vector<std::string> invalid_inputs;
   for (auto input : m_inputs)
   {
      if (!input->is_initialised() && !input->is_optional())
      {
         invalid_inputs.push_back(input->name());
      }
   }
   return invalid_inputs;
}