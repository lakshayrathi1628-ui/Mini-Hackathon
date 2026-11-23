#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define SUBJECTS 5
#define QUESTIONS 5

struct Student
{
    int id;
    char name[50];
    char course[30];
    int marks[SUBJECTS];
};

char subjects[SUBJECTS][30] = {
    "C Programming",
    "Maths",
    "Physics",
    "Problem Solving",
    "EVS"
};

struct Student s;

int registered = 0;
int marksEntered = 0;
int quizTaken = 0;

int quizScores[SUBJECTS] = {0};

// Function declarations
int readInt(char prompt[], int min, int max);
void readLine(char prompt[], char str[], int size);
void registration();
void viewSubjects();
void enterMarks();
void takeQuiz();
void analysePerformance();
void viewResult();

// Safe integer input
int readInt(char prompt[], int min, int max)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
            return min;

        value = strtol(input, &end, 10);

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (end == input || *end != '\0' ||
            value < min || value > max)
        {
            printf("Invalid input! Enter a number between %d and %d.\n",
                   min, max);
        }
        else
        {
            return (int)value;
        }
    }
}

// Read text input
void readLine(char prompt[], char str[], int size)
{
    printf("%s", prompt);

    if (fgets(str, size, stdin) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
    }
}

// Student Registration
void registration()
{
    printf("\n====================================\n");
    printf("       STUDENT REGISTRATION\n");
    printf("====================================\n");

    s.id = readInt("Enter Student ID: ", 1, 999999999);

    readLine("Enter Student Name: ", s.name, sizeof(s.name));

    readLine("Enter Course: ", s.course, sizeof(s.course));

    registered = 1;
    marksEntered = 0;
    quizTaken = 0;

    for (int i = 0; i < SUBJECTS; i++)
    {
        s.marks[i] = 0;
        quizScores[i] = 0;
    }

    FILE *fp = fopen("students.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp, "%d | %s | %s\n",
                s.id, s.name, s.course);

        fclose(fp);
    }

    printf("\nRegistration Successful!\n");
}

// Display Subjects
void viewSubjects()
{
    printf("\n====================================\n");
    printf("          AVAILABLE SUBJECTS\n");
    printf("====================================\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("%d. %s\n", i + 1, subjects[i]);
    }
}

// Enter Subject Marks
void enterMarks()
{
    if (!registered)
    {
        printf("\nPlease register first!\n");
        return;
    }

    printf("\n====================================\n");
    printf("          ENTER SUBJECT MARKS\n");
    printf("====================================\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        char prompt[100];

        snprintf(prompt, sizeof(prompt),
                 "Enter marks for %s (0-100): ",
                 subjects[i]);

        s.marks[i] = readInt(prompt, 0, 100);
    }

    marksEntered = 1;
    quizTaken = 0;

    for (int i = 0; i < SUBJECTS; i++)
    {
        quizScores[i] = 0;
    }

    FILE *fp = fopen("results.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp, "\n====================================\n");
        fprintf(fp, "Student: %s\n", s.name);
        fprintf(fp, "Student ID: %d\n", s.id);

        for (int i = 0; i < SUBJECTS; i++)
        {
            fprintf(fp, "%s: %d/100\n",
                    subjects[i], s.marks[i]);
        }

        fclose(fp);
    }

    printf("\nMarks saved successfully!\n");
}

