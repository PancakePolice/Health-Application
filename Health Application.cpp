// https://sites.google.com/site/compendiumofphysicalactivities/Activity-Categories
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

double WEIGHT = 0; // in pounds
double HEIGHT = 0; // in inches
double AGE = 0; // in years

enum WeightStatus{ UNDERWEIGHT, HEALTHY_WEIGHT, OVERWEIGHT, OBESE};
// enum menuStatus { BROWSING, QUIT } menuStatus;

const double getBMI(double pounds = WEIGHT, double inches = HEIGHT);
const double getBMR(double activityFactor = 1.2, double pounds = WEIGHT, double inches = HEIGHT, int age = AGE);
const double getIdealWeight(double inches = HEIGHT);
const int getWeeksUntilIdealWeight(double calorieIntake = 1500, double idealWeight = 0, double weight = WEIGHT);
const WeightStatus getWeightStatus(double pounds = WEIGHT, double inches = HEIGHT);

const string PrintWeightStatus();
const string PrintHealthyWeightRange(double inches = HEIGHT);

static const double lb2kg(double pounds) { return pounds / 2.205; }
static const double kg2lb(double mass) { return mass * 2.205; }
static const double in2cm(double inches) { return inches * 2.54; }

int main() {
    if (!WEIGHT || !HEIGHT || !AGE) {
        if (!WEIGHT) {
            cout << "Please enter your weight in pounds: ";
            cin >> WEIGHT;
        }
        if (!HEIGHT) {
            cout << "Please enter your height in inches: ";
            cin >> HEIGHT;
        }
        if (!AGE) {
            cout << "Please enter your age in years: ";
            cin >> AGE;
        }
        cout << "----------------------------------------" << endl;
    }

    cout << "Body Mass Index: " << setprecision(3) << getBMI() << endl;
    cout << PrintWeightStatus() << endl;
    cout << "Ideal Weight: " << setprecision(3) << getIdealWeight() << " lbs" << endl;
    cout << PrintHealthyWeightRange() << endl;
    cout << "Base Metabolic Rate: " << setprecision(4) << getBMR() << " calories" << endl;

    if (getWeightStatus() == OBESE)
        cout << "\nIf you consumed roughly 1500 calories a day, it would take " << getWeeksUntilIdealWeight(1500, (29.9 * pow(HEIGHT, 2) / 703)) << " weeks to no longer be obese.";
    cout << "\nIf you consumed roughly 1500 calories a day, it would take " << getWeeksUntilIdealWeight() << " weeks to reach ideal weight." << endl;

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
        return OBESE;
}

// https://www.cdc.gov/nccdphp/dnpao/growthcharts/training/bmiage/page5_2.html
const double getBMI(double pounds, double inches) {
    return pounds / pow(inches, 2) * 703;
}

// The Mifflin-St Jeor Equation
const double getBMR(double activityFactor, double pounds, double inches, int age) {
    return ((10 * lb2kg(WEIGHT)) + (6.25 * in2cm(HEIGHT)) - (5 * AGE) + 5) * activityFactor;
}

// The J. D. Robinson Formula
const double getIdealWeight(double inches) {
    double idealWeight = 52; // in kilograms
    for (int i = 60; i < HEIGHT; i++)
        idealWeight += 1.9;
    return kg2lb(idealWeight);
}

const string PrintWeightStatus() {
    switch (getWeightStatus()) {
    case UNDERWEIGHT:
        return "You are underweight.";
    case HEALTHY_WEIGHT:
        return "You are a healthy weight.";
    case OVERWEIGHT:
        return "You are overweight.";
    case OBESE:
        return "You are obese.";
    default:
        return "Error getting weight status.";
    }
}

static const string PrintHealthyWeightRange(double inches) {
    int min = round(18.5 * pow(inches, 2) / 703);
    int max = round(24.9 * pow(inches, 2) / 703);
    return "Ideal Weight Range: " + to_string(min) + " - " + to_string(max) + " lbs.";
}

const int getWeeksUntilIdealWeight(double calorieIntake, double idealWeight, double weight) {
    double weeklyLoss = ((getBMR() - calorieIntake) * 7) / 3500; // 1 lb fat is approx. 3500 cal
    int weeks = 0;

    if (idealWeight == 0)
        idealWeight = getIdealWeight();

    while (weight > idealWeight) {
        weight -= weeklyLoss;
        weeks++;
    }
    return weeks;
}