#ifndef __H_COUNT_COMMAND__
#define __H_COUNT_COMMAND__

#include "action.h"

/// <summary>
/// Count�� param ��ŭ ������Ű�� Ŀ�ǵ� �׼�
/// </summary>
struct CountCommand : Action<void>
{
    int param;

    CountCommand(int param)
        : param{param}
    { }
};

#endif