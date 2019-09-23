#ifndef __DELAY_ACTION_H__
#define __DELAY_ACTION_H__

#include <string>
#include "../BaseAction.h"

class ACTION_DEPENDENCY_SYSTEM_API DelayAction : public BaseAction
{
public:
   DelayAction();
   DelayAction(const std::string name);
   DelayAction(const std::string name, unsigned int delay);
   ~DelayAction() final = default;

   void run() override;
};

#endif // __DELAY_ACTION_H__