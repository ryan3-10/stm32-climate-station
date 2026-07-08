#include <array>
#include <date_time.h>
#include <stdint.h>

namespace {
	constexpr DateTime::Model EPOCH{0, 0, 0, 6, 1, 1, 0};
}

bool DateTime::operator==(const DateTime& other) const {
	auto& oth = other.dat;

	return dat.second == oth.second
		&& dat.minute == oth.minute
		&& dat.hour == oth.hour
		&& dat.month == oth.month
		&& dat.year == oth.year;
}

bool DateTime::operator>(const DateTime& other) const {
	auto& oth = other.dat;

	if (dat.year != oth.year) return dat.year > oth.year;
	if (dat.month != oth.month) return dat.month > oth.month;
	if (dat.date != oth.date) return dat.date > oth.date;
	if (dat.hour != oth.hour) return dat.hour > oth.hour;
	if (dat.minute != oth.minute) return dat.minute > oth.minute;
	return dat.second > oth.second;
}

bool DateTime::operator<(const DateTime& other) const {
	auto& oth = other.dat;

	if (dat.year != oth.year) return dat.year < oth.year;
	if (dat.month != oth.month) return dat.month < oth.month;
	if (dat.date != oth.date) return dat.date < oth.date;
	if (dat.hour != oth.hour) return dat.hour < oth.hour;
	if (dat.minute != oth.minute) return dat.minute < oth.minute;
	return dat.second < oth.second;
}

DateTime DateTime::operator+(uint32_t seconds) {
	return fromEpochSeconds(toEpochSeconds() + seconds);
}

uint8_t DateTime::daysInMonth(uint8_t month, uint8_t year) const {
	if (month == 2 && isLeapYear(year)) {
		return 29;
	}

	constexpr std::array<uint8_t, 12> DAYS_PER_MONTH = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	return DAYS_PER_MONTH[month];
}

uint32_t DateTime::toEpochSeconds() const {
    uint32_t days = 0;

    for (uint8_t year = EPOCH.year; year < dat.year; ++year) {
        days += isLeapYear(year) ? 366 : 365;
    }

    for (uint8_t month = 1; month < dat.month; ++month) {
        days += daysInMonth(month, dat.year);
    }

    days += dat.date - 1;

    return days * 86400UL
         + dat.hour * 3600UL
         + dat.minute * 60UL
         + dat.second;
}

DateTime DateTime::fromEpochSeconds(uint32_t seconds) {
	DateTime result{EPOCH};

	// Break into days + time of day
	uint32_t totalDays = seconds / 86400;
	uint32_t remainingSeconds = seconds % 86400;

	// Set the day of the week
	result.dat.day = ((result.dat.day - 1 + totalDays) % 7) + 1;

	result.dat.hour = remainingSeconds / 3600;
	remainingSeconds %= 3600;

	result.dat.minute = remainingSeconds / 60;
	result.dat.second = remainingSeconds % 60;

	// Find the year
	while (true) {
		uint32_t daysInYear = isLeapYear(result.dat.year) ? 366 : 365;

		if (totalDays < daysInYear)
			break;

		totalDays -= daysInYear;
		result.dat.year++;
	}

	// Find the month
	while (true) {
		uint8_t daysThisMonth = daysInMonth(result.dat.month, result.dat.year);

		if (totalDays < daysThisMonth)
			break;

		totalDays -= daysThisMonth;
		++result.dat.month;
	}

	// Remaining days are day of month
	result.dat.date = totalDays + 1;

	return result;
}

bool DateTime::isValidModel(const Model& m) {
	return m.second < 60
		&& m.minute < 60
		&& m.hour < 24
		&& m.day >= 1 && m.day <=7
		&& m.date >= 1 && m.date <= 31
		&& m.month >= 1 && m.month <= 12;
}





