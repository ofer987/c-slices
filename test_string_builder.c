#include "string_builder.h"
#include "vendor/unity/unity.h"

#include <stddef.h>

void
setUp(void) {}

void
tearDown(void) {}

void
test_make_string_builder_sets_capacity(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));

  free_string_builder(s);
}

void
test_make_string_builder_sets_length(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  TEST_ASSERT_EQUAL_size_t(5, get_length(s));

  free_string_builder(s);
}

void
test_make_string_builder_sets_value(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  TEST_ASSERT_EQUAL_STRING("hello", get_value(s));

  free_string_builder(s);
}

void
test_make_string_builder_null_value(void) {
  struct StringBuilder* s = make_string_builder(NULL, 20);
  TEST_ASSERT_EQUAL_size_t(0, get_length(s));
  TEST_ASSERT_TRUE(is_empty(s));

  free_string_builder(s);
}

void
test_make_string_builder_zero_capacity_returns_null(void) {
  struct StringBuilder* s = make_string_builder("hello", 0);
  TEST_ASSERT_NULL(s);
}

void
test_append_string_builder_does_not_change_capacity(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));

  s = append_string_builder(s, " world");
  s = append_string_builder(s, " 12345678");
  TEST_ASSERT_EQUAL_STRING("hello world 12345678", get_value(s));
  TEST_ASSERT_EQUAL_size_t(20, get_length(s));
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));

  free_string_builder(s);
}

void
test_append_string_builder_changes_capacity(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));

  s = append_string_builder(s, " world");
  s = append_string_builder(s, " 123456789");
  TEST_ASSERT_EQUAL_STRING("hello world 123456789", get_value(s));
  TEST_ASSERT_EQUAL_size_t(21, get_length(s));
  TEST_ASSERT_EQUAL_size_t(42, get_capacity(s));

  free_string_builder(s);
}

void
test_append_string_builder_updates_value(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  s = append_string_builder(s, " world");
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));

  free_string_builder(s);
}

void
test_append_string_builder_updates_length(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  s = append_string_builder(s, " world");
  TEST_ASSERT_EQUAL_size_t(11, get_length(s));

  free_string_builder(s);
}

void
test_append_string_builder_grows_capacity(void) {
  struct StringBuilder* s = make_string_builder("hello", 6);
  s = append_string_builder(s, " world");
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));
  TEST_ASSERT_EQUAL_size_t(11, get_length(s));
  TEST_ASSERT_EQUAL_size_t(22, get_capacity(s));

  free_string_builder(s);
}

void
test_append_string_builder_doubles_capacity_of_length(void) {
  struct StringBuilder* s = make_string_builder("hello", 6);
  s = append_string_builder(s, ", world today");
  TEST_ASSERT_EQUAL_size_t(get_length(s) * 2, get_capacity(s));

  free_string_builder(s);
}

void
test_append_string_builder_grows_capacity_by_a_lot(void) {
  struct StringBuilder* s = make_string_builder("hello", 6);
  s = append_string_builder(s, " my big bold beautiful world");
  TEST_ASSERT_EQUAL_STRING("hello my big bold beautiful world", get_value(s));
  TEST_ASSERT_EQUAL_size_t(33, get_length(s));
  TEST_ASSERT_EQUAL_size_t(66, get_capacity(s));

  free_string_builder(s);
}

void
test_append_string_builder_multiple(void) {
  struct StringBuilder* s = make_string_builder("hello", 20);
  s = append_string_builder(s, " ");
  s = append_string_builder(s, "world");
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));

  free_string_builder(s);
}

int
main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_make_string_builder_sets_capacity);
  RUN_TEST(test_make_string_builder_sets_length);
  RUN_TEST(test_make_string_builder_sets_value);
  RUN_TEST(test_make_string_builder_null_value);
  RUN_TEST(test_make_string_builder_zero_capacity_returns_null);

  RUN_TEST(test_append_string_builder_does_not_change_capacity);
  RUN_TEST(test_append_string_builder_changes_capacity);
  RUN_TEST(test_append_string_builder_updates_value);
  RUN_TEST(test_append_string_builder_updates_length);
  RUN_TEST(test_append_string_builder_grows_capacity);
  RUN_TEST(test_append_string_builder_doubles_capacity_of_length);
  RUN_TEST(test_append_string_builder_grows_capacity_by_a_lot);
  RUN_TEST(test_append_string_builder_multiple);

  return UNITY_END();
}
