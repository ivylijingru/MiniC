// Check the priority between time and plus
int putint(int i);

int main() {
    int a;
    a = 20;
    int b;
    b = 5;
    int c;
    c = 6;
    int d;
    d = -b + c;
    a = a + c * d - b % (a + d) / a;
    a = putint(!a);
    return 0;
}

