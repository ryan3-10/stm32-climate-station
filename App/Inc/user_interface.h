#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

class UserInterface {
private:
	float displayedHum;
	float displayedTemp;
	bool needsUpdate;

	void displayHome() const;
	bool weatherChanged(float temp, float hum) const;

public:
	UserInterface();
	UserInterface(const UserInterface&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;
	UserInterface(UserInterface&&) = delete;
	UserInterface& operator=(UserInterface&&) = delete;

	void update(float temp, float hum);
};


#endif /* INC_USER_INTERFACE_H_ */
