#ifndef __BASE_ACTION_H__
#define __BASE_ACTION_H__

#include <vector>

#include "ActionInput.h"

class BaseAction
{
public:
   BaseAction() = default;
   virtual ~BaseAction() = default;

   void add_input(ActionInput);
   void add_output(ActionInput);
   
   virtual void run() = 0;

private:

   std::vector<ActionInput> m_inputs;
   std::vector<ActionInput> m_outputs;
};

#endif // __IACTION_H__