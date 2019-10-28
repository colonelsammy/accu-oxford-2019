#pragma once
#include <operation_definitions.hpp>

namespace demo1
{
  struct magic_type;

  struct vtable_t
  {
    void(*op)(void const* this_, magic_type const* invoke, operations& ops);
  };

  template <typename T>
  vtable_t const vtable_for_t = {
    [](void const* this_, magic_type const* invoke, operations& ops) -> void {
      invoke->call(static_cast<T const*>(this_), ops);
    }
  };

  struct magic_type
  {
    vtable_t const* const vptr;
    void const* ptr;

    template <typename Ptr>
    magic_type(Ptr const* p)
      : vptr{ &vtable_for_t<Ptr> }
      , ptr{ p }
    {}

    void call(operations& ops)
    {
      vptr->op(ptr, this, ops);
    }

    template <typename T>
    static void
      call(T const* obj, operations& ops);
  };
}
