#pragma once

#include <QtWidgets/QWidget>
#include "ui_CalSalary.h"

class CalSalary : public QWidget
{
	Q_OBJECT

public:
	CalSalary(QWidget *parent = Q_NULLPTR);
	void SetValidator();

private:
	Ui::CalSalaryClass ui;

public slots:
	void StartCalSalary();
};
