#include "DailyTask.h"

DailyTask::DailyTask(QString NAME, bool done)
{
	this->NAME = NAME;
	this->done = done;
}

QString DailyTask::getName() {
	return this->NAME;
}

bool DailyTask::isDone() {
	return this->done;
}

void DailyTask::isDone(bool v) {
	this->done = v;
}