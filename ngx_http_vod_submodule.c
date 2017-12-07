#include "ngx_http_vod_dash.h"
#include "ngx_http_vod_hds.h"
#include "ngx_http_vod_hls.h"
#include "ngx_http_vod_mss.h"

#if (NGX_HAVE_LIB_AV_CODEC)
#include "ngx_http_vod_thumb.h"
#include "ngx_http_vod_volume_map.h"
<<<<<<< HEAD
#include "ngx_http_vod_transcode.h"
=======
#endif // NGX_HAVE_LIB_AV_CODEC
>>>>>>> adf50e05a7f2a2b5b14072c7e8f7b20685dddbca

const ngx_http_vod_submodule_t* submodules[] = {
	&dash,
	&hds,
	&hls,
	&mss,
#if (NGX_HAVE_LIB_AV_CODEC)
	&thumb,
	&volume_map,
  &transcode,
#endif // (NGX_HAVE_LIB_AV_CODEC)
	NULL,
};
