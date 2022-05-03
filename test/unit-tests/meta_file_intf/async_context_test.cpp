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

#include "src/meta_file_intf/async_context.h"

#include <gtest/gtest.h>

namespace pos
{
int TestHandler(void* data)
{
    std::cout << "TestHandler" << std::endl;
    return 1;
}

void TestCallback(AsyncMetaFileIoCtx* ctx)
{
    std::cout << "TestCallback" << std::endl;
}

TEST(AsyncMetaFileIoCtx, HandleIoComplete_NoDeathEvenIfCallbackIsNullptr)
{
    AsyncMetaFileIoCtx ctx;
    ctx.ioDoneCheckCallback = TestHandler;
    ctx.callback = nullptr;

    EXPECT_NO_FATAL_FAILURE(ctx.HandleIoComplete(nullptr));
    EXPECT_EQ(ctx.error, 1);
}

TEST(AsyncMetaFileIoCtx, HandleIoComplete_NoDeathEvenIfDonecallbackIsNullptr)
{
    AsyncMetaFileIoCtx ctx;
    ctx.ioDoneCheckCallback = nullptr;
    ctx.callback = TestCallback;

    EXPECT_NO_FATAL_FAILURE(ctx.HandleIoComplete(nullptr));
}

TEST(AsyncMetaFileIoCtx, HandleIoComplete_NoDeathEvenIfCallbacksAreNullptr)
{
    AsyncMetaFileIoCtx ctx;
    ctx.ioDoneCheckCallback = nullptr;
    ctx.callback = nullptr;

    EXPECT_NO_FATAL_FAILURE(ctx.HandleIoComplete(nullptr));
}

TEST(AsyncMetaFileIoCtx, GetError_testIfTheMethodCanReturnError)
{
    const int error = 20;
    AsyncMetaFileIoCtx ctx;
    ctx.error = error;

    EXPECT_EQ(ctx.GetError(), error);
}

TEST(AsyncMetaFileIoCtx, GetLength_testIfTheMethodCanReturnTheLength)
{
    const uint64_t length = 20;
    AsyncMetaFileIoCtx ctx;
    ctx.length = length;

    EXPECT_EQ(ctx.GetLength(), length);
}

TEST(AsyncMetaFileIoCtx, SetTopPriority_testIfTheMethodCanSetTopPriority)
{
    AsyncMetaFileIoCtx ctx;
    ctx.SetTopPriority();

    EXPECT_EQ(ctx.priority, RequestPriority::Highest);
}

TEST(AsyncMetaFileIoCtx, ClearTopPriority_testIfTheMethodCanClearTopPriority)
{
    AsyncMetaFileIoCtx ctx;
    ctx.SetTopPriority();
    ctx.ClearTopPriority();

    EXPECT_EQ(ctx.priority, RequestPriority::Normal);
}

TEST(AsyncMetaFileIoCtx, IsTopPriority_testIfTheMethodCanCheckWheatherTheContextIsTopPriority)
{
    AsyncMetaFileIoCtx ctx;
    ctx.SetTopPriority();

    EXPECT_TRUE(ctx.IsTopPriority());
}

TEST(AsyncMetaFileIoCtx, SetPriority_testIfTheMethodCanSetPriority)
{
    AsyncMetaFileIoCtx ctx;

    ctx.SetPriority(RequestPriority::Highest);
    EXPECT_EQ(ctx.GetPriority(), RequestPriority::Highest);

    ctx.SetPriority(RequestPriority::Normal);
    EXPECT_EQ(ctx.GetPriority(), RequestPriority::Normal);
}
} // namespace pos
