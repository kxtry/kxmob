﻿#ifndef _KXAPI_H_
#define _KXAPI_H_


#ifdef KXFW_STATICLIB
# define KXFW_API
#else
#ifdef KXFW_LIB
# define KXFW_API Q_DECL_EXPORT
#else
# define KXFW_API Q_DECL_IMPORT
#endif
#endif



#endif
