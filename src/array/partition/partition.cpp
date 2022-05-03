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

#include "partition.h"

#include "src/include/array_config.h"
#include "../device/array_device.h"
#include "src/logger/logger.h"
#include "src/include/pos_event_id.h"

namespace pos
{
Partition::Partition(vector<ArrayDevice*> d, PartitionType type)
: devs(d),
  type(type)
{
}

// LCOV_EXCL_START
Partition::~Partition(void)
{
}
// LCOV_EXCL_STOP

int
Partition::FindDevice(ArrayDevice* target)
{
    int i = 0;
    for (ArrayDevice* dev : devs)
    {
        if (dev == target)
        {
            return i;
        }
        i++;
    }

    return -1;
}

const PartitionLogicalSize*
Partition::GetLogicalSize(void)
{
    return &logicalSize;
}

const PartitionPhysicalSize*
Partition::GetPhysicalSize(void)
{
    return &physicalSize;
}

bool
Partition::IsValidLba(uint64_t lba)
{
    if (physicalSize.startLba > lba || lastLba <= lba)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool
Partition::_IsValidAddress(const LogicalBlkAddr& lsa)
{
    if (lsa.stripeId < logicalSize.totalStripes && lsa.offset < logicalSize.blksPerStripe)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool
Partition::_IsValidEntry(const LogicalWriteEntry& entry)
{
    if (entry.addr.stripeId < logicalSize.totalStripes &&
        entry.addr.offset + entry.blkCnt <= logicalSize.blksPerStripe &&
        entry.blkCnt >= logicalSize.minWriteBlkCnt)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void
Partition::_UpdateLastLba(void)
{
    lastLba = physicalSize.startLba +
        static_cast<uint64_t>(ArrayConfig::SECTORS_PER_BLOCK) *
        physicalSize.blksPerChunk * physicalSize.stripesPerSegment *
        physicalSize.totalSegments;

    POS_TRACE_DEBUG(EID(ARRAY_DEBUG_MSG), "Partition::_UpdateLastLba, lastLba:{}", lastLba);
}

} // namespace pos
