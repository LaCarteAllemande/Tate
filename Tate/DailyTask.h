#pragma once
#include <qstring.h>

//Represents a daily task
class DailyTask {
private :
	QString NAME;
	bool done;

public :
	DailyTask(QString NAME, bool done);
	QString getName();
	bool isDone();

	/**
	Set if the task is done or not
	@param The boolean value representing if the task is done or not
	*/
	void isDone(bool done);
};
