int source[] = {3, 1, 4, 1, 5, 9, 0};
int dest[10];

int fun(int x) {
	return -x * (x + 1);
}

int main() {
    int k;
    int sum = 0;
    for (k = 0; source[k] != 0; k++) {
        dest[k] = fun(source[k]);
        sum += dest[k];
    }
    return sum;
}

//////////
int f(int x) {
    if (x > 1) {
        return x * f(x-1);
    }
    return 1;
}

int fr(int x) {
    int re = 1;
    while ( x>0 )
    {
        /* code */
        re *= x;
        x--;
    }
    return re;
}
