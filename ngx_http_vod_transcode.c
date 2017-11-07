#include <ngx_http.h>
#include <ngx_md5.h>
#include "ngx_http_vod_submodule.h"

#if (NGX_HAVE_LIB_AV_CODEC)

DEFINE_SUBMODULE(transcode);

#endif // (NGX_HAVE_LIB_AV_CODEC)
