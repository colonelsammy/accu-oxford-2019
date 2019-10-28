#pragma once

#include <array>
#include <string>
#include <tuple>
#include <variant>

#define SPECIALIZE (1)

namespace typelist
{
  class magic_type
  {
    void const* ptr;
    size_t idx;
  public:
    template <typename TypeList, typename Ptr>
    static magic_type make_magic_type(Ptr const* obj_ptr)
    {
      using Te = std::remove_reference_t<Ptr>;
      return magic_type(index_of<Te, TypeList>::value, static_cast<Te const*>(obj_ptr));
    }
    inline size_t id() const
    {
      return idx;
    }
    template <typename Ptr>
    inline Ptr const& magic_cast() const
    {
      return *static_cast<Ptr const*>(ptr);
    }
  private:
    template <typename Ptr>
    magic_type(size_t index, Ptr const* obj_ptr)
      : ptr{ obj_ptr }
      , idx(index)
    {}
  };

  template <class... Ts> struct tuple
  {
  };

  template <class T, class... Ts>
  struct tuple<T, Ts...> : tuple<Ts...> {
  };

  namespace detail {
    template <typename Seq>
    struct size_impl;

    template <template <typename...> class Seq, typename... Ts>
    struct size_impl<Seq<Ts...>> {
      using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
    };
  }

  template <typename Seq>
  using tuple_size = typename detail::size_impl<Seq>::type;

  template <size_t, class> struct elem_type_holder;

  template <class T, class... Ts>
  struct elem_type_holder<0, tuple<T, Ts...>> {
    typedef T type;
  };

  template <size_t k, class T, class... Ts>
  struct elem_type_holder<k, tuple<T, Ts...>> {
    typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
  };

  template <class T, class Tuple>
  struct index_of;

  template <class T, class... Types>
  struct index_of<T, tuple<T, Types...>> {
    static const std::size_t value = 0;
  };

  template <class T, class U, class... Types>
  struct index_of<T, tuple<U, Types...>> {
    static const std::size_t value = 1 + index_of<T, tuple<Types...>>::value;
  };

  template <typename T>
  void print_type(T)
  {
    std::cout << typeid(T).name() << "\n";
  }

  template <typename T, typename... Args>
  void print_type(T, Args... args)
  {
    std::cout << typeid(T).name() << "\n";
    print_type(args...);
  }

  template <typename T>
  static auto remove_ref_wrapper(T const& arg)
  {
    return arg;
  }
  template <typename T>
  static auto remove_ref_wrapper(std::reference_wrapper<T> const& arg)
  {
    return arg.get();
  }

  template <typename List>
  struct virtual_arg_traits
  {
    template <typename T>
    static size_t index(T const& arg)
    {
      return arg.index();
    }
    static size_t index(magic_type const& arg)
    {
      return arg.id();
    }
    template <size_t ID, typename T>
    static auto extract_type(T const& arg)
    {
      const auto& ty = remove_ref_wrapper(std::get<ID>(arg));
      return ty;
    }
    template <size_t ID>
    static auto extract_type(magic_type const& arg)
    {
#ifdef USE_STD_TUPLE
      using Te = typename std::tuple_element_t<ID, List>;
#else
      using Te = typename elem_type_holder
        <ID, List>::type;
#endif
      const Te& ty = arg.template magic_cast<Te>();
      return ty;
    }
  };

  template <size_t NumArgs, size_t ID, size_t ArgIndex> struct dispatch_impl;

  template <size_t ArgIndex>
  struct dispatch_impl<1, 0, ArgIndex>
  {
    template <typename List, typename ReturnType, typename Exec, typename VirtualArgs>
    static ReturnType eval(Exec, const VirtualArgs& vargs) {
      // Any id that is outside the range of the typelist
      // is invalid and will end up here when we've tried
      // all the available ids and none of them have matched...
      size_t index = virtual_arg_traits<List>::index(vargs[0]);
      throw std::runtime_error(std::string("Bad argument type: had id=") + std::to_string(index));
    }
  };

