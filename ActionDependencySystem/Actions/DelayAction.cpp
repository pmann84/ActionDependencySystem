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

   // Add outputs
   std::shared_ptr<ActionInput> outputDummy = std::make_shared<ActionInput>("Dummy Output");
   add_output(outputDummy);
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
   std::cout << "Sleeping for " << delay << "s..." << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(delay));
   m_outputs[0]->set(std::make_any<bool>(true));
}
