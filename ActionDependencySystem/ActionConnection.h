#ifndef __ACTION_CONNECTION_H__
#define __ACTION_CONNECTION_H__

#include "IAction.h"

class ActionConnection
{
public:
   ActionConnection(std::shared_ptr<IAction> src, int src_idx, std::shared_ptr<IAction> dst, int dst_idx)
      : m_src_action(src)
      , m_dst_action(dst)
      , m_src_action_output_idx(src_idx)
      , m_dst_action_input_idx(dst_idx)
   {
   }
   ~ActionConnection() = default;

   std::shared_ptr<IAction> src_action() { return m_src_action; }
   std::shared_ptr<IAction> dst_action() { return m_dst_action; }
   int src_output_idx() { return m_src_action_output_idx; }
   int dst_input_idx() { return m_dst_action_input_idx; }

   bool is_src(std::shared_ptr<IAction> action) { return m_src_action == action; }
   bool is_dst(std::shared_ptr<IAction> action) { return m_dst_action == action; }

private:
   int m_src_action_output_idx;
   int m_dst_action_input_idx;
   std::shared_ptr<IAction> m_src_action;
   std::shared_ptr<IAction> m_dst_action;
};

#endif // __ACTION_CONNECTION_H__