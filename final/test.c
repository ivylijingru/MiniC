int getint(); 
int putchar(int c); 
int putint(int i); 
int getchar();  
int f(int x)
{ 
    if (x < 2)
        return 1; 
    else 
        return f(x - 1) + f(x - 2); 
} 
int g(int j) 
{
    int a[40]; 
    a[0] = 1; 
    int i; 
    i = 2; 
    while (i < j + 1) 
    {
        a[i] = a[i - 1] + a[i - 2];
    }
    return a[j];
}
int n; 
int main() 
{
    n = getint(); 
    if (n < 0 || n > 30) 
        return 1;
    putint(f(n)); 
    putchar(10); 
    putint(g(n)); 
    putchar(10); 
    return 0;
}
