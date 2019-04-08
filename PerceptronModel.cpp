#include <iostream>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#define N 10
using namespace std;

float l=-1.00, h=1.00; //low and high for random value
float lr = 0.1;

// activation function
int sign(float n){
    if(n >= 0){
        return 1;
    } else {
        return -1;
    }
}

class Perceptron {
    public:

        float weights[N];
        //float lr;

        //Initializing weights with random value at first
        Perceptron(){
            for (int i=0; i<N; i++){
                weights[i] = l + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(h-l)));
            }
            //lr = 0.1;
        }

        int guess(float inputs[]){
            float sum = 0;
            for(int i=0; i<N; i++){
                sum += inputs[i]*weights[i];
            }
            int output = sign(sum);
            return output;
        }

        void train(float inputs[], int target){
            int guessValue = guess(inputs);
            int error = target - guessValue;

            for(int i=0; i<N; i++){
                weights[i] += error * inputs[i] + lr;
            }
        }
};

class Point{
    public:
        float x;
        float y;
        int label; // whether above(1) or below(-1)

        Point(){
            cout.precision(2);
            x = l + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(100-1)));
            y = l + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(100-1)));

            if (x > y){
                label = 1; // above diagonal
            } else {
                label = -1; // below diagonal
            }
        }

        void show(){
            if (label == 1) {
                cout << "(" << setprecision(2) << x << ", (" << setprecision(2) << y << ")\t" << "- Above" << endl;
            } else {
                cout << "(" << setprecision(2) << x << ", (" << setprecision(2) << y << ")\t" << "- Below" << endl;
            }
        }
};

int main()
{
    // for make the value really random each time
    srand(static_cast<unsigned>(time(0)));

    // creating a single perceptron
    Perceptron brain;
    // creating 20 points e.g. p(5,6), p(6,5)... to 20
    Point pt[20];


    float inputs[N];
    // setting the input value randomly between -1 and 1
    for(int i=0; i<N; i++){
        inputs[i] = l + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(h-l)));
    }

    // displaying the inputs and weights
    cout << "curent initialized random inputs and weights are: \n";
    cout << "Inputs\tWeights" << endl;
    for(int i=0; i<N; i++){
        cout << setprecision(2) << inputs[i] << "\t" << setprecision(2) << brain.weights[i] << endl;
    }

    // guessed value
    int guess = brain.guess(inputs);
    cout << endl << "Guessed value is: " << guess << endl;

    cout << endl << endl;

    // displaying points
    for(int i=0; i<20; i++){
        pt[i].show();
    }

    // train the data
    for(int i=0; i<20; i++){
        float inputs[] = {pt[i].x, pt[i].y};
        brain.train(inputs, pt[i].label);
    }


    cout << endl << endl;
    // After trained
    // displaying the inputs and weights
    cout << "After the training, inputs and weights are: \n";
    cout << "Inputs\tWeights" << endl;
    for(int i=0; i<N; i++){
        cout << setprecision(2) << inputs[i] << "\t" << setprecision(2) << brain.weights[i] << endl;
    }

    // guessed value
    guess = brain.guess(inputs);
    cout << endl << "Guessed value is: " << guess << endl;


    getch();
    return 0;

}

