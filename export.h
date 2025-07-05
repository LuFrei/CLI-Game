#ifdef LIBCLR_EXPORTS
#define LIBCLR_API __declspec(dllexport)
#else
#define LIBCLR_API __declspec(dllimport)
#endif