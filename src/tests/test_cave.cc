#include <gtest/gtest.h>

#include "../cave.h"
#include "../model.h"
#include "../parser.h"

using namespace s21;

TEST(ParseCave, Cave_1) {
  Cave example;
  Parser parser;
  parser.ParseCave("data/cave_example_1.txt", &example);
  Matrix answer = Matrix(
      10, 10, {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
               0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
               0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
               1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
               1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0});

  ASSERT_EQ(example.GetRows(), 10);
  ASSERT_EQ(example.GetCols(), 10);
  ASSERT_TRUE(example.GetCave() == answer);
}

TEST(NextCave, Cave_2) {
  Cave example;
  Parser parser;
  parser.ParseCave("data/cave_example_1.txt", &example);
  example.SetBornLimit(4);
  example.SetDeathLimit(3);
  example.Next();
  Matrix answer = Matrix(
      10, 10, {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
               0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
               1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
               1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
               1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1});

  ASSERT_EQ(example.GetRows(), 10);
  ASSERT_EQ(example.GetCols(), 10);
  ASSERT_TRUE(example.GetCave() == answer);
}

TEST(NextCave, Cave_3) {
  Cave example;
  Matrix past;
  Parser parser;
  parser.ParseCave("data/cave_example_1.txt", &example);
  example.SetBornLimit(4);
  example.SetDeathLimit(3);

  for (int i = 0; !(past == example.GetCave()); ++i) {
    past = example.GetPastCave();
    example.Next();
  }

  Matrix answer = Matrix(
      10, 10, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
               1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
               1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});

  ASSERT_EQ(example.GetRows(), 10);
  ASSERT_EQ(example.GetCols(), 10);
  ASSERT_TRUE(example.GetCave() == answer);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}