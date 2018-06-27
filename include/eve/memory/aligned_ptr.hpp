//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MEMORY_ALIGNED_PTR_HPP_INCLUDED
#define EVE_MEMORY_ALIGNED_PTR_HPP_INCLUDED

#include <eve/memory/is_aligned.hpp>
#include <type_traits>
#include <cassert>

namespace eve
{
  template<typename Type, std::size_t Alignment = alignof(Type)>
  struct aligned_ptr
  {
    static_assert(is_power_of_2(Alignment), "[eve] Alignment must be a power of 2");

    using pointer = std::add_pointer_t<Type>;

    static constexpr std::size_t alignment() { return Alignment; }

    aligned_ptr()                noexcept : pointer_(nullptr) {}
    aligned_ptr(std::nullptr_t)  noexcept : pointer_(nullptr) {}

    aligned_ptr(pointer p) noexcept : pointer_(p) { assert(is_aligned<Alignment>(p)); }

    template< typename U
            , std::size_t A
            , typename = std::enable_if_t<(A>=Alignment)>
            , typename = std::enable_if_t<std::is_convertible_v<U*,Type*>>
            >
    aligned_ptr& operator=(aligned_ptr<U,A> const& p) noexcept
    {
      pointer_ = p.get();
      return *this;
    }

    aligned_ptr& operator=(pointer p) noexcept
    {
      assert(is_aligned<Alignment>(p));
      pointer_ = p;
      return *this;
    }

    aligned_ptr& operator+=(std::ptrdiff_t o) noexcept
    {
      assert(is_aligned<Alignment>(o));
      pointer_ +=o;
      return *this;
    }

    aligned_ptr& operator-=(std::ptrdiff_t o) noexcept
    {
      assert(is_aligned<Alignment>(o));
      pointer_ -=o;
      return *this;
    }

    aligned_ptr& operator++() noexcept
    {
      static_assert(Alignment==1, "[eve] Pointer of non-unit alignment can't be incremented");
      pointer_++;
      return *this;
    }

    aligned_ptr operator++(int) noexcept
    {
      static_assert(Alignment==1, "[eve] Pointer of non-unit alignment can't be incremented");
      aligned_ptr tmp(*this);
      this->operator++();
      return tmp;
    }

    aligned_ptr& operator--() noexcept
    {
      static_assert(Alignment==1, "[eve] Pointer of non-unit alignment can't be decremented");
      pointer_--;
      return *this;
    }

    aligned_ptr operator--(int) noexcept
    {
      static_assert(Alignment==1, "[eve] Pointer of non-unit alignment can't be decremented");
      aligned_ptr tmp(*this);
      this->operator--();
      return tmp;
    }

    explicit operator bool() const noexcept { return pointer_ != nullptr; }

    pointer get() const  noexcept { return pointer_; }

    decltype(auto) operator[](std::size_t i) const  noexcept  { return pointer_[i]; }
    decltype(auto) operator[](std::size_t i)        noexcept  { return pointer_[i]; }

    decltype(auto) operator*() const  noexcept  { return *pointer_; }
    decltype(auto) operator*()        noexcept  { return *pointer_; }

    decltype(auto) operator->() const  noexcept  { return pointer_; }
    decltype(auto) operator->()        noexcept  { return pointer_; }

    void swap(aligned_ptr& that) noexcept { std::swap(pointer_,that.pointer_); }

    private:
    pointer pointer_;
  };

  template<typename Type, std::size_t Alignment>
  void swap(aligned_ptr<Type,Alignment>& lhs,aligned_ptr<Type,Alignment>& rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<std::size_t Alignment, typename Type>
  aligned_ptr<Type,Alignment> as_aligned(Type* ptr) noexcept
  {
    return {ptr};
  }

  template<typename Type> aligned_ptr<Type> as_aligned(Type* ptr) noexcept
  {
    return {ptr};
  }

  template<std::size_t A,typename T,std::size_t B>
  constexpr bool is_aligned(aligned_ptr<T,B> const& ptr) noexcept
  {
    if constexpr(A <= B)
      return true;
    else
      return is_aligned(ptr.get());
  }
}

#endif