// Quiz System - All Five Subjects
void takeQuiz()
{
    int choice;
    int totalScore = 0;

    const char *questions[5][5] = {
        {
            "Which function is the starting point of C?",
            "Which header file is used for printf()?",
            "Which keyword declares an integer?",
            "Which symbol ends a C statement?",
            "What is the first index of an array?"
        },

        {
            "What is 2 + 3 * 4?",
            "What is the square root of 81?",
            "What is the sum of angles in a triangle?",
            "What is 25% of 200?",
            "What is 7 multiplied by 8?"
        },

        {
            "What is the SI unit of force?",
            "How is speed calculated?",
            "What is the SI unit of energy?",
            "What is the SI unit of electric current?",
            "Which force pulls objects towards Earth?"
        },

        {
            "Breaking a complex problem into smaller parts is called?",
            "Which flowchart symbol represents a decision?",
            "What is an algorithm?",
            "What is debugging?",
            "What is pseudocode?"
        },

        {
            "Which is a renewable source of energy?",
            "What are the 3Rs of waste management?",
            "Which is a major source of urban air pollution?",
            "What does biodiversity mean?",
            "Which action helps conserve water?"
        }
    };

    const char *options[5][5][4] = {
        {
            {"start()", "main()", "run()", "begin()"},
            {"stdlib.h", "string.h", "math.h", "stdio.h"},
            {"float", "char", "int", "double"},
            {".", ";", ":", ","},
            {"0", "1", "2", "-1"}
        },

        {
            {"10", "14", "20", "24"},
            {"6", "8", "9", "10"},
            {"90", "180", "270", "360"},
            {"25", "40", "50", "75"},
            {"48", "54", "56", "64"}
        },

        {
            {"Newton", "Joule", "Watt", "Pascal"},
            {"Distance / Time", "Time / Distance",
             "Mass / Volume", "Force / Area"},
            {"Newton", "Watt", "Joule", "Volt"},
            {"Volt", "Ohm", "Watt", "Ampere"},
            {"Gravity", "Friction", "Magnetism", "Pressure"}
        },

        {
            {"Abstraction", "Decomposition",
             "Compilation", "Iteration"},
            {"Rectangle", "Oval", "Diamond", "Circle"},
            {"A finite set of steps", "A computer",
             "A programming language", "A hardware device"},
            {"Finding and fixing errors", "Writing code",
             "Drawing diagrams", "Saving files"},
            {"A type of hardware",
             "An informal description of an algorithm",
             "A database", "An operating system"}
        },

        {
            {"Solar energy", "Coal", "Petroleum", "Natural gas"},
            {"Read, Write, Run",
             "Reduce, Reuse, Recycle",
             "Remove, Replace, Return",
             "Reuse, Repair, Refuse"},
            {"Vehicle emissions", "Rainwater",
             "Trees", "Wind"},
            {"Variety of living organisms",
             "Types of buildings",
             "Different types of machines",
             "Weather conditions"},
            {"Leaving taps running",
             "Washing vehicles daily",
             "Turning off taps when not in use",
             "Wasting drinking water"}
        }
    };

    // Correct option numbers
    int answers[5][5] = {
        {2, 4, 3, 2, 1},
        {2, 3, 2, 3, 3},
        {1, 1, 3, 4, 1},
        {2, 3, 1, 1, 2},
        {1, 2, 1, 1, 3}
    };

    if (!registered)
    {
        printf("\nPlease register first!\n");
        return;
    }

    if (!marksEntered)
    {
        printf("\nPlease enter subject marks first!\n");
        return;
    }

    printf("\n====================================\n");
    printf("       EDUBRIDGE SUBJECT QUIZ\n");
    printf("====================================\n");

    // Quiz for all five subjects
    for (int i = 0; i < SUBJECTS; i++)
    {
        quizScores[i] = 0;

        printf("\n\n========== %s ==========\n", subjects[i]);

        for (int j = 0; j < QUESTIONS; j++)
        {
            printf("\nQ%d. %s\n", j + 1, questions[i][j]);

            for (int k = 0; k < 4; k++)
            {
                printf("%d. %s\n", k + 1, options[i][j][k]);
            }

            choice = readInt("Enter your answer (1-4): ", 1, 4);

            if (choice == answers[i][j])
            {
                printf("Correct Answer!\n");
                quizScores[i]++;
            }
            else
            {
                printf("Incorrect Answer!\n");
            }
        }

        printf("\n%s Quiz Score: %d/5\n",
               subjects[i], quizScores[i]);

        totalScore += quizScores[i];
    }

    quizTaken = 1;

    printf("\n====================================\n");
    printf("           FINAL QUIZ RESULT\n");
    printf("====================================\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("%s: %d/5\n",
               subjects[i], quizScores[i]);
    }

    printf("\nTotal Score: %d/25\n", totalScore);

    printf("Overall Quiz Percentage: %.2f%%\n",
           (totalScore / 25.0) * 100);

    printf("\nQuiz Completed Successfully!\n");

    FILE *fp = fopen("results.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp, "\n----- SUBJECT QUIZ SCORES -----\n");

        for (int i = 0; i < SUBJECTS; i++)
        {
            fprintf(fp, "%s: %d/5\n",
                    subjects[i], quizScores[i]);
        }

        fprintf(fp, "Total Quiz Score: %d/25\n", totalScore);

        fclose(fp);
    }
}