  template <size_t ID, size_t ArgIndex>
  struct dispatch_impl<1, ID, ArgIndex>
  {
    template <typename List, typename ReturnType, typename Exec, typename VirtualArgs>
    static ReturnType eval(Exec exec, const VirtualArgs& vargs) {
#ifdef DEBUG_OUTPUT
      std::cout << "dispatch_impl::eval [" << ArgIndex << "] args=" << typeid(VirtualArgs).name() << "\n";
#endif
      auto varg0 = vargs[0];
      size_t id0 = virtual_arg_traits<List>::index(varg0);
      if (id0 == ID - 1)
      {
        const auto& lhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg0);
#ifdef DEBUG_OUTPUT
        std::cout << "eval " << id0 << ", ty=" << typeid(Te).name() << "\n";
#endif
        return exec(lhs);
      }
      return dispatch_impl<1, ID - 1, ArgIndex>::template eval<List, ReturnType>(exec, vargs);
    }
  };

  template <size_t ArgIndex>
  struct dispatch_impl<2, 0, ArgIndex>
  {
    template <typename List, typename ReturnType, typename Exec, typename VirtualArgs>
    static ReturnType eval(Exec, const VirtualArgs& vargs) {
      // Any id that is outside the range of the typelist
      // is invalid and will end up here when we've tried
      // all the available ids and none of them have matched...
      constexpr size_t NumArgs = 2;
      size_t index = virtual_arg_traits<List>::index(vargs[0]);
      throw std::runtime_error(std::string("Bad argument type: had id=") + std::to_string(index) + " for argument " + std::to_string(NumArgs - ArgIndex));
      //return ReturnType{};
    }
    template <typename List, typename ReturnType, typename Exec, typename LHS, typename VArg>
    static ReturnType eval_lhs(Exec, size_t id, const LHS&, const VArg&) {
      // Any id that is outside the range of the typelist
      // is invalid and will end up here when we've tried
      // all the available ids and none of them have matched...
      constexpr size_t NumArgs = 2;
      throw std::runtime_error(std::string("Bad argument type: had id=") + std::to_string(id) + " for argument " + std::to_string(NumArgs - ArgIndex));
      //return ReturnType{};
    }
    template <typename List, typename ReturnType, typename Exec, typename VArg, typename RHS>
    static ReturnType eval_rhs(Exec, size_t id, const VArg&, const RHS&) {
      // Any id that is outside the range of the typelist
      // is invalid and will end up here when we've tried
      // all the available ids and none of them have matched...
      constexpr size_t NumArgs = 2;
      throw std::runtime_error(std::string("Bad argument type: had id=") + std::to_string(id) + " for argument " + std::to_string(NumArgs - ArgIndex));
      //return ReturnType{};
    }
  };

  template <size_t ID, size_t ArgIndex>
  struct dispatch_impl<2, ID, ArgIndex>
  {
    template <typename List, typename ReturnType, typename Exec, typename VirtualArgs>
    static ReturnType eval(Exec exec, const VirtualArgs& vargs) {
      //constexpr size_t NumVArgs = tuple_size<VirtualArgs>::value;
      //constexpr size_t ListSize = tuple_size<List>::value;
  #ifdef DEBUG_OUTPUT
      std::cout << "dispatch_impl::eval [" << ArgIndex << "] args=" << typeid(VirtualArgs).name() << "\n";
  #endif
      auto varg0 = vargs[0];
      auto varg1 = vargs[1];
      size_t id0 = virtual_arg_traits<List>::index(varg0);
      size_t id1 = virtual_arg_traits<List>::index(varg1);
      if (id0 == id1)
      {
        if (id0 == ID - 1)
        {
          const auto& lhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg0);
          const auto& rhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg1);
#ifdef DEBUG_OUTPUT
          std::cout << "eval " << id0 << ", ty=" << typeid(Te).name() << "\n";
  #endif
          return exec(lhs, rhs);
        }
        return dispatch_impl<2, ID - 1, ArgIndex>::template eval<List, ReturnType>(exec, vargs);
      }
      else if (id0 == ID - 1)
      {
        const auto& lhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg0);
  #ifdef DEBUG_OUTPUT
        std::cout << "eval " << id0 << ", ty=" << typeid(Te).name() << "\n";
  #endif
        constexpr size_t OtherID = (ID == 2 ? 1 : 2);
        return dispatch_impl<2, OtherID, ArgIndex - 1>::template eval_lhs<List, ReturnType>(exec, id1, lhs, varg1);
      }
      else if (id1 == ID - 1)
      {
        const auto& rhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg1);
  #ifdef DEBUG_OUTPUT
        std::cout << "eval " << id1 << ", ty=" << typeid(Te).name() << "\n";
  #endif
        constexpr size_t OtherID = (ID == 2 ? 1 : 2);
        return dispatch_impl<2, OtherID, ArgIndex - 1>::template eval_rhs<List, ReturnType>(exec, id0, varg0, rhs);
      }
      return dispatch_impl<2, ID - 1, ArgIndex>::template eval<List, ReturnType>(exec, vargs);
    }
    template <typename List, typename ReturnType, typename Exec, typename LHS, typename VArg>
    static ReturnType eval_lhs(Exec exec, size_t id, const LHS& lhs, const VArg& varg) {
      //constexpr size_t NumVArgs = tuple_size<VirtualArgs>::value;
  #ifdef DEBUG_OUTPUT
      std::cout << "dispatch_impl::eval [" << ArgIndex << "] ty=" << typeid(LHS).name() << ", arg=" << typeid(VArg).name() << "\n";
  #endif
      if (id == ID - 1)
      {
        const auto& rhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg);
#ifdef DEBUG_OUTPUT
        std::cout << "eval " << id << ", ty=" << typeid(Te).name() << "\n";
  #endif
        return exec(lhs, rhs);
      }
      return dispatch_impl<2, ID - 1, ArgIndex>::template eval_lhs<List, ReturnType>(exec, id, lhs, varg);
    }
    template <typename List, typename ReturnType, typename Exec, typename VArg, typename RHS>
    static ReturnType eval_rhs(Exec exec, size_t id, const VArg& varg, const RHS& rhs) {
      //constexpr size_t NumVArgs = tuple_size<VirtualArgs>::value;
  #ifdef DEBUG_OUTPUT
      std::cout << "dispatch_impl::eval [" << ArgIndex << "] arg=" << typeid(VArg).name() << ", ty=" << typeid(RHS).name() << "\n";
  #endif
      if (id == ID - 1)
      {
        const auto& lhs = virtual_arg_traits<List>::extract_type<ID - 1>(varg);
#ifdef DEBUG_OUTPUT
        std::cout << "eval " << id << ", ty=" << typeid(Te).name() << "\n";
  #endif
        return exec(lhs, rhs);
      }
      return dispatch_impl<2, ID - 1, ArgIndex>::template eval_rhs<List, ReturnType>(exec, id, varg, rhs);
    }
  };

  template <size_t> struct args_iter;

  template <size_t, size_t> struct disp3;

  template <size_t VirtualArgIndex>
  struct disp3<0, VirtualArgIndex>
  {
    template <typename List, typename ReturnType, typename Exec, typename Types, typename VArg, typename VirtualArgs>
    static ReturnType eval(Exec, Types&&, const VArg& varg, const VirtualArgs&) {
      // Any id that is outside the range of the typelist
      // is invalid and will end up here when we've tried
      // all the available ids and none of them have matched...
      constexpr size_t NumVArgs = std::tuple_size<VirtualArgs>::value;
      size_t index = virtual_arg_traits<List>::index(varg);
      throw std::runtime_error(std::string("Bad argument type: had id=") + std::to_string(index) + " for argument " + std::to_string(NumVArgs - VirtualArgIndex));
    }
  };

  template <size_t ID, size_t VirtualArgIndex>
  struct disp3
  {
    template <typename List, typename ReturnType, typename Exec, typename Types, typename VArg, typename VirtualArgs>
    static ReturnType eval(Exec exec, Types&& types, const VArg& varg, const VirtualArgs& vargs) {
      constexpr size_t NumVArgs = std::tuple_size<VirtualArgs>::value;
#ifdef DEBUG_OUTPUT
      std::cout << "disp3::eval [" << VirtualArgIndex << "] ty=" << typeid(Types).name() << ", args=" << typeid(VirtualArgs).name() << "\n";
#endif
      size_t index = virtual_arg_traits<List>::index(varg);
      if (index == ID - 1)
      {
        const auto& p = virtual_arg_traits<List>::extract_type<ID - 1>(varg);
#ifdef DEBUG_OUTPUT
        std::cout << "eval " << varg.id() << ", ty=" << typeid(Te).name() << "\n";
#endif
        using Te = decltype(p);
        auto new_types = std::tuple_cat(types, std::tuple<Te>(p));
        return args_iter<VirtualArgIndex - 1>::template eval<List, ReturnType>(exec, new_types, vargs);
      }
      return disp3<ID - 1, VirtualArgIndex>::template eval<List, ReturnType>(exec, std::move(types), varg, vargs);
    }
  };

  // If we process all the input arguments, then we will end up
  // in this specialization and we have gathered all the required
  // types to dispatch to the callee's function.
  template<>
  struct args_iter<0> {

    template <typename ReturnType, typename Exec, typename Types>
    static ReturnType dispatch(Exec exec, Types&& types)
    {
#ifdef DEBUG_OUTPUT
      std::cout << "****** dispatch:\n";
      print_type(types);
#endif
      return exec(std::get<0>(types), std::get<1>(types));
    }

    template <typename List, typename ReturnType, typename Exec, typename Types, typename VirtualArgs>
    static ReturnType eval(Exec exec, Types&& types, const VirtualArgs&) {
#ifdef DEBUG_OUTPUT
      std::cout << "eval ty=" << typeid(Types).name() << "\n";
#endif
      return dispatch<ReturnType>(exec, std::move(types));
    }
  };

  template <size_t VirtualArgIndex>
  struct args_iter {
    template <typename List, typename ReturnType, typename Exec, typename Types, typename VirtualArgs>
    static ReturnType eval(Exec exec, Types&& types, const VirtualArgs& vargs) {
      constexpr size_t NumVArgs = std::tuple_size<VirtualArgs>::value;
#ifdef DEBUG_OUTPUT
      std::cout << "args::eval [" << VirtualArgIndex << "] ty=" << typeid(Types).name() << ", args=" << typeid(VirtualArgs).name() << "\n";
#endif
      // Reverse the order that we get the args so that we deal with lowest
      // index first.
      //auto varg = std::get<NumVArgs - VirtualArgIndex>(vargs);
      auto varg = vargs[NumVArgs - VirtualArgIndex];
      return disp3<NumVArgs, VirtualArgIndex>::template eval<List, ReturnType>(exec, std::move(types), varg, vargs);
    }
  };

  template <size_t I, typename List>
  struct list_traits
  {
    using BaseElementType = typename elem_type_holder<0, List>::type;
  };

  template <size_t I, typename... T>
  struct list_traits<I, std::variant<T...>>
  {
    using BaseElementType = typename std::variant_alternative_t<I, std::variant<T...>>;
  };

  namespace detail
  {
    template <size_t NumArgs>
    struct invoke_impl;

    template <>
    struct invoke_impl<1>
    {
      template <typename List, typename Exec, typename VirtualArgs>
      static auto invoke(Exec exec, const VirtualArgs& vargs)
      {
        using BaseElementType = typename list_traits<0, List>::BaseElementType;
        using ReturnType = decltype(exec(*static_cast<BaseElementType const*>(nullptr)));

        constexpr size_t ListSize = tuple_size<List>::value;
        constexpr size_t NumArgs = std::tuple_size<VirtualArgs>::value;
        static_assert(NumArgs == 1, "invoke_impl<1> should only be instantiated for 1 arg");
        return dispatch_impl<NumArgs, ListSize, NumArgs>::template eval<List, ReturnType>(exec, vargs);
      }
    };

#ifdef SPECIALIZE
    template <>
    struct invoke_impl<2>
    {
      template <typename List, typename Exec, typename VirtualArgs>
      static auto invoke(Exec exec, const VirtualArgs& vargs)
      {
        using BaseElementType = typename list_traits<0, List>::BaseElementType;
        using ReturnType = decltype(exec(*static_cast<BaseElementType const*>(nullptr), *static_cast<BaseElementType const*>(nullptr)));

        constexpr size_t ListSize = tuple_size<List>::value;
        constexpr size_t NumArgs = std::tuple_size<VirtualArgs>::value;
        return dispatch_impl<NumArgs, ListSize, NumArgs>::template eval<List, ReturnType>(exec, vargs);
      }
    };
#else
    template <size_t NumArgs>
    struct invoke_impl
    {
      template <typename List, typename Exec, typename VirtualArgs>
      static auto invoke(Exec exec, const VirtualArgs& vargs)
      {
        using BaseElementType = typename list_traits<0, List>::BaseElementType;
        using ReturnType = decltype(exec(
          *static_cast<BaseElementType const*>(nullptr),
          *static_cast<BaseElementType const*>(nullptr)));
        return args_iter<NumArgs>::template eval<List, ReturnType>(exec, std::tuple<>{}, vargs);
      }
    };
#endif
  }

  template <typename List, typename Exec, typename VirtualArgs>
  auto dispatch(Exec exec, VirtualArgs const& vargs) {
#ifdef DEBUG_OUTPUT
    std::cout << "invoke: " << typeid(ReturnType).name() << "\n";
#endif
    constexpr size_t NumArgs = std::tuple_size<VirtualArgs>::value;
    return detail::invoke_impl<NumArgs>::template invoke<List>(exec, vargs);
  }
}
