/* 
 * File: stdx
 * Author: Amlal El Mahrouss, 
 * Copyright 2023-2025, Amlal El Mahrouss all rights reserved. 
 */

#ifndef _STDX
#define _STDX

#include <stdexcept>

namespace stdx
{
  enum class ret
  {
    okay,
    err
  };

  struct opt final
  {
    explicit opt(const ret& ret)
      : m_ret(ret)
    {}

    opt& expect(const char* input)
    {
       if (m_ret == ret::err)
       {
          throw std::runtime_error(input);
       }
  
        return *this;
    }

  private:
    ret m_ret;

  };

  template <typename Teller, typename... Args>
  stdx::ret eval(Teller tell, Args... arg)
  {
    return tell(arg...) ? stdx::ret::okay : stdx::ret::err;
  }

  namespace traits
  {
    struct int_eq_teller
    {
      explicit int_eq_teller() {}
    
      bool operator()(int a, int b)
      {
        return (a == b);
      }
    };

    struct int_greater_than_teller
    {
      explicit int_greater_than_teller() {}
    
      bool operator()(int a, int b)
      {
        return (a > b);
      }
    };

    struct int_less_than_teller
    {
      explicit int_less_than_teller() {}
    
      bool operator()(int a, int b)
      {
        return (a < b);
      }
    };
  }

  template <typename... Lst>
  ret eval_less_than(Lst... arg)
  {
    static traits::int_less_than_teller eq;
    return eq(arg...) ? ret::okay : ret::err;
  }

  template <typename... Lst>
  ret eval_eq(Lst... arg)
  {
    static traits::int_eq_teller less_than;
    return less_than(arg...) ? ret::okay : ret::err;
  }

  template <typename... Lst>
  ret eval_greater(Lst... arg)
  {
    static traits::int_greater_than_teller greater_than;
    return greater_than(arg...) ? ret::okay : ret::err;
  }

} /* namespace stdx */

#endif /* ifndef _STDX */
