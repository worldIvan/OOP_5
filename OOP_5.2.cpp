#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Tax {
private:
	double salary; // Нарахована зарплата

public:
	Tax(double s) : salary(s) {}

	double calculateESV() const { // Єдиний соціальний внесок (6.1%)
		return (salary * 6.1) / 100;
	}

	double calculateIncomeTax() const { // ПДФО (15%)
		double esv = calculateESV();
		double taxableIncome = salary - esv;
		return (taxableIncome * 15) / 100;
	}

	double totalDeductions() const { // Загальні утримання (ЄСВ + ПДФО)
		return calculateESV() + calculateIncomeTax();
	}

	double salaryAfterTaxes() const { // Зарплата після податків
		return salary - totalDeductions();
	}
};

class Teacher {
protected:
	string lastName, firstName, middleName;
	int departmentNumber, hireYear;
	double baseSalary;

public:
	Teacher(const string& ln, const string& fn, const string& mn, int dep, int year, double salary)
		: lastName(ln), firstName(fn), middleName(mn), departmentNumber(dep), hireYear(year), baseSalary(salary) {}

	virtual double calculateSeniorityBonus(int currentYear) const { // Надбавка за вислугу років
		int experience = currentYear - hireYear;
		if (experience > 20) return baseSalary * 0.30;
		if (experience > 10) return baseSalary * 0.20;
		if (experience > 3) return baseSalary * 0.10;
		return 0.0;
	}

	virtual double calculateTotalSalary(int currentYear) const { // Загальна зарплата з премією
		return baseSalary + calculateSeniorityBonus(currentYear);
	}

	void printInfo(int currentYear) const {
		cout << "Teacher: " << lastName << " " << firstName << " " << middleName << endl;
		cout << "Department number: " << departmentNumber << ", Acceptance year: " << hireYear << endl;
		cout << "Salary: " << baseSalary << " UAH, Total salary: " << calculateTotalSalary(currentYear) << " UAH" << endl;
	}

	virtual void writeToFile(ofstream& file) const {
		file << lastName << " " << firstName << " " << middleName << " "
			<< departmentNumber << " " << hireYear << " " << baseSalary << endl;
	}

	virtual void readFromFile(ifstream& file) {
		file >> lastName >> firstName >> middleName >> departmentNumber >> hireYear >> baseSalary;
	}

	virtual ~Teacher() {}
};

class AssistProfessor : public Teacher {
private:
	double degreeBonus = 0.15; // Доплата за науковий ступінь
	double titleBonus = 0.25; // Доплата за вчене звання

public:
	AssistProfessor(const string& ln, const string& fn, const string& mn, int dep, int year, double salary)
		: Teacher(ln, fn, mn, dep, year, salary) {}

	double calculateTotalSalary(int currentYear) const override {
		double salary = Teacher::calculateTotalSalary(currentYear);
		return salary + (salary * degreeBonus) + (salary * titleBonus);
	}

	void writeToFile(ofstream& file) const override {
		Teacher::writeToFile(file);
		file << " Docent" << endl;
	}
};

// Функція для тестування
int main() {
	AssistProfessor professor("Ivanenko", "Ivan", "Ivanovich", 2, 2005, 5000.00);
	professor.printInfo(2024);

	Tax tax(professor.calculateTotalSalary(2024));
	cout << fixed << setprecision(2);
	cout << "ESV: " << tax.calculateESV() << " UAH" << endl;
	cout << "PIT: " << tax.calculateIncomeTax() << " UAH" << endl;
	cout << "Withholding: " << tax.totalDeductions() << " UAH" << endl;
	cout << "Salary before issuance: " << tax.salaryAfterTaxes() << " UAH" << endl;

	// Запис в файл
	ofstream outFile("teacher.txt");
	professor.writeToFile(outFile);
	outFile.close();

	// Читати з файлу
	AssistProfessor newProfessor("", "", "", 0, 0, 0);
	ifstream inFile("teacher.txt");
	newProfessor.readFromFile(inFile);
	inFile.close();

	cout << "\nInformation from the file:" << endl;
	newProfessor.printInfo(2024);

	return 0;
}