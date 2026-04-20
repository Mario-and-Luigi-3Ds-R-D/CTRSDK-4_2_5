#pragma once

#include "nn/types.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn{
namespace os{
    class ITask{
    public:
    };

    class ITaskInvoker{
    public:
    };

    class IWaitTaskInvoker : public nn::os::ITaskInvoker{
    public:
    };

    class QueueableTask : public nn::os::ITask, public nn::fnd::IntrusiveQueue::Item{
    public:
    };
}
}