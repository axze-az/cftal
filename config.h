#if !defined (__CFTAL_CONFIG_H__)
#define __CFTAL_CONFIG_H__ 1

#if defined (__GNUC__)
#define thread_local __thread
#define likely(a) __builtin_expect(!!(a), 1)
#define unlikely(a) __builtin_expect(!!(a), 0)
#endif

#if defined (_MSC_VER)
#define thread_local __declspec(thread)
#endif

#if !defined (likely)
#define likely(a) a
#endif
#if !defined (unlikely)
#define unlikely(a) a
#endif


// Local variables:
// mode: c++
// end:
#endif
