#include <thread>
#include <emscripten.h>
#include <vector>

typedef long int i32;

extern "C" {
EMSCRIPTEN_KEEPALIVE
i32 *calculate(i32 from, i32 to) {
    std::vector<i32> factors;

    for (int j = from; j < to; j++) {
        // Divide the number by 2 until it is no longer divisible by 2
        i32 number = j;
        while (number % 2 == 0) {
            factors.push_back(2);
            number /= 2;
        }

        // Divide the number by odd numbers starting from 3
        for (int i = 3; i * i <= number; i += 2) {
            while (number % i == 0) {
                factors.push_back(i);
                number /= i;
            }
        }

        // If the number is still greater than 2, it must be a prime number itself
        if (number > 2) {
            factors.push_back(number);
        }
    }

    i32 *result = (i32 *) malloc(2 * sizeof(i32));
    result[0] = factors.size();
    result[1] = (i32) &factors[0];
    return result;
}
}

int main() {

}