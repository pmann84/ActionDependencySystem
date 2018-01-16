#ifndef __BASE_ACTION_H__
#define __BASE_ACTION_H__

#include "IAction.h"

class BaseAction : public IAction
{
public:
   BaseAction() = default;
   virtual ~BaseAction() = default;

   void add_input(std::unique_ptr<IActionInput>) override;
   void add_output(std::unique_ptr<IActionInput>) override;
   
   virtual void run() = 0;

protected:
   ActionInputListT m_inputs;
   ActionInputListT m_outputs;
};

#endif // __IACTION_H__