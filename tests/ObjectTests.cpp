#include <gtest/gtest.h>
#include "../src/World/Object.cpp"
#include "ResourceHandling/Types/Common.hpp"

TEST(Suite, ObjectRetainsModelPointer) {
    LoadedModelData model;
    model.handle = 42;
    World::Object obj(&model);
    
    ASSERT_NE(obj.GetModel(), nullptr);
    EXPECT_EQ(obj.GetModel()->handle, 42);
}
