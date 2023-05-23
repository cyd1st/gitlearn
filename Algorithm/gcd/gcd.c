int myGcd(int a, int b)
{
    // int _a = (a > b ? a : b);
    // int _b = (a > b ? b : a);

    if (a % b == 0) {
        return b;
    }

    return myGcd(b, a%b);
}