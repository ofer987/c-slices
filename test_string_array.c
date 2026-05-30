#include "string_array.h"
#include "vendor/unity/unity.h"

#include <stddef.h>
#include <string.h>

void
setUp(void) {}

void
tearDown(void) {}

void
test_make_string_array_sets_capacity(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  TEST_ASSERT_EQUAL_size_t(20, s->capacity);
  free_string_array(s);
}

void
test_make_string_array_sets_length(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  TEST_ASSERT_EQUAL_size_t(5, s->length);
  free_string_array(s);
}

void
test_make_string_array_sets_value(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  TEST_ASSERT_EQUAL_STRING("hello", s->value);
  free_string_array(s);
}

void
test_make_string_array_null_value(void) {
  struct ArraySlice* s = make_string_array(NULL, 20);
  TEST_ASSERT_EQUAL_size_t(0, s->length);
  TEST_ASSERT_TRUE(s->is_empty);
  free_string_array(s);
}

void
test_make_string_array_zero_capacity_returns_null(void) {
  struct ArraySlice* s = make_string_array("hello", 0);
  TEST_ASSERT_NULL(s);
}

void
test_my_strlen_empty_string(void) {
  TEST_ASSERT_EQUAL_size_t(0, my_strlen(""));
}

void
test_my_strlen_matches_strlen(void) {
  const char* s = "hello world";
  TEST_ASSERT_EQUAL_size_t(strlen(s), my_strlen((char*)s));
}

void
test_append_string_array_updates_value(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  s = append_string_array(s, " world");
  TEST_ASSERT_EQUAL_STRING("hello world", s->value);
  free_string_array(s);
}

void
test_append_string_array_updates_length(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  s = append_string_array(s, " world");
  TEST_ASSERT_EQUAL_size_t(11, s->length);
  free_string_array(s);
}

void
test_append_string_array_grows_capacity(void) {
  struct ArraySlice* s = make_string_array("hello", 6);
  s = append_string_array(s, " world");
  TEST_ASSERT_EQUAL_STRING("hello world", s->value);
  TEST_ASSERT_EQUAL_size_t(11, s->length);
  free_string_array(s);
}

void
test_append_string_array_multiple(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  s = append_string_array(s, " ");
  s = append_string_array(s, "world");
  TEST_ASSERT_EQUAL_STRING("hello world", s->value);
  free_string_array(s);
}

void
test_add_capacity_increases_capacity(void) {
  struct ArraySlice* s = make_string_array("hello", 10);
  s = add_capacity(s, 20);
  TEST_ASSERT_EQUAL_size_t(20, s->capacity);
  free_string_array(s);
}

void
test_add_capacity_preserves_value(void) {
  struct ArraySlice* s = make_string_array("hello", 10);
  s = add_capacity(s, 20);
  TEST_ASSERT_EQUAL_STRING("hello", s->value);
  free_string_array(s);
}

void
test_add_capacity_smaller_returns_null(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct ArraySlice* result = add_capacity(s, 10);
  TEST_ASSERT_NULL(result);
  free_string_array(s);
}

int
main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_make_string_array_sets_capacity);
  RUN_TEST(test_make_string_array_sets_length);
  RUN_TEST(test_make_string_array_sets_value);
  RUN_TEST(test_make_string_array_null_value);
  RUN_TEST(test_make_string_array_zero_capacity_returns_null);

  RUN_TEST(test_my_strlen_empty_string);
  RUN_TEST(test_my_strlen_matches_strlen);

  RUN_TEST(test_append_string_array_updates_value);
  RUN_TEST(test_append_string_array_updates_length);
  RUN_TEST(test_append_string_array_grows_capacity);
  RUN_TEST(test_append_string_array_multiple);

  RUN_TEST(test_add_capacity_increases_capacity);
  RUN_TEST(test_add_capacity_preserves_value);
  RUN_TEST(test_add_capacity_smaller_returns_null);

  return UNITY_END();
}
