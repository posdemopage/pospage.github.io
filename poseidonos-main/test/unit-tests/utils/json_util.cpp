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

#include <vector>

#include "src/helper/json/json_helper.h"
#include "src/volume/volume.h"
#include "test/unit-tests/utils/test_util.h"

namespace pos
{
std::string
VolumeListToString(std::vector<pos::Volume*> volumes)
{
    // refer to VolumeMetaIntf::SaveVolumes() for the full details. possible candidate for refactoring
    JsonElement root("");
    JsonArray jsonArray("volumes");
    for (auto& v : volumes)
    {
        JsonElement elem("");
        elem.SetAttribute(JsonAttribute("name", "\"" + v->GetName() + "\""));
        elem.SetAttribute(JsonAttribute("id", std::to_string(v->ID)));
        elem.SetAttribute(JsonAttribute("total", std::to_string(v->TotalSize())));
        elem.SetAttribute(JsonAttribute("maxiops", std::to_string(v->MaxIOPS())));
        elem.SetAttribute(JsonAttribute("maxbw", std::to_string(v->MaxBW())));
        jsonArray.AddElement(elem);
    }
    root.SetArray(jsonArray);
    return root.ToJson();
}

}  // namespace pos
