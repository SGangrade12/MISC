#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int degree;
    int *coefficients;
} Polynomial;

Polynomial createPolynomial(int degree)
{
    Polynomial p;
    p.degree = degree;
    p.coefficients = (int *)malloc((degree + 1) * sizeof(int));
    for (int i = 0; i <= degree; i++)
    {
        p.coefficients[i] = 0;
    }
    return p;
}

Polynomial addPolynomials(Polynomial p1, Polynomial p2)
{
    int maxDegree = (p1.degree > p2.degree) ? p1.degree : p2.degree;
    Polynomial result = createPolynomial(maxDegree);

    for (int i = 0; i <= maxDegree; i++)
    {
        int coeff1 = (i <= p1.degree) ? p1.coefficients[i] : 0;
        int coeff2 = (i <= p2.degree) ? p2.coefficients[i] : 0;
        result.coefficients[i] = coeff1 + coeff2;
    }
    return result;
}

Polynomial subtractPolynomials(Polynomial p1, Polynomial p2)
{
    int maxDegree = (p1.degree > p2.degree) ? p1.degree : p2.degree;
    Polynomial result = createPolynomial(maxDegree);

    for (int i = 0; i <= maxDegree; i++)
    {
        int coeff1 = (i <= p1.degree) ? p1.coefficients[i] : 0;
        int coeff2 = (i <= p2.degree) ? p2.coefficients[i] : 0;
        result.coefficients[i] = coeff1 - coeff2;
    }
    return result;
}

Polynomial multiplyPolynomials(Polynomial p1, Polynomial p2)
{
    Polynomial result = createPolynomial(p1.degree + p2.degree);

    for (int i = 0; i <= p1.degree; i++)
    {
        for (int j = 0; j <= p2.degree; j++)
        {
            result.coefficients[i + j] += p1.coefficients[i] * p2.coefficients[j];
        }
    }
    return result;
}

void printPolynomial(Polynomial p)
{
    for (int i = 0; i <= p.degree; i++)
    {
        if (p.coefficients[i] != 0)
        {
            printf("%dx^%d ", p.coefficients[i], i);
            if (i < p.degree)
            {
                printf("+ ");
            }
        }
    }
    printf("\n");
}

int main()
{
    Polynomial p1 = createPolynomial(2);
    p1.coefficients[0] = 3;
    p1.coefficients[1] = 2;
    p1.coefficients[2] = 5;

    Polynomial p2 = createPolynomial(2);
    p2.coefficients[0] = 1;
    p2.coefficients[2] = 4;

    printf("P1: ");
    printPolynomial(p1);
    printf("P2: ");
    printPolynomial(p2);

    Polynomial sum = addPolynomials(p1, p2);
    printf("Addition: ");
    printPolynomial(sum);

    Polynomial difference = subtractPolynomials(p1, p2);
    printf("Subtraction: ");
    printPolynomial(difference);

    Polynomial product = multiplyPolynomials(p1, p2);
    printf("Multiplication: ");
    printPolynomial(product);

    free(p1.coefficients);
    free(p2.coefficients);
    free(sum.coefficients);
    free(difference.coefficients);
    free(product.coefficients);
    getch();
    return 0;
}
