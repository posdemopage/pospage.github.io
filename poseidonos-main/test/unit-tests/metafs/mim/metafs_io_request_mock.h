#include <gmock/gmock.h>

#include <list>
#include <string>
#include <vector>

#include "src/metafs/mim/metafs_io_request.h"

namespace pos
{
class MockMetaFsIoRequest : public MetaFsIoRequest
{
public:
    using MetaFsIoRequest::MetaFsIoRequest;
    MOCK_METHOD(void, CopyUserReqMsg, (const MetaFsIoRequest& req), (override));
    MOCK_METHOD(bool, IsValid, (), (override));
    MOCK_METHOD(bool, IsSyncIO, (), (override));
    MOCK_METHOD(bool, IsIoCompleted, (), (override));
    MOCK_METHOD(bool, GetError, (), (override));
    MOCK_METHOD(void, SuspendUntilIoCompletion, (), (override));
    MOCK_METHOD(void, NotifyIoCompletionToClient, (), (override));
    MOCK_METHOD(void, SetError, (bool err), (override));
    MOCK_METHOD(void, SetRetryFlag, (), (override));
    MOCK_METHOD(bool, GetRetryFlag, (), (override));
};

} // namespace pos
