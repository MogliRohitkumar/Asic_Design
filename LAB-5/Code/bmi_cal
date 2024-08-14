#include <stdio.h>

void calculateBMI(double weight, double height) {
    double bmi = weight / (height * height);
    printf("Your BMI is: %.2f\n", bmi);
    if (bmi < 18.5) {
        printf("You are underweight.\n");
    } else if (bmi < 24.9) {
        printf("You have a normal weight.\n");
    } else if (bmi < 29.9) {
        printf("You are overweight.\n");
    } else {
        printf("You are obese.\n");
    }
}

int main() {
    double weight, height;

    printf("Enter your weight in kilograms: ");
    scanf("%lf", &weight);
    printf("Enter your height in meters: ");
    scanf("%lf", &height);

    calculateBMI(weight, height);

    return 0;
}
