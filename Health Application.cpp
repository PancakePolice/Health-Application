// https://sites.google.com/site/compendiumofphysicalactivities/Activity-Categories
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double WEIGHT = 0; // in pounds
double HEIGHT = 0; // in inches
double AGE = 0; // in years

enum WeightStatus{UNDERWEIGHT, HEALTHY_WEIGHT, OVERWEIGHT, OBESITY};

const WeightStatus getWeightStatus(double pounds = WEIGHT, double inches = HEIGHT);
const double getBMI(double pounds = WEIGHT, double inches = HEIGHT);
const double getBMR(double pounds = WEIGHT, double inches = HEIGHT, int age = AGE);
const double getIdealWeight(double bmi = 21.7, double inches = HEIGHT);

int main() {
    if (WEIGHT == 0) {
        cout << "Please enter your weight in pounds: ";
        cin >> WEIGHT;
    }
    if (HEIGHT == 0) {
        cout << "Please enter your height in inches: ";
        cin >> HEIGHT;
    }
    if (AGE == 0) {
        cout << "Please enter your age in years: ";
        cin >> AGE;
    }

    cout << "You have a BMI of " << setprecision(3) << getBMI() << " which is ";

    switch (getWeightStatus()) {
    case UNDERWEIGHT:
        cout << "underweight." << endl;
        break;
    case HEALTHY_WEIGHT:
        cout << "healthy." << endl;
        break;
    case OVERWEIGHT:
        cout << "overweight." << endl;
        break;
    case OBESITY:
        cout << "obese." << endl;
        break;
    default:
        cout << "ERROR." << endl;
    }

    cout << "The ideal weight for your height is " << getIdealWeight() << " lbs." << endl;
    cout << "This is a difference of " << abs(WEIGHT - getIdealWeight()) << " lbs." << endl;
    
    switch (getWeightStatus()) {
    case UNDERWEIGHT:
        cout << "You must gain a minimum of "  << getIdealWeight(25) - WEIGHT << " lbs to be at a healthy weight." << endl;
        break;
    case HEALTHY_WEIGHT:
        cout << "Congratulations on being healthy weight!" << endl;
        break;
    case OVERWEIGHT:
        cout << "You must lose a minimum of " << WEIGHT - getIdealWeight(24.9) << " lbs to be at a healthy weight." << endl;
        break;
    case OBESITY:
       cout << "You must lose a minimum of " << WEIGHT - getIdealWeight(29.9) << " lbs to no longer be obese." << endl;
       cout << "You must lose a minimum of " << WEIGHT - getIdealWeight(24.9) << " lbs to be at a healthy weight." << endl;
        break;
    default:
        cout << "ERROR." << endl;
    }

    // Calculate Ideal Calorie Reductions/Gains to Safely Reach Ideal Weight
    cout << "You require " << setprecision(4) << getBMR() << " calories a day to maintain your current weight." << endl;
    cout << "If you consume 1500 calories a day, you will lose " << setprecision(2) << ((getBMR() - 1500) * 7) / 3500 << " lbs a week." << endl;

    system("pause");

    return 0;
}

// https://www.cdc.gov/healthyweight/assessing/bmi/adult_bmi/index.html#InterpretedAdults
const WeightStatus getWeightStatus(double pounds, double inches) {
    double bmi = getBMI(pounds, inches);
    if (bmi < 18.5)
        return UNDERWEIGHT;
    if (bmi >= 18.5 && bmi <= 24.9)
        return HEALTHY_WEIGHT;
    if (bmi >= 25 && bmi <= 29.9)
        return OVERWEIGHT;
    if (bmi > 30)
        return OBESITY;
}

// https://www.cdc.gov/healthyweight/assessing/bmi/adult_bmi/index.html#Interpreted
const double getBMI(double pounds, double inches) {
    return pounds / pow(inches, 2) * 703;
}

// The Mifflin-St Jeor Equation
const double getBMR(double pounds, double inches, int age) {
    double activityLevel = 1.2; // minimal activity (office job)
    return ((10 * (WEIGHT / 2.205)) + (6.25 * (HEIGHT * 2.54)) - (5 * AGE) + 5) * activityLevel;
}

const double getIdealWeight(double bmi, double inches) {
    return bmi * pow(inches, 2) / 703;
}