#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#include <sysinfoapi.h>
#include <timezoneapi.h>

#include <chrono>
#include <string>

namespace receiver {
enum date_format { ISO_8601 };

class time_zone {
 public:
  using value_type = long;


  time_zone();

  time_zone(value_type offset);

  time_zone(const std::string& timezone);

  static time_zone current();

  value_type offset() const noexcept { return native_; }

 private:
  value_type native_;
};

class date_time {
 public:
  using value_type = long long;

  date_time();

  date_time(const std::string& datetime,
            date_format standard = date_format::ISO_8601,
            const time_zone& zone = {});

  date_time(value_type timestamp, const time_zone& zone = {});

  date_time& set_time_zone(const time_zone& timezone);

  date_time& operator+=(value_type seconds);
  date_time& operator-=(value_type seconds);
  date_time& operator+=(const std::chrono::seconds& seconds);
  date_time& operator-=(const std::chrono::seconds& seconds);
  const date_time operator+(value_type seconds) const;
  const date_time operator-(value_type seconds) const;
  const date_time operator+(const std::chrono::seconds& seconds) const;
  const date_time operator-(const std::chrono::seconds& seconds) const;
  date_time& operator=(value_type timestamp);

  std::string format(date_format standard = date_format::ISO_8601,
                     bool consider_zone = true);

  static date_time current();

  value_type timestamp(bool consider_zone = true) const;

 private:
  static constexpr std::uint64_t UNIX_TIME_START{0x019DB1DED53E8000};
  static constexpr std::uint64_t TICKS_PER_SECOND{10000000};

  static auto file_time_to_timestamp(const FILETIME& file_time) -> value_type;
  static auto timestamp_to_file_time(value_type timestamp) -> FILETIME;

 private:
  value_type native_;
  time_zone zone_;
};
} r
