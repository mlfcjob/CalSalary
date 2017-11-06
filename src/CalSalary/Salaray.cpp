#include "Salaray.h"

class XSalary :public Salary {

public:

	float CalFinalSalay() {
		return this->preTax - this->CalInsuracyDeduction() - this->CalProvidentFundDection();
	}

	float CalInsuracyDeduction() {
		return this->socialInsurancyBase * this->socialInsurancyRate + 3;
	}

	float CalProvidentFundDection() {
		return this->providentFundBase * this->providentFundBaseRate;
	}

	void InitSalary(float preTax, float socialBase, float socialRate, float fundBase, float fundRate) {
		this->preTax = preTax;
		this->socialInsurancyBase = socialBase;
		this->socialInsurancyRate = socialRate;
		this->providentFundBase = fundBase;
		this->providentFundBaseRate = fundRate;
	}

private:
	
};


Salary::Salary()
{
}


Salary::~Salary()
{
}

Salary* Salary::Get() {
	static XSalary sal;
	return &sal;
}