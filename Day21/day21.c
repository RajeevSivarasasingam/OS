 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Function to calculate circle area
float CircleArea(float radius){
    return 3.14159 * radius * radius;
}

// Function to calculate triangle area
float TriangleArea(float base, float height){
    return 0.5 * base * height;
}

// Function to calculate square area
float SquareArea(float side){
    return side * side;
}

// Function to calculate rectangle area
float RectangleArea(float length, float width){
    return length * width;
}

int main() {
    int pipefd[2]; // Pipe file descriptors this is a array 
    char choice;
    float area, param1, param2;
    pid_t pid;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent Process: Get user input and send data through the pipe
        printf("Area Calculation Program\n");
        printf("Circle => C\nTriangle => T\nSquare => S\nRectangle => R\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        close(pipefd[0]); // Close unused read end

        switch(choice) {
            case 'C':
                printf("\nCircle area calculation:\nEnter radius: ");
                scanf("%f", &param1);
                area = CircleArea(param1);
                break;
            case 'T':
                printf("\nTriangle area calculation:\nEnter base: ");
                scanf("%f", &param1);
                printf("Enter height: ");
                scanf("%f", &param2);
                area = TriangleArea(param1, param2);
                break;
            case 'S':
                printf("\nSquare area calculation:\nEnter side length: ");
                scanf("%f", &param1);
                area = SquareArea(param1);
                break;
            case 'R':
                printf("\nRectangle area calculation:\nEnter length: ");
                scanf("%f", &param1);
                printf("Enter width: ");
                scanf("%f", &param2);
                area = RectangleArea(param1, param2);
                break;
            default:
                printf("Invalid choice!!\n");
                return 1;
        }

        write(pipefd[1], &choice, sizeof(choice));
        write(pipefd[1], &area, sizeof(area));

        close(pipefd[1]); // Close write end after sending data

        // Wait for the child process to finish
        wait(NULL);
    } else {
        // Child Process: Receive data from pipe and display output
        close(pipefd[1]); // Close unused write end

        read(pipefd[0], &choice, sizeof(choice));
        read(pipefd[0], &area, sizeof(area));

        close(pipefd[0]); // Close read end after receiving data

        printf("\n--- Child Process Output ---\n");
        switch(choice) {
            case 'C': printf("Circle area: %.2f\n", area); break;
            case 'T': printf("Triangle area: %.2f\n", area); break;
            case 'S': printf("Square area: %.2f\n", area); break;
            case 'R': printf("Rectangle area: %.2f\n", area); break;
            default: printf("Invalid choice received!\n"); break;
        }
    }

    return 0;
}
