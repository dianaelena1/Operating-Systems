#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

double do_operation(double leftNumber, double rightNumber, char operator) {
    int pipeEnds[2];
    pipe(pipeEnds);

    pid_t childPid = fork();

    if (childPid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (childPid == 0) {
        close(pipeEnds[0]);
        double operationResult;

        if (operator == '+')
            operationResult = leftNumber + rightNumber;
        else if (operator == '-')
            operationResult = leftNumber - rightNumber;
        else if (operator == '*')
            operationResult = leftNumber * rightNumber;
        else if (operator == '/')
            operationResult = leftNumber / rightNumber;
        else {
            printf("Invalid operator\n");
            exit(1);
        }

        printf("Child process %d calculated: %.2lf %c %.2lf = %.2lf\n",
               getpid(), leftNumber, operator, rightNumber, operationResult);

        write(pipeEnds[1], &operationResult, sizeof(operationResult));
        close(pipeEnds[1]);

        exit(0);
    } else {
        close(pipeEnds[1]);
        double operationResult;

        wait(NULL);
        read(pipeEnds[0], &operationResult, sizeof(operationResult));
        close(pipeEnds[0]);

        return operationResult;
    }
}

int main() {
    double a, b, c, d;

    printf("Enter a b c d: ");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    double bTimesC = do_operation(b, c, '*');
    double firstBracket = do_operation(a, bTimesC, '+');

    double aMinusB = do_operation(a, b, '-');
    double aMinusBPlusD = do_operation(aMinusB, d, '+');
    double secondBracket = do_operation(aMinusBPlusD, c, '-');

    if (secondBracket == 0) {
        printf("Error: division by zero\n");
        return 1;
    }

    double divisionPart = do_operation(firstBracket, secondBracket, '/');

    double aTimesB = do_operation(a, b, '*');
    double aTimesBTimesC = do_operation(aTimesB, c, '*');
    double multiplicationPart = do_operation(aTimesBTimesC, d, '*');

    double finalResult = do_operation(divisionPart, multiplicationPart, '+');

    printf("\nFinal result = %.2lf\n", finalResult);

    return 0;
}