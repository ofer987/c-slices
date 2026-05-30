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
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));
  free_string_array(s);
}

void
test_make_string_array_sets_length(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  TEST_ASSERT_EQUAL_size_t(5, get_length(s));
  free_string_array(s);
}

void
test_make_string_array_sets_value(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  TEST_ASSERT_EQUAL_STRING("hello", get_value(s));
  free_string_array(s);
}

void
test_make_string_array_null_value(void) {
  struct ArraySlice* s = make_string_array(NULL, 20);
  TEST_ASSERT_EQUAL_size_t(0, get_length(s));
  TEST_ASSERT_TRUE(is_empty(s));
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
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));
  free_string_array(s);
}

void
test_append_string_array_updates_length(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  s = append_string_array(s, " world");
  TEST_ASSERT_EQUAL_size_t(11, get_length(s));
  free_string_array(s);
}

void
test_append_string_array_grows_capacity(void) {
  struct ArraySlice* s = make_string_array("hello", 6);
  s = append_string_array(s, " world");
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));
  TEST_ASSERT_EQUAL_size_t(11, get_length(s));
  free_string_array(s);
}

void
test_append_string_array_multiple(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  s = append_string_array(s, " ");
  s = append_string_array(s, "world");
  TEST_ASSERT_EQUAL_STRING("hello world", get_value(s));
  free_string_array(s);
}

void
test_add_capacity_increases_capacity(void) {
  struct ArraySlice* s = make_string_array("hello", 10);
  s = add_capacity(s, 20);
  TEST_ASSERT_EQUAL_size_t(20, get_capacity(s));
  free_string_array(s);
}

void
test_add_capacity_preserves_value(void) {
  struct ArraySlice* s = make_string_array("hello", 10);
  s = add_capacity(s, 20);
  TEST_ASSERT_EQUAL_STRING("hello", get_value(s));
  free_string_array(s);
}

void
test_add_capacity_smaller_returns_null(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct ArraySlice* result = add_capacity(s, 10);
  TEST_ASSERT_NULL(result);
  free_string_array(s);
}

void
test_copy_into_array_slice_success_is_success(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct Result* r = copy_into_array_slice(0, "world", s);
  TEST_ASSERT_TRUE(is_success(r));
  free_result(r);
  free_string_array(s);
}

void
test_copy_into_array_slice_success_returns_destination(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct Result* r = copy_into_array_slice(0, "world", s);
  TEST_ASSERT_EQUAL_PTR(s, get_array_slice(r));
  free_result(r);
  free_string_array(s);
}

void
test_copy_into_array_slice_success_no_error_message(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct Result* r = copy_into_array_slice(0, "world", s);
  TEST_ASSERT_NULL(get_error_message(r));
  free_result(r);
  free_string_array(s);
}

void
test_copy_into_array_slice_null_value_is_success(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct Result* r = copy_into_array_slice(0, NULL, s);
  TEST_ASSERT_TRUE(is_success(r));
  free_result(r);
  free_string_array(s);
}

void
test_copy_into_array_slice_null_value_returns_destination(void) {
  struct ArraySlice* s = make_string_array("hello", 20);
  struct Result* r = copy_into_array_slice(0, NULL, s);
  TEST_ASSERT_EQUAL_PTR(s, get_array_slice(r));
  free_result(r);
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

  RUN_TEST(test_copy_into_array_slice_success_is_success);
  RUN_TEST(test_copy_into_array_slice_success_returns_destination);
  RUN_TEST(test_copy_into_array_slice_success_no_error_message);
  RUN_TEST(test_copy_into_array_slice_null_value_is_success);
  RUN_TEST(test_copy_into_array_slice_null_value_returns_destination);

  return UNITY_END();
}
