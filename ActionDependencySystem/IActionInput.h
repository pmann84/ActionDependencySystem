#ifndef __IACTION_INPUT_H__
#define __IACTION_INPUT_H__

#include <string>
#include <any>
#include <memory>
#include <vector>

class IActionInput
{
public:
   virtual ~IActionInput() = default;

   virtual std::string name() const = 0;
   virtual bool is_initialised() const = 0;

   virtual void set(std::any value) = 0;
   virtual std::any get() const = 0;
};

using ActionInputListT = std::vector<std::unique_ptr<IActionInput>>;

#endif // __IACTION_INPUT_H__