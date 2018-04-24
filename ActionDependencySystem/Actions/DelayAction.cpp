#include "DelayAction.h"
#include <thread>
#include <chrono>
#include <iostream>

// Sets up the inputs
DelayAction::DelayAction()
{
   // Add inputs
   std::shared_ptr<ActionInput> inputDelayTime = std::make_shared<ActionInput>("Delay Time (s)");
   add_input(inputDelayTime);

   std::shared_ptr<ActionInput> maxRangeInput = std::make_shared<ActionInput>("Max Range (s)");
   maxRangeInput->set_optional(true);
   add_input(maxRangeInput);

   // Add outputs
   std::shared_ptr<ActionInput> outputDelay = std::make_shared<ActionInput>("New Delay Time(s)");
   add_output(outputDelay);
}

DelayAction::DelayAction(const std::string name) : DelayAction()
{
   BaseAction::name(name);
}

DelayAction::DelayAction(const std::string name, unsigned delay) : DelayAction(name)
{
   set_input(0, std::make_any<unsigned int>(delay));
}

void DelayAction::run()
{
   const unsigned int delay = m_inputs[0]->get<unsigned int>();
   std::cout << "Action [" << m_name << "] sleeping for " << delay << "s..." << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(delay));
   // Calculate new time
   int range = 4;
   if (m_inputs[1]->is_initialised())
   {
      range = m_inputs[1]->get<unsigned int>();
   }
   int min = -range;
   int max = range;
   int factor = min + (rand() % static_cast<int>(max - min + 1));
   m_outputs[0]->set(std::make_any<unsigned int>(delay + factor));
   std::cout << "Adding [" << factor << "] to delay time - new delay [" << delay + factor << "]" << std::endl;
   std::cout << "Action [" << m_name << "] complete!" << std::endl;
}
