#pragma once

//global constants used in various places in project

//time computation unit
using timeunit_t = double;
//simple typedef of timer used in all benchmarks
using Timer = x::timer<std::chrono::microseconds, timeunit_t>;

//name of the settings filename containing saved application state
constexpr char const SETTINGS_FILENAME[] = "settings.ini";
//formatting html code for results highlighting
constexpr char const HIGHLIGHTED_TEXT_STYLE_HEADER_1[] = "<font color=\"#F7DC6F\">";
constexpr char const HIGHLIGHTED_TEXT_STYLE_HEADER_2[] = "<font color=\"#FFC114\">";
constexpr char const* HIGHLIGHTED_TEXT_STYLE_HEADER[2] = {HIGHLIGHTED_TEXT_STYLE_HEADER_1, HIGHLIGHTED_TEXT_STYLE_HEADER_2};
constexpr char const HIGHLIGHTED_TEXT_STYLE_FOOTER[] = "</font>";
//default size of buffer preallocated per single regex search result
constexpr size_t SEARCH_RESULT_INFO_PREALLOC_SIZE = 100;
//size of data allocated per single result highlighting
constexpr size_t HIGHLIGHTER_BUFFER_INPUT_SIZE_MULT = sizeof(HIGHLIGHTED_TEXT_STYLE_HEADER_1) + sizeof(HIGHLIGHTED_TEXT_STYLE_FOOTER);
constexpr size_t HIGHLIGHTER_BUFFER_MIN_SIZE = 1024;