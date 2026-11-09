#include <iostream> // provide std::cout to print the results in the terminal
#include <vector> // provide std::vector to store the candidates for each empty cell
#include <fstream> // read the file from the computer
#include <string> // provide std::string to store the puzzle in a string format



class SudokuPuzzle
{
        public:

        int puzzle[9][9];

   
        SudokuPuzzle(int p[9][9])

        {
            for (int r = 0; r < 9; r++){  // row
                for (int c = 0; c < 9; c++){ // column
                    puzzle[r][c] = p[r][c]; // store the whole puzzle into the class
                }
            }
        }
        
       
        void print()   // print the puzzle one row per line
        {
            for (int r = 0; r < 9; r++){
                for (int c = 0; c < 9; c++){
                    std::cout << puzzle[r][c] << ' ';
                }
            std::cout << std::endl;
            }
        std::cout << std::endl;     
        }
};




bool is_num_present(int puzzle[9][9], int row, int col, int num)
{

    bool found = false;    // bool is the return type of the function, it is used to check if the number is present in the row, column or box
    for(int c = 0; c < 9; c++)
    {
        if(puzzle[row][c] == num)
        {
            found = true;
        }
    }

    for(int r = 0; r < 9; r++)
    {
        if(puzzle[r][col] == num)
        {
            found = true;
        }
    }

    
// box check, find the top left corner of the box that contains the cell at (row, col)
    int col_offset = (col/3)*3;  
    int row_offset = (row/3)*3;
    for (int r = 0; r<3; r++){
        for (int c = 0; c<3; c++){
            if(puzzle[row_offset + r][col_offset + c] == num){
                found = true;
            }
        }
    }
    return found; // return the result of the check otherwise return false
}


void print_puzzle(int puz[9][9])
{
for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            int clue = puz [i][j];
            if (clue == 0){
                std::cout << " ";
            }else{
                std::cout << clue;
            }
        }
         std::cout << std::endl;
    }
}

// Count and return the number of cells containing zero.
int count_empty(int puzzle[9][9])
{
    int count = 0;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            if(puzzle[r][c] == 0){
                count++;
            }
        }
    }
    return count;
}


// Calculate the candidates for each empty cell and store them in the supplied array of vectors. (go therough from 0-9 and check if the number is present in the row, column or box, if not then add it to the vector)
void calculate_possibilities(int puzzle[9][9],
                            std::vector<int> possibilities[9][9])
{
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
          
            possibilities[r][c].clear();
            if (puzzle[r][c] == 0){
               
                for (int num = 1; num <= 9; num++){
                    bool found = is_num_present(puzzle, r, c, num);
                    if (found == false){
                        possibilities[r][c].push_back(num);
                    }
                }
            }
        }
    }
}

// Fill empty cells that have exactly one candidate (called a singleton).
int fill_singletons(int puzzle[9][9],
                    std::vector<int> possibilities[9][9])
{
    int inserted = 0;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            if (puzzle[r][c] == 0){
                if (possibilities[r][c].size() == 1){
                    puzzle[r][c] = possibilities[r][c][0];
                    inserted++;
                }
            }
        }
    }
    return inserted;
}

// Repeatedly calculate candidates and fill singletons, without guessing. Stop when the board is full.
bool solve_simple(int puzzle[9][9])
{
    std::vector<int> possibilities[9][9];
    int inserted = 1;
    while (count_empty(puzzle) > 0 && inserted > 0)
    {
        calculate_possibilities(puzzle, possibilities);

        inserted = fill_singletons(puzzle, possibilities);
    }

    return count_empty(puzzle) == 0;
}

// convert the 81-character string of digits into a 9x9 box
bool load_puzzle(std::string digits, int puzzle[9][9])
{
    if (digits.size() != 81) {
        return false;
    }
    for (int i = 0; i < 81; i++) {  // exclude numbers that are not between 0-9
        if (digits[i] < '0' || digits[i] > '9') {
            return false;
        }
    }

    // map them into a box
    for (int i = 0; i < 81; i++) {
        int row = i / 9;
        int col = i % 9;
        puzzle[row][col] = digits[i] - '0';
    }

    return true;
}

int main()
{
// open the data base on my computer
    std::ifstream input("easy.txt");
    if (!input.is_open()) {
        std::cout << "Could not open easy.txt\n";
        return 1;
    }

 // calculate all the datas and which puzzles are solved, stalled or malformed and then in the terminal
    int lines_read = 0;
    int attempted = 0;
    int solved = 0;
    int stalled = 0;
    int malformed = 0;

   // read the file line by line, and for each line, load the puzzle, solve it, and update the counters accordingly
    std::string line;
    while (std::getline(input, line)) {
        lines_read++;
        int puzzle[9][9] = {};
        if (line.size() < 94) {
            malformed++;
        } else {
            std::string digits = line.substr(13, 81);
            bool loaded = load_puzzle(digits, puzzle);
            if (loaded == false) {
                malformed++;
            } else {
                attempted++;
                bool complete = solve_simple(puzzle); // use the solve-simple function to solve the puzzle

                if (complete == true) {
                    solved++;
                } else {
                    stalled++;
                }
            }
        }
    }

 // print the results to the terminal
    std::cout << "Lines read: " << lines_read << "\n";
    std::cout << "Attempted: " << attempted << "\n";
    std::cout << "Solved: " << solved << "\n";
    std::cout << "Stalled: " << stalled << "\n";
    std::cout << "Malformed: " << malformed << "\n";
    if (attempted > 0) {
        std::cout << "Percent solved: " // std means command that prints in the terminal
                  << 100.0 * solved / attempted << "%\n";
    }
// Return zero to indicate that the program finished normally.
    return 0;
}
