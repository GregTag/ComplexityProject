#include <gtest/gtest.h>

#include <filesystem>
#include <optional>

#include "graph_reader.hpp"
#include "tests/checks/united_check.hpp"

class CommonReadGraph : public testing::TestWithParam<int> {
   protected:
    virtual GraphReader& GetReader() = 0;

    void SetUp() override {
        graph.emplace(GetReader().ReadGraph());
    }

    std::optional<EdgeList> graph;
};

#define CREATE_READER_TEST(name, path, count)       \
    class name : public CommonReadGraph {           \
        GraphReader& GetReader() override {         \
            return reader;                          \
        }                                           \
        static GraphReader reader;                  \
    };                                              \
    GraphReader name::reader{DATA_PREFIX "/" path}; \
    TEST_P(name, Check) {                           \
        UnitedCheck(*graph);                        \
    }                                               \
    INSTANTIATE_TEST_SUITE_P(ReaderTests, name, ::testing::Range(0, count));

CREATE_READER_TEST(AllSize6, "graph6c.g6", 112);
CREATE_READER_TEST(AllSize7, "graph7c.g6", 853);
CREATE_READER_TEST(AllSize8, "graph8c.g6", 11117);
CREATE_READER_TEST(AllSize9, "graph9c.g6", 261080);

CREATE_READER_TEST(AllEdges8, "ge8c.g6", 227);
CREATE_READER_TEST(AllEdges9, "ge9c.g6", 710);
CREATE_READER_TEST(AllEdges10, "ge10c.g6", 2322);
CREATE_READER_TEST(AllEdges11, "ge11c.g6", 8071);
CREATE_READER_TEST(AllEdges12, "ge12c.g6", 29503);
CREATE_READER_TEST(AllEdges13, "ge13c.g6", 112822);
CREATE_READER_TEST(AllEdges14, "ge14c.g6", 450141);
CREATE_READER_TEST(AllEdges15, "ge15c.g6", 1867871);
