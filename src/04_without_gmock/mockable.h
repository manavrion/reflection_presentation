#pragma once
#include <cassert>

#ifdef NDEBUG

#define MOCKABLE

#else

#include "mockable_impl.h"
#define MOCKABLE (mockable)

#endif
