#include "DailyTaskWindow.h"

DailyTaskWindow::DailyTaskWindow(QWidget* father, Day* day) : QDialog(father), layout(QBoxLayout::TopToBottom, this), list(this), groupBox("Daily Tasks"), lineEdit(this), deleteBtn("Delete daily task", this), addBtn("Add new daily task", this) {
	assert(day != nullptr);
	this->setParent(father);
	this->setLayout(&layout);
	this->day = day;
	this->addTaskstoList();
	this->setWindowTitle(QString::fromStdString(day->getDate()));
	layout.addWidget(&list, 3);
	layout.addWidget(&lineEdit);
	layout.addWidget(&addBtn);
	layout.addWidget(&deleteBtn);

	connect(&this->deleteBtn, SIGNAL(clicked(bool)), this, SLOT(deleteDT()));
	connect(&this->addBtn, SIGNAL(clicked(bool)), this, SLOT(addDT()));
}


void DailyTaskWindow::addDT()
{

	QString newTask = this->lineEdit.text();

	//check if the input is valid
	if (newTask != "" && !day->dailyTaskExists(newTask))
	{
		day->addDailyTask(newTask);
		day->enregistrer();
		list.addItem(newTask);
		list.item(list.count()-1)->setCheckState(Qt::Unchecked);
	}	
}

void DailyTaskWindow::deleteDT()
{
	QListWidgetItem* item = this->list.takeItem(list.currentRow());
	if (item != nullptr) {
		day->deleteDailyTask(item->text());
		day->enregistrer();
	}

}

void DailyTaskWindow::addTaskstoList() {
	for (size_t i = 0; i < this->day->nbDailyTasks(); ++i) {
		DailyTask* task = day->getDailyTask(i);
		list.addItem(task->getName());
		if(task->isDone())
			list.item(i)->setCheckState(Qt::Checked);
		else
			list.item(i)->setCheckState(Qt::Unchecked);
	}
}
