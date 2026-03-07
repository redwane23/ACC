// MathUtils in a class style but in c for better usability ,privecy and encapsulation
// and it's a huge advantege on memeory managment as it only take a pointer of the struct and then fetch only needed vars each time
typedef struct {
    double integral;
    double prev_value;
    double limit;
} MathUtils;



// Math Utility Functions
double math_update_integral(MathUtils* utils, double error, double dt);
double math_update_derivative(MathUtils* utils, double current_val, double dt);
void math_reset(MathUtils* utils);

// Helper function (Static inline for performance)
static inline double sign(double x) {
    return (double)((x > 0) - (x < 0));
}