#include "result.h"

namespace biot {

__thread biot_err_t Result::berrno = BIOT_OK;	///< 错误码
__thread char Result::msg[256] = "OK";			///< 短语
__thread Result bresult;

}
