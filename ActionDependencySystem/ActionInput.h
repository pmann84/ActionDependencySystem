#ifndef __ACTION_INPUT_H__
#define __ACTION_INPUT_H__

#include <optional>
#include <any>
#include <string>
#include <vector>
#include <memory>

class ActionInput
{
public:
   ActionInput(const std::string name) 
      : m_name(name)
      , m_optional(false)
   {
   }
   ~ActionInput() = default;

   std::string name() const
   {
      return m_name;
   }

   bool is_initialised() const
   {
      return m_value.has_value();
   }

   bool is_optional() const
   {
      return m_optional;
   }

   void set_optional(const bool optional)
   {
      m_optional = optional;
   }

   void set(std::any value)
   {
      m_value = value;
   }

   std::any get() const
   {
      return m_value.value();
   }

   template<typename Type>
   void set(Type value)
   {
      m_value = std::make_any<Type>(value);
      
   }
   
   template<typename Type>
   Type get() const
   {
      return std::any_cast<Type>(m_value.value());
   }

private:
   std::string m_name;
   std::optional<std::any> m_value;
   bool m_optional;
};

using ActionInputListT = std::vector<std::shared_ptr<ActionInput>>;

#endif // __IACTION_INPUT_H__
