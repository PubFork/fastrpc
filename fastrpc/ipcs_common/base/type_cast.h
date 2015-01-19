
#ifndef IPCS_COMMON_BASE_TYPE_CAST_H
#define IPCS_COMMON_BASE_TYPE_CAST_H

# include <assert.h>
# include <typeinfo>

// ȡ�� glog
// Author: kenton@google.com (Kenton Varda) and others
//
// Contains basic types and utilities used by the rest of the library.

//
// Use implicit_cast as a safe version of static_cast or const_cast
// for upcasting in the type hierarchy (i.e. casting a pointer to Foo
// to a pointer to SuperclassOfFoo or casting a pointer to Foo to
// a const pointer to Foo).
// When you use implicit_cast, the compiler checks that the cast is safe.
// Such explicit implicit_casts are necessary in surprisingly many
// situations where C++ demands an exact type match instead of an
// argument type convertable to a target type.
//
// The From type can be inferred, so the preferred syntax for using
// implicit_cast is the same as for static_cast etc.:
//
//   implicit_cast<ToType>(expr)
//
// implicit_cast would have been part of the C++ standard library,
// but the proposal was submitted too late.  It will probably make
// its way into the language in the future.

/// ִ����ȷ������ת����ͬʱ����ѹ�Ʊ������ľ��档
template<typename To, typename From>
inline To implicit_cast(From const &f) {
    return f;
}

///////////////////////////////////////////////////////////////////////////////
// ����ȡ�� boost/cast.hpp

/// ִ�ж�̬����ת�������ת��ʧ�ܣ�throw �쳣��
template <class Target, class Source>
inline Target polymorphic_cast(Source* x)
{
    if (x == 0)
        return 0;
    Target tmp = dynamic_cast<Target>(x); // NOLINT(runtime/rtti)
    if (tmp == 0)
        throw std::bad_cast();
    return tmp;
}

/// ��̬����ת�ͣ�debug ģʽ��δ���� NDEBUG�����м�飬�����Ч�� static_cast
template <class Target, class Source>
inline Target polymorphic_downcast(Source* x)
{
    assert(dynamic_cast<Target>(x) == x); // NOLINT(runtime/rtti)
    return static_cast<Target>(x);
}

#endif // COMMON_BASE_TYPE_CAST_H
