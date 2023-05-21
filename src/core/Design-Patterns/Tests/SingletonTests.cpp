#include <gtest/gtest.h>

#include "Singleton.hpp"

struct ExampleDataStruct
{
  ExampleDataStruct() = default;

  ExampleDataStruct(int value)
  {
    m_data = new int[10];

    for (int i = 0; i < 10; ++i)
    {
      m_data[i] = value;
    }
  }

  ~ExampleDataStruct()
  {
    delete[] m_data;
    m_data = nullptr;
  }

  int *m_data = nullptr;
};

TEST(SingletonTests, SingletonCreate)
{
  using ExampleSingleton = Singleton<ExampleDataStruct>;

  ExampleSingleton::Create(20);

  ExampleDataStruct& data = ExampleSingleton::Instance();

  EXPECT_EQ(data.m_data[0], 20);
}

TEST(SingletonTests, SingletonDestroy)
{
  using ExampleSingleton = Singleton<ExampleDataStruct>;

  ExampleSingleton::Create(20);

  ExampleDataStruct& data = ExampleSingleton::Instance();

  EXPECT_EQ(data.m_data[0], 20);

  ExampleSingleton::Destroy();

  ASSERT_TRUE(data.m_data == nullptr);
}

TEST(SingletonTests, SingletonIsValid)
{
  using ExampleSingleton = Singleton<ExampleDataStruct>;

  EXPECT_EQ(ExampleSingleton::IsValid(), false);

  ExampleSingleton::Create(10);

  EXPECT_EQ(ExampleSingleton::IsValid(), true);

  ExampleSingleton::Destroy();

  EXPECT_EQ(ExampleSingleton::IsValid(), false);
}

TEST(SingletonTests, SingletonIsValidReferences)
{
  using ExampleSingleton = Singleton<ExampleDataStruct>;

  EXPECT_THROW(ExampleSingleton::Instance(), std::runtime_error);

  ExampleSingleton::Create(10);

  EXPECT_NO_THROW(ExampleSingleton::Instance());

  ExampleDataStruct& data = ExampleSingleton::Instance();

  EXPECT_EQ(data.m_data[0], 10);

  ExampleSingleton::Destroy();

  ASSERT_TRUE(data.m_data == nullptr);
  EXPECT_THROW(ExampleSingleton::Instance(), std::runtime_error);
}