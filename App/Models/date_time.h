#ifndef MODELS_DATE_TIME_H_
#define MODELS_DATE_TIME_H_

#include <stdint.h>

class DateTime {
public:
	struct Model {
		uint8_t second = 0;
		uint8_t minute = 0;
		uint8_t hour = 0;
		uint8_t day = 1;
		uint8_t date = 1;
		uint8_t month = 1;
		uint8_t year = 0;
	};

	DateTime() = default;
	DateTime(Model m) : dat(m) {}
	const Model& getData() const { return dat; }
	void setData(const Model& model) { dat = model; }
	uint32_t toEpochSeconds() const;
	DateTime fromEpochSeconds(uint32_t seconds);
	bool operator==(const DateTime& other) const;
	bool operator>(const DateTime& oth) const;
	bool operator<(const DateTime& oth) const;
	bool operator>=(const DateTime& oth) const { return *this > oth || *this == oth; }
	bool operator<=(const DateTime& oth) const { return *this < oth || *this == oth; }
	bool operator!=(const DateTime& oth) const { return !(*this == oth); }
	static bool isValidModel(const Model& m);
	DateTime operator+(uint32_t seconds);

private:
	bool isLeapYear(uint8_t year) const { return year % 4 == 0; }
	uint8_t daysInMonth(uint8_t month, uint8_t year) const;
	Model dat;
};

#endif /* MODELS_DATE_TIME_H_ */

