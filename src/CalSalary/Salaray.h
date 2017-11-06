#pragma once
class Salary
{
public:
	static Salary *Get();
	
	virtual ~Salary();
	virtual float CalFinalSalay() = 0;
	virtual float CalInsuracyDeduction() = 0;
	virtual float CalProvidentFundDection() = 0;
	virtual void InitSalary(float preTax, float socialBase, float socialRate, float fundBase, float fundRate) = 0;
	
	float  preTax = 0.0;
	float  socialInsurancyBase = 0.0;
	float  providentFundBase = 0.0;
	float  socialInsurancyRate = 0.102;
	float  providentFundBaseRate = 0.12;
	float  socialInsurancyDeduction = 0.0;
	float  providentFundDeduction = 0.0;
protected:
	Salary();
};

