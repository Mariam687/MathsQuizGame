
#include <iostream> 
using namespace std;
enum enStatus {pass,fail};
enum enLevel{easy=1,medium,hard,mixLevel};
enum enOperation{sum=1,division,mul,minus,mixOp};
struct stExam {
    int QuestionNumber,RightAnswers,WrongAnswers;
    enLevel Level;
    enOperation Operation;
};
int ReadNumber(string message) {
    int number;
    do {
        cout << message;
        cin >> number;
    } while (number <= 0);
    return number;
}
int RandomNumber(int from, int to) {

    return rand() % (to - from + 1) + from;
}
void PrintScreenWinColor(enStatus Status) {
    switch (Status) {
       case pass:
        system("color 2f");
        break;
    default:
        cout << "\a";
        system("color 4f");
    }
}
void ResetScreen() {
    system("cls");
    system("color 0f");
}
int ReadQuestionNumber() {
    int QuestionNumber = ReadNumber("How many questions you want to answer ? ");
    return QuestionNumber;
}
enLevel ReadExamLevel() {
    int Level= ReadNumber("Choose the level of the questions you want [1]easy, [2]medium, [3]hard, [4]mix\n");
    return (enLevel)Level;
}
enOperation ReadExamOperation() {
    int Operation = ReadNumber("Choose the type of the operation you want [1]sum, [2]div, [3]mul, [4]minus, [5]mix\n");
    return (enOperation)Operation;
}
string OperationName(enOperation Operation) {
    string Operations[5] = { "Summition","Division","Multiplication","Difference","Mixed operations" };
    return Operations[Operation - 1];
}
string LevelName(enLevel Level) {
    string Levels[5] = { "Easy","Medium","Hard","Mixed Levels"};
    return Levels[Level - 1];
}
void PrintExamInformation(stExam Exam) {
    cout << "NUmber of questions is " << Exam.QuestionNumber << endl;
    cout << "Type of operation is " << OperationName(Exam.Operation) << endl;
    cout << "Level of the exam is " << LevelName(Exam.Level) << endl;
    cout << "Number of right answers is " << Exam.RightAnswers << endl;
    cout << "Number of wrong answers is " << Exam.WrongAnswers << endl;
}
stExam FillExamInfo(int QuestionNumber, int RightAnswers, int WrongAnswers, enLevel Level, enOperation Operation) {
    stExam Exam;
    Exam.Level = Level;
    Exam.Operation = Operation;
    Exam.QuestionNumber = QuestionNumber;
    Exam.RightAnswers = RightAnswers;
    Exam.WrongAnswers = WrongAnswers;
    return Exam;
}
string Tab(int NumberOfTabs) {
    string Tabs = "";
    for (int i = 0; i < NumberOfTabs; i++)
        Tabs += '\t';
    return Tabs;
}
void Printstatus(stExam Exam) {
    
    cout << "\n-------------------------" << endl;

    if (Exam.RightAnswers >= Exam.WrongAnswers) {

        cout << Tab(1) << "Passed :-)" << endl;
       
    }
    else {
        cout << Tab(1) << "Failed :-(" << endl;
        
    }
    cout << "-------------------------" << endl;
}
int GetRightAnswer(int num1, int num2, enOperation Operation) {
    switch (Operation) {
    case enOperation::sum:
        return num1 + num2;
    case enOperation::division:
        return num1 / num2;
    case enOperation::mul:
        return num1 * num2;
    default:
        return num1 - num2;
    }

}
enStatus CheckAnswer( int UserAnswer,int RightAnswer) {
    if (RightAnswer == UserAnswer) {
        cout << "Right answer :-)" << endl;
        return enStatus::pass;
    }
    else {
        cout << "Wrong answer :-(" << endl;
        cout << "The right answer is " << RightAnswer << endl;
        return enStatus::fail;
    }

}

int AskQuestion(int num1, int num2, enOperation Operation) {
    int answer;
    switch (Operation) { 
    case enOperation::sum:
        cout << num1 << "\n + \n" << num2 << "\n-------\n"; 
        break;
    case enOperation::division:
        cout << (num1) << "\n / \n" << num2 << "\n-------\n";
        break;
    case enOperation::mul:
        cout << num1 << "\n * \n" << num2 << "\n-------\n";
        break;
    default:
        cout << num1 << "\n - \n" << num2 << "\n-------\n";
        break;
    }
    cin >> answer;
    return answer;

}
int GetNum(enLevel Level) {
    switch (Level) {
    case easy:
        return RandomNumber(1, 10);
    case medium:
        return RandomNumber(11, 99);
    case hard:
        return RandomNumber(101, 999);
    }
}
int GetNumForQuestion(enLevel Level) {
    if (Level != mixLevel)
        return GetNum(Level);
    else {
        enLevel L = (enLevel)RandomNumber(1, 3);
        return GetNum(L);
    }
}
enOperation GetOperationForQuestion() {
        enOperation Op = (enOperation)RandomNumber(1, 4);
        return Op;
    }





stExam PlayGame() {
    int NumberOfQuestions = ReadQuestionNumber();
    enLevel Level = ReadExamLevel();
    enLevel LevelOfExam = Level;
    enOperation Operation= ReadExamOperation();
    enOperation OperationOfExam = Operation;
    int UserAnswer,RightAnswer,num1,num2;
    int rightAnswers = 0, WrongAnswers = 0;
    for (int i = 1; i <= NumberOfQuestions; i++) {

        cout << "\nQuestion[" << i << "/" << NumberOfQuestions << "]" << "\n" << endl;
        
        if (LevelOfExam == mixLevel)
            Level = (enLevel)RandomNumber(1, 3);

            num1 = GetNumForQuestion(Level);
            num2 = GetNumForQuestion(Level);
        
        if (OperationOfExam == mixOp)
            Operation = GetOperationForQuestion();

        UserAnswer = AskQuestion(num1, num2, Operation);
        RightAnswer = GetRightAnswer(num1, num2, Operation);
        enStatus status;
        status = CheckAnswer(UserAnswer, RightAnswer);
        if (status == pass)
            rightAnswers++;
        else
            WrongAnswers++;

        PrintScreenWinColor(status);

    }
        return FillExamInfo(NumberOfQuestions, rightAnswers, WrongAnswers, LevelOfExam, OperationOfExam);
}
void StartGame() {
    bool answer = 1;
    while (answer) {
        ResetScreen();
        stExam Exam = PlayGame();
        Printstatus(Exam);
        PrintExamInformation(Exam);
        cout << "\nDo you want to play the game again [0]No, [1]Yes ? ";
        cin >> answer;
    }


}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    
}
