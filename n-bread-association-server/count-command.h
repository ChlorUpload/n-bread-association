#ifndef __H_COUNT_COMMAND__
#define __H_COUNT_COMMAND__

#include "action.h"

/// <summary>
/// Count를 param 만큼 증가시키는 커맨드 액션
/// </summary>
struct CountCommand : Action<void>
{
    int param;

    CountCommand(int param)
        : param{param}
    { }
};

#endif