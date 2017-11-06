#include "CalSalary.h"
#include <iostream>

#include "Salaray.h"
using namespace std;

CalSalary::CalSalary(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetValidator();

	ui.socialBaseRateIn->setText("0.102");
	ui.fundBaseRateIn->setText("0.12");

}
void CalSalary::SetValidator()
{
	ui.preTaxIn->setValidator(new QIntValidator(0, 1000000, this));
	
	ui.fundBaseIn->setValidator(new QIntValidator(1000, 60000, this));
	//ui.fundBaseRateIn->setValidator(new QIntValidator(0, 1, this));

	ui.socialBaseIn->setValidator(new QIntValidator(1000, 60000, this));
	//ui.socialBaseRateIn->setValidator(new QIntValidator(0, 1, this));
}


void CalSalary::StartCalSalary(){

	Salary::Get()->InitSalary(ui.preTaxIn->text().toFloat(),
		ui.socialBaseIn->text().toFloat(), ui.socialBaseRateIn->text().toFloat(),
		ui.fundBaseIn->text().toFloat(),  ui.fundBaseRateIn->text().toFloat());
	cout << "social cost " << Salary::Get()->CalInsuracyDeduction() << endl;
	cout << "fund cost " << Salary::Get()->CalProvidentFundDection() << endl;

}