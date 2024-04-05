#include <iostream>
#include <cstdlib>  // for rand/srand
#include <ctime>    // for time
#include <string>//for stoi
const int MAX_SIZE=16;

// Global variables for counts
int Cexact = 0;
int Cmisplaced = 0;
int randomNumDigitAmount=0;//IMPLEMENT IMMIDIATELY
int moveCounter=0;
bool userWon=false;
//Global variable for valid element checklist
char validElements[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
//Global variable for gameplay
char randomNumber[MAX_SIZE];
char userSetNumber[MAX_SIZE];
char userGuess[MAX_SIZE];
//helper functions
void fillArray(char array[],int size);
void printArray(char array[],int size);
int arraySize(char array[]);
int randomIntGenerator();
void copyArray(char destination[],char source[]);
bool compareArrays(char arr1[], char arr2[]);

//minor but useful game oriented functions
void printGameSituation(int cex, int cmis);
bool gameOver();
bool gameOverUserSetVersion(int argv2);
void takeInput();
void takeInputUserSetVersion(int argv2);
//major functions
bool isValidInput(char array[]);
void createRandomNumber(char array[],int size);
void determineExactOrMisplaced(char secret[],char guess[]);
void randomGame(int randomNumDigitAmount_input);
void userSetGame(int argv2);

int main(int argc, char* argv[]) {
  srand(time(0));
    if (argc != 3) {
        std::cout << "E0";
        return 1;
    }

     char r[3] = "-r";
     char u[3] = "-u";

    if (compareArrays(argv[1], r)) {
        int digitAmount = std::stoi(argv[2]);
        if (digitAmount > 16 || digitAmount <= 0) {
            std::cout << "E0";
            return 1;
        } else {
            randomGame(digitAmount);
        }
    } else if (compareArrays(argv[1], u)) {
        if (!isValidInput(argv[2])) {
            std::cout << "E0";
            return 1;
        } else {
            copyArray(userSetNumber, argv[2]);
            int argv2 = arraySize(argv[2]);
            userSetGame(argv2);
        }
    } else {
        std::cout << "E0";
        return 1;
    }

    return 0;
}
int arraySize(char array[])
{
  int count = 0;
    while(array[count] != '\0')
    {
      count++;
    }
    return count; // Return the number of characters excluding the null terminator

}

void fillArray(char array[],int size)
{
  for(int i=0;i<size;i++)
  {
    std::cin>>array[i];
  }
  array[size]='\0';
}

void printArray(char array[],int size)
{
  for(int i=0;i<size;i++)
  {
    std::cout<<array[i];
  }
  std::cout<<"\n";
}

int randomIntGenerator()
{
  return (rand()%MAX_SIZE)+1;
}

void copyArray(char destination[],char source[]) {
  // Loop through each character of the source string
  int i = 0;
  while (source[i] != '\0') {
    // Copy the character from source to destination
    destination[i] = source[i];
    i++;
  }

  // Add null terminator to the destination string
  destination[i] = '\0';
}

bool isValidInput(char input[]){

  bool charValid=true;
  bool noDuplicates=true;
  for(int i=0;i<arraySize(input);i++)
  {
    for(int j=0;j<MAX_SIZE;j++)
    {
      if(input[i]!=validElements[j]){
      charValid=false;
      break;
      }
    }
  }

  for (int i = 0; i < arraySize(input); i++)
  {
  for (int j = i + 1; j < arraySize(input); j++)
  {
    if (input[i] == input[j]) {
      noDuplicates = false;
      break;
    }
  }
}
  
  if(arraySize(input)<=MAX_SIZE&&charValid&&input[0]!='0'&&noDuplicates)
  {
    return true;
  }
  else
  {
    return false;
  } 
}

void createRandomNumber(char array[],int size)
{
  do
  {
  const int MAX_CHARS=arraySize(validElements);
    
    int filled = 0; // Tracks the number of characters filled into the array
    while (filled < size) {
        int randIndex = randomIntGenerator();
        char nextChar = validElements[randIndex];

        // Check if nextChar is already in array
        bool isUnique = true;
        for (int i = 0; i < filled; ++i) {
            if (array[i] == nextChar) {
                isUnique = false;
                break; // nextChar is already in the array, break the inner loop
            }
        }

        // If nextChar is not in the array, add it
        if (isUnique) {
            array[filled] = nextChar;
            filled++;
        }
    }

    // Ensure the array is properly null-terminated
    array[filled] = '\0';
    }
    while(!isValidInput(array));
}

void determineExactOrMisplaced(char secret[],char guess[])
{
  Cexact = 0; // Reset global count variables
    Cmisplaced = 0;

    // Temporary arrays to mark matched characters
    char tempSecret[MAX_SIZE] = {}; // Assuming strings won't be longer than 100 characters
    char tempGuess[MAX_SIZE] = {};

    // First, find exact matches
    for (int i = 0; i < arraySize(guess) && i < arraySize(secret); ++i) {
        if (guess[i] == secret[i]) {
            Cexact++;
            tempSecret[i] = 'X'; // Mark matched characters
            tempGuess[i] = 'X';
        }
    }

    // Then, find misplaced matches
    for (int i = 0; i < arraySize(guess); ++i) {
        if (tempGuess[i] != 'X') { // If not already matched exactly
            for (int j = 0; j < arraySize(secret); ++j) {
                if (tempSecret[j] != 'X' && guess[i] == secret[j]) {
                    Cmisplaced++;
                    tempSecret[j] = 'X'; // Mark as matched to avoid double counting
                    break; // Move to the next character in guess
                }
            }
        }
    }
}

void printGameSituation(int cex, int cmis)
{
  std::cout<<"Cexact: "<<cex<<" Cmisplaced: "<<cmis<<"\n";
}

bool gameOver()
{
  if(Cexact==arraySize(randomNumber))
  {
    userWon=true;
    return true;
  }
  else if(moveCounter>100)
  {
  return true;
  }
  else
  {
  return false;
  }
}

void randomGame(int randomNumDigitAmount_input)
{
  randomNumDigitAmount=randomNumDigitAmount_input;
  std::cout<<"Welcome to the mastermind game.\nIt's my understanding that you've chosen to play with a random number consisting\n of "<<randomNumDigitAmount<<" digits.\n";
  createRandomNumber(randomNumber,randomNumDigitAmount);
  std::cout<<randomNumDigitAmount<<" digit secret number has been generated.\n";
  std::cout<<"for debugging, secret number is: ";
  printArray(randomNumber,arraySize(randomNumber));//debug purposes
  std::cout<<"\n";
  do
  {
    std::cout<<"Enter guess: ";
    takeInput();
    moveCounter++;
    determineExactOrMisplaced(randomNumber,userGuess);
    printGameSituation(Cexact,Cmisplaced);
    
  }while(!gameOver());
  if(userWon)
  {
  std::cout<<"Congratulations! Found the secret number in "<<moveCounter<<" tries.";
  }
  else
  {
  std::cout<<"Tough break... You've exceeded the 100 try limit and failed.";
  }




}




void takeInput() {
    std::string input;
    std::getline(std::cin, input); // Capture the entire input line
    char inputA[16]; 
    std::strcpy(inputA,input.c_str());
    if ((input.length() != randomNumDigitAmount||!isValidInput(inputA))) {
        std::cout << "E1";
        exit(1);
    }

    for (int i = 0; i < randomNumDigitAmount; i++) {
        userGuess[i] = input[i];
    }
    userGuess[randomNumDigitAmount] = '\0'; // Ensure null termination
}


// void takeInput() {
//     std::cout << "Enter your guess: ";
//     for (int i = 1; i < randomNumDigitAmount; i++) {
//         char ch;
//         std::cin >> ch;
//         if (std::cin.fail()) {
//             std::cout << "E1";
//             exit(1);
//         }
//         userGuess[i] = ch;
//     }
//     userGuess[randomNumDigitAmount] = '\0'; // Ensure null termination
// }

// void takeInput()
// {
//   char initialInput[MAX_SIZE];
//   fillArray(initialInput,randomNumDigitAmount);
//   if(arraySize(initialInput)!=randomNumDigitAmount)
//   {
//     std::cout<<"E1";
//     exit(1);
//   }
//   else
//   {
//     copyArray(userGuess,initialInput);
//   }
// }

void userSetGame(int argv2)
{
  
  std::cout<<"Secret number has been taken from the user as input.\n";
  std::cout<<"for debugging, secret number is: ";
  printArray(userSetNumber,arraySize(userSetNumber));//debug purposes
  std::cout<<"\n";
  do
  {
    std::cout<<"Enter guess: ";
    takeInputUserSetVersion(argv2);
    moveCounter++;
    determineExactOrMisplaced(userSetNumber,userGuess);
    printGameSituation(Cexact,Cmisplaced);
    
  }while(!gameOverUserSetVersion(argv2));
  if(userWon)
  {
  std::cout<<"Congratulations! Found the secret number in "<<moveCounter<<" tries.";
  }
  else
  {
  std::cout<<"Tough break... You've exceeded the 100 try limit and failed.";
  }
}

void takeInputUserSetVersion(int argv2) {
    std::string input;
    std::getline(std::cin, input); // Capture the entire input line

    if (input.length() != static_cast<size_t>(argv2)) {
        std::cout << "E1";
        exit(1);
    }

    for (int i = 0; i < argv2; i++) {
        userGuess[i] = input[i];
    }
    userGuess[argv2] = '\0'; // Ensure null termination
}

// void takeInputUserSetVersion(int argv2)
// {
//     char initialInput[MAX_SIZE];
//   fillArray(initialInput,argv2);
//   if(arraySize(initialInput)!=argv2)
//   {
//     std::cout<<"E1";
//     exit(1);
//   }
//   else
//   {
//     copyArray(userGuess,initialInput);
//   }
// }

bool gameOverUserSetVersion(int argv2)
{
  if(Cexact==arraySize(userSetNumber))
  {
    userWon=true;
    return true;
  }
  else if(moveCounter>100)
  {
  return true;
  }
  else
  {
  return false;
  }
}

bool compareArrays(char arr1[], char arr2[]) {
  // Check if lengths match (excluding null terminator)
  int len1 = strlen(arr1);
  int len2 = strlen(arr2);
  if (len1 != len2) {
    return false; // Different lengths, not equal
  }

  // Loop through each element and compare
  for (int i = 0; i < len1; i++) {
    if (arr1[i] != arr2[i]) {
      return false; // Elements differ, not equal
    }
  }

  // If all elements match, return true
  return true;
}
