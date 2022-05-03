/*
*   BSD LICENSE
*   Copyright (c) 2021 Samsung Electronics Corporation
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided with the
*       distribution.
*     * Neither the name of Samsung Electronics Corporation nor the names of
 *       its contributors may be used to endorse or promote products derived
*       from this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <functional>

#include "src/include/smart_ptr_type.h"

namespace pos
{
class LogWriteHandler;
class LogWriteContext;
class EventScheduler;

using GcStripeLogWriteCallback = std::function<int(LogWriteContext*)>;

// TODO (huijeong.kim) : move to class to general folder to be used at everywhere in journal
class JournalEventFactory
{
public:
    JournalEventFactory(void) = default;
    virtual ~JournalEventFactory(void) = default;

    virtual void Init(EventScheduler* scheduler, LogWriteHandler* logWriteHandler);

    virtual EventSmartPtr CreateGcLogWriteCompletedEvent(EventSmartPtr callback);
    virtual EventSmartPtr CreateGcStripeLogWriteRequestEvent(LogWriteContext* callbackContext);

private:
    EventScheduler* eventScheduler = nullptr;
    GcStripeLogWriteCallback gcCallbackFunc;
};

} // namespace pos
