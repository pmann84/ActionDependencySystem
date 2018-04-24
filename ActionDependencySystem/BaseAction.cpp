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
      if (!input->is_optional())
      {
         validated = validated && input->is_initialised();
      }
   }
   return validated;
}

bool BaseAction::validate_optional_inputs(std::vector<ActionConnection> connections)
{
   bool validated = true;

   for (int i = 0; i < m_inputs.size(); ++i)
   {
      auto& input = m_inputs[i];
      if (input->is_optional())
      {
         for (auto connection : connections)
         {
            if (connection.dst_action()->name() == m_name && connection.dst_input_idx() == i)
            {
               validated = validated && input->is_initialised();
            }
         }
      }
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

std::vector<std::shared_ptr<IAction>> BaseAction::get_subsequent_actions(std::vector<ActionConnection> connections)
{
   std::vector<std::shared_ptr<IAction>> connected_actions;
   if (!connections.empty())
   {
      for (auto action_connection : connections)
      {
         std::shared_ptr<IAction> dst_action = action_connection.dst_action();
         if (dst_action.get() != this)
         {
            connected_actions.push_back(dst_action);
         }
      }
   }
   return connected_actions;
}

std::vector<std::shared_ptr<IAction>> BaseAction::get_prior_actions(std::vector<ActionConnection> connections)
{
   std::vector<std::shared_ptr<IAction>> connected_actions;
   if (!connections.empty())
   {
      for (auto action_connection : connections)
      {
         std::shared_ptr<IAction> src_action = action_connection.src_action();
         if (src_action.get() != this)
         {
            connected_actions.push_back(src_action);
         }
      }
   }
   return connected_actions;
}