// Performance Analysis
void analysePerformance()
{
    float total = 0;
    int weak = 0;
    int average = 0;
    int strong = 0;

    if (!marksEntered)
    {
        printf("\nPlease enter marks first!\n");
        return;
    }

    if (!quizTaken)
    {
        printf("\nPlease complete all five subject quizzes first!\n");
        return;
    }

    printf("\n====================================\n");
    printf("          PERFORMANCE ANALYSIS\n");
    printf("====================================\n");

    printf("\nStudent Name: %s\n", s.name);
    printf("Student ID: %d\n", s.id);
    printf("Course: %s\n", s.course);

    printf("\n----- SUBJECT-WISE PERFORMANCE -----\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        total += s.marks[i];

        printf("\n%s\n", subjects[i]);
        printf("Marks: %d/100\n", s.marks[i]);
        printf("Quiz Score: %d/5\n", quizScores[i]);

        if (s.marks[i] < 40)
        {
            printf("Performance: Weak\n");
            weak++;
        }
        else if (s.marks[i] < 60)
        {
            printf("Performance: Average\n");
            average++;
        }
        else
        {
            printf("Performance: Strong\n");
            strong++;
        }
    }

    printf("\nOverall Percentage: %.2f%%\n",
           total / SUBJECTS);

    printf("Overall Quiz Score: %d/25\n",
           quizScores[0] + quizScores[1] +
           quizScores[2] + quizScores[3] +
           quizScores[4]);

    printf("\n----- PERFORMANCE SUMMARY -----\n");

    printf("Weak Subjects: %d\n", weak);
    printf("Average Subjects: %d\n", average);
    printf("Strong Subjects: %d\n", strong);

    // Weak Subject Pointers
    printf("\n====================================\n");
    printf("       AREAS NEEDING IMPROVEMENT\n");
    printf("====================================\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        if (s.marks[i] < 40 || quizScores[i] <= 2)
        {
            printf("\n%s:\n", subjects[i]);

            switch (i)
            {
                case 0:
                    printf("- Revise variables, loops, arrays and functions.\n");
                    break;

                case 1:
                    printf("- Practise formulas, algebra and numerical problems.\n");
                    break;

                case 2:
                    printf("- Revise physics concepts, units and numericals.\n");
                    break;

                case 3:
                    printf("- Practise algorithms, flowcharts and logical reasoning.\n");
                    break;

                case 4:
                    printf("- Revise ecosystems, biodiversity, pollution and sustainability.\n");
                    break;
            }

            if (quizScores[i] <= 2)
            {
                printf("- Practise more questions from this subject.\n");
            }
        }
    }

    if (weak == 0)
    {
        int needsWork = 0;

        for (int i = 0; i < SUBJECTS; i++)
        {
            if (quizScores[i] <= 2)
                needsWork = 1;
        }

        if (!needsWork)
            printf("No major improvement areas identified!\n");
    }

    // Strong Subject Pointers
    printf("\n====================================\n");
    printf("            STRONG AREAS\n");
    printf("====================================\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        if (s.marks[i] >= 60 && quizScores[i] >= 3)
        {
            printf("\n%s:\n", subjects[i]);

            printf("- Maintain consistent performance.\n");
            printf("- Practise advanced questions.\n");
            printf("- Apply knowledge to practical examples.\n");
        }
    }

    printf("\n====================================\n");
    printf("       END OF PERFORMANCE REPORT\n");
    printf("====================================\n");
}

// View Saved Results
void viewResult()
{
    FILE *fp = fopen("results.txt", "r");
    char line[200];

    if (fp == NULL)
    {
        printf("\nNo saved results available!\n");
        return;
    }

    printf("\n====================================\n");
    printf("            SAVED RESULTS\n");
    printf("====================================\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

// Main Function
int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("========================================\n");
        printf("        EDUBRIDGE LEARNING SYSTEM\n");
        printf("========================================\n");

        printf("1. Student Registration\n");
        printf("2. View Subjects\n");
        printf("3. Enter Subject Marks\n");
        printf("4. Take All Subject Quizzes\n");
        printf("5. Analyse Performance\n");
        printf("6. View Results\n");
        printf("7. Exit\n");

        choice = readInt("\nEnter Your Choice: ", 1, 7);

        switch (choice)
        {
            case 1:
                registration();
                break;

            case 2:
                viewSubjects();
                break;

            case 3:
                enterMarks();
                break;

            case 4:
                takeQuiz();
                break;

            case 5:
                analysePerformance();
                break;

            case 6:
                viewResult();
                break;

            case 7:
                printf("\nThank you for using EduBridge!\n");
                break;
        }

    } while (choice != 7);

    return 0;
}