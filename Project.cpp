/*
Mohanad Ayman Aly
20180296
Bishoy Mokhless Khela
20180072
Hassan Mahmoud Hassan
20180088
*/
#include <iostream>
#include <fstream> // input file stream
#include <string>
#include <cstdlib> // rand()
#include<ctime> // time() to change the random seed

using namespace std;

//function prototypes
void show_admin(int& q_count); // [1] admin menu

void show_questions(int& q_count); // [1][1] View All Questions

int is_numeric(string variable); // [1][1]* check if a string consists of only numbers

int char_to_int(string variable); // [1][1]** extract integers from a string

void add_question(int& q_count); // [1][2] Add a new question

void load_file(int& q_count); // [1][3] Load questions from file

void update_name(string& user_name); // [2] change user's name

void start_quiz(int& score, int q_count, int quiz_questions, int& quiz_id); // [3] start a new quiz

void show_stats(int* scores, int numofQuizzes, int quiz_questions, int& exit); // [4] show score statistics

void show_scores(int* scores, int numofQuizzes, int quiz_questions, int& exit); // [5] show all previous scores

int* randomnumbers(int last, int numofInt); // ** generate a "numofInt" random integers in the range [first, last]

struct Quiz { // Struct to store a question and its 4 choices
	string sentence;
	string choices[4];
};

Quiz question[100]; // Array of 100 structs

int main() {
	int scores[100]; // Array of 100 integers to store score for each quiz
	int quiz_id = 0; // index of last quiz taken
	int q_count = 0; // number of questions stored in the structs
	int quiz_questions = 5; // number of questions per quiz
	int exit = 0; // flag to exit the program
	string user_name = "USER"; // variable to store the user's name
	while (true) {
		string tempCHOICE; // temporary storage for user's choice
		int choice = 0; // user's actual choice
		cout << "Welcome " << user_name << ", please choose from the following options:" << endl; // print main menu's text
		cout << "[1] Go to administration menu" << endl;
		cout << "[2] Update your name " << endl;
		cout << "[3] Start a new quiz" << endl;
		cout << "[4] Display your scores statistics " << endl;
		cout << "[5] Display all your scores" << endl;
		cout << "[6] Exit " << endl;
		cout << "My choice: ";
		getline(cin, tempCHOICE); // get user's input to a string

		while (is_numeric(tempCHOICE) != 1) { // if user's input isn't strictly numeric, ask for it again
			cout << "Please enter a number" << endl;
			getline(cin, tempCHOICE);
		}
		choice = char_to_int(tempCHOICE); // extract the integer from the user's input
		while (choice < 1 || choice > 6) { // if the integer isn't within bounds, ask for it again
			cout << "Please enter a correct option" << endl;
			getline(cin, tempCHOICE);
			while (is_numeric(tempCHOICE) != 1) { // re-check for numeric value
				cout << "Please enter a number" << endl;
				getline(cin, tempCHOICE);
			}
			choice = char_to_int(tempCHOICE); // store the numeric value
		}

		if (choice == 1) {
			show_admin(q_count); // show admin menu
		}
		else if (choice == 2) {
			update_name(user_name); // change user's name
		}
		else if (choice == 3) {
			start_quiz(scores[quiz_id], q_count, quiz_questions, quiz_id); // start a new quiz
		}
		else if (choice == 4) {
			show_stats(scores, quiz_id, quiz_questions, exit); // show score statistics
			if (exit == 1) break;
		}
		else if (choice == 5) {
			show_scores(scores, quiz_id, quiz_questions, exit); // show previous scores
			if (exit == 1) break;
		}
		else if (choice == 6) { // exit
			break;
		}
	}
	cout << "Thank you for using our program" << endl;
	cout << "Exiting..." << endl;

	return 0;
}

void show_admin(int& q_count) { // q_count : number of questions in structs
	while (true) {
		string tempCHOICE; // temporary choice for user's input
		int choice = 0; // user's actual input

		cout << "Welcome to the administration menu, please choose from the following options: "
			<< endl; // print admin menu's text
		cout << " [1] View all questions" << endl;
		cout << " [2] Add new question" << endl;
		cout << " [3] Load questions from file" << endl;
		cout << " [4] Go back to main menu" << endl;
		cout << "My choice: ";
		getline(cin, tempCHOICE); // get user's input into temporary variable

		while (is_numeric(tempCHOICE) != 1) { // if the user's input isn't strictly numeric, ask for it again
			cout << "Please enter a number" << endl;
			getline(cin, tempCHOICE);
		}
		choice = char_to_int(tempCHOICE); // extract the numeric value into actual variable
		while (choice < 1 || choice > 4) { // if user's input is outside the range, ask for it again
			cout << "Please enter a correct option" << endl;
			getline(cin, tempCHOICE);
			while (is_numeric(tempCHOICE) != 1) { // check if input isn't strictly numeric, ask for it again
				cout << "Please enter a number" << endl;
				getline(cin, tempCHOICE);
			}
			choice = char_to_int(tempCHOICE);
		}

		if (choice == 1) {
			show_questions(q_count); // view all questions
		}
		else if (choice == 2) {
			add_question(q_count); // add a new question
		}
		else if (choice == 3) {
			load_file(q_count); // load questions from a file
		}
		else if (choice == 4) { // go back to main menu
			break;
		}
	}
}

void show_questions(int& q_count) { // q_count : number of questions in structs

	int valid = 0; // flag to check if user's input is valid

	if (q_count == 0) { // if the structs have no questions
		cout << "No questions found" << endl;
	}
	else {

		cout << "Number of questions available: " << q_count << endl; // otherwise print all questions
		cout << "Question list:" << endl;
		cout << "-------------------" << endl;
		for (int i = 0; i < q_count; i++) {
			cout << '[' << i + 1 << ']' << question[i].sentence << endl; // print the question itself preceeded by numbering
			for (int j = 0; j < 4; j++) { // print choices preceeded by the letters a b c d
				cout << '[' << (char)(97 + j) << ']' << question[i].choices[j] << ' '; // cast 97 to the letter 'a' and increment it
			}
			cout << endl << endl;
		}
		cout << '[' << q_count + 1 << ']' << " All questions" << endl; // option to delete all questions

		cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)" << endl;
		cout << "Press [b] if you want to go back to the admin menu" << endl;

		while (valid == 0) {
			valid = 1;
			string user_input; // variable for user's input
			getline(cin, user_input);

			if (user_input.length() == 1 && user_input == "b")
				cout << "Going back to admin menu..." << endl; // if user's input is 'b' go back to main
			else if (user_input.substr(0, 2) == "d ") { // else if user's input begins with letter 'd' followed by a space, otherwise print an error
				if (is_numeric(user_input.substr(2))) { // if the characters after the space are numeric, otherwise print an error
					int q_num = char_to_int(user_input.substr(2)); // extract those numbers
					if (q_num >= 1 &&
						q_num <= q_count + 1) { // if the numbers are within range, otherwise print an error
						if (q_num == q_count + 1) { // if the user chooses to delete all questions
							q_count = 0; // reset the question counter
							cout << "Deleted all questions" << endl;
						}
						else {
							for (int i = q_num - 1; i < q_count; i++) { // otherwise shift the questions back starting from the user's index
								question[i].sentence = question[i + 1].sentence; // shift the question
								for (int j = 0; j < 4; j++)
									question[i].choices[j] = question[i + 1].choices[j]; // shift the choices
							}
							q_count--; // decrease the question count
						}
						show_questions(q_count); // view all questions
					}
					else {
						cout << "Number out of bounds, please try again." << endl; // if user inputs number large than q_count+1
						valid = 0;
					}
				}
				else {
					cout << "Invalid question number, please try again." << endl; // if user inputs 'd ' followed by something other than a number
					valid = 0;
				}
			}
			else { // if the user doesn't input 'b' or 'd ##'
				cout << "Invalid input, please try again." << endl;
				valid = 0;
			}
		}
	}
}

int is_numeric(string variable)    // Check if a string contains only numbers (string's variable)
{
	int numeric = 1;    // Flag for whether the current character is a number
	for (int i = 0; variable[i] != '\0'; i++) {
		if (!isdigit(variable[i])) numeric = 0;     // If the ASCII of current character doesn't correspond to a number
	}
	return numeric;    // Return the value of the flag
}

int char_to_int(string variable)    // Cast an array of numbers to an integer(Numbers' array)
{
	int num = 0;
	size_t length = variable.length();    // Converted value, Length of the array of numbers
	for (unsigned int i = 0; i < length; i++) {
		int power = 1;
		for (unsigned int j = 0; j < length - (i + 1); j++) {    // Get the multiplier of the current place
			power *= 10;
		}
		num += (variable[i] - '0') * power;    // Add current's place value
	}
	return num;    // Return the converted value
}

void add_question(int& q_count) { // q_count : number of questions in structs

	string added_question, ch, tempCOUNTER; // user's question, temporary storage for user's input
	int counter = 0; // number of questions to add
	cout << "How many questions would you like to add? " << endl;
	getline(cin, tempCOUNTER);
	while (is_numeric(tempCOUNTER) != 1) { // if user's input isn't strictly numeric, ask for it again
		cout << "Please enter a number" << endl;
		getline(cin, tempCOUNTER);
	}
	counter = char_to_int(tempCOUNTER); // extract numeric value from tempCOUNTER string

	for (int i = 0; i < counter; i++) { // loop to add 'counter' questions
		cout << "Please enter question " << i + 1 << endl;
		getline(cin, added_question);
		question[q_count].sentence = added_question; // store user's question in the last struct
		cout << "Please enter the four answers\n(Put a '*' before the right one)" << endl;
		while (true) {
			int k = 0;
			int x = 1;
			for (int j = 0; j < 4; j++) { // loop to add 4 choices
				cout << "Please enter choice number " << j + 1 << endl;
				getline(cin, ch);
				if (ch[0] == '*') { // if the first character of a choice is a '*' store if in the first position of the array
					question[q_count].choices[0] = ch;
					k++; // increase the counter of correct answers
				}
				else { // otherwise add the choice at the index x and increment x
					question[q_count].choices[x++] = ch;
				}
			}
			if (k != 1) { // if there's more or less than 1 correct answers preceeded by a '*', ask for choices again
				cout << "Please mark one correct answer by a '*'" << endl;
				continue;
			}
			break;
		}
		q_count++; // increase number of stored questions
	}
	if (counter == 0) cout << "No questions added" << endl; // if the user chooses not to enter any questions
	else cout << counter << " questions added successfully" << endl; // number of questions added after the loop
}

void load_file(int& q_count) { // q_count : number of questions in structs

	string questions_file; // name of the file to be opened
	int exit = 0; // flag to cancel loading questions from file
	cout << "Please enter the name of the file you'd like to open" << endl;
	cout << "(Please enter the full path to the file, or make sure the file is in the same folder as the program)" << endl;
	getline(cin, questions_file); // get full path to the file
	if (questions_file[0] == '"' && questions_file[questions_file.length() - 1] == '"') // if the input contains quotation marks, remove them
		questions_file = questions_file.substr(1, questions_file.length() - 2);
	ifstream file;
	file.open(questions_file); // open the file
	while (file.fail()) { // as long as the file can't be found/opened, keep askin for another one
		cout << "Could not open file, please try again" << endl;
		cout << "(Enter b to stop)" << endl;
		getline(cin, questions_file);
		if (questions_file[0] == '"' && questions_file[questions_file.length() - 1] == '"') // remove quotation marks from input
			questions_file = questions_file.substr(1, questions_file.length() - 2);
		file.open(questions_file); // try to open the file
		if (questions_file.length() == 1 && questions_file[0] == 'b') { // if the user inputs 'b', set the exit flag to 1 and break the loop
			exit = 1;
			break;
		}
	}
	if (exit == 0) { // if the user didn't choose to stop loading a file

		for (int i = q_count; !file.eof(); i++) { // add questions starting from q_count as long as end of the file hasn't been reached

			int k = 1, found = 0; // index for other choices, index for correct choice
			getline(file, question[i].sentence); // store the question
			for (int j = 0; j < 4; j++) { // store the 4 choices
				string choice;
				getline(file, choice); // read the choice
				if (choice[0] == '*') { // if the first character of the choice is a '*'
					if (found == 0) { // if no correct choices were found, store this one in the first index
						question[i].choices[found] = choice;
						found++; // increment the found index
					}
					else { // if a correct choice was already found, store choice minus the '*' at k and increment k
						question[i].choices[k++] = choice.substr(1);
					}
				}
				else { // if the choice doesn't begin with a '*'
					if (question[i].choices[0].length() == 0 && k == 4) { // if no correct choice has been stored
						for (int x = 0; x < 3; x++) { // shift the choices back
							question[i].choices[x] = question[i].choices[x + 1];
						}
						question[i].choices[3] = choice; // store the last choice at the end of the array
					}
					else {
						question[i].choices[k++] = choice; // otherwise store the choice at k and increment k
					}
				}
			}
			q_count++; // increase the number of questions in struct

		}
		cout << "File loaded successfully." << endl;
		file.close(); // close the file
	}
	else {
		cout << "Cancelled file open" << endl; // if the user chooses not to open a file
	}
}

void update_name(string& user_name) { // user_name : variable in main to store user's name

	string name; // temporary storage for user's name
	cout << "Update user's name" << endl;
	cout << "Please enter a name you'd like to use:" << endl;
	getline(cin, name);

	while (true) {
		bool invalid = false; // flag to check for invalid name
		for (int i = 0; name[i] != '\0'; i++) {
			if (isalpha(name[i]) == 0 && name[i] != 32) { // make sure name contains only letters and spaces
				invalid = true;
				break;
			}
		}
		if (!invalid) { // if the name contains no illegal characters
			user_name = name; // store it in the main variable
			cout << "Name changed successfully!" << endl;
			cout << "User's current name is: " << user_name << endl; // output the new name
			break;
		}
		else {
			cout << "Please enter a valid name:" << endl; // if the name contains illegal characters, ask for it again
			getline(cin, name);
		}
	}
}

void start_quiz(int& score, int q_count, int quiz_questions, int& quiz_id) {
	// score : current quiz's score, q_count : number of questions in structs
	// quiz_questions : number of questions per quiz, quiz_id : index of current quiz
	if (q_count < quiz_questions)
		cout << "Not enough questions found" << endl; // can't start a quiz with questions in struct less than quiz_questions
	else {
		score = 0; // initialize the score for current quiz to 0
		int* n; // pointer to store random numbers for questions
		string user_input; // temporary storage for user's choice
		n = randomnumbers(q_count - 1, quiz_questions); // point to array returned by gen_ranInt
		cout << "Welcome to your quiz" << endl;
		for (int i = 0; i < quiz_questions; i++) { // loop to print number of questions per quiz
			cout << '[' << i + 1 << ']' << question[n[i]].sentence << endl; // print a number then the question
			int* m; // pointer to store random numbers for choices
			m = randomnumbers(3, 4); // point to array returned by gen_ranInt
			for (int j = 0; j < 4; j++) { // cast 97 to 'a' and increment by j to bring b c d
				cout << '[' << (char)(97 + j) << ']';
				if (question[n[i]].choices[m[j]][0] == '*') { // exclude the '*' before printing the choice if it exists
					cout << question[n[i]].choices[m[j]].substr(1) << ' ';
				}
				else
					cout << question[n[i]].choices[m[j]] << ' ';
			}
			cout << endl; // print a new line after printing choices
			getline(cin, user_input); // get user's choice
			bool isValid = // if user's choice isn't within {a,b,c,d} (upper or lower case)
				(user_input[0] >= 97 && user_input[0] <= 100) || (user_input[0] >= 65 && user_input[0] <= 68);
			while (user_input.length() != 1 ||
				!isValid) { // if the user didn't input one character or the user entered an invalid character
				cout << "Invalid choice, please try again" << endl;
				getline(cin, user_input);
				isValid = // recheck for validity of the character
					(user_input[0] >= 97 && user_input[0] <= 100) || (user_input[0] >= 65 && user_input[0] <= 68);
			}
			int userChoice_index = (int)(user_input[0] - 97); // get the index of the letter entered by the user {a:0, b:1, c:2, d:3}
			if (user_input[0] < 97)
				userChoice_index += 32; // get the index of the letter entered if it's an uppercase one
			if (question[n[i]].choices[m[userChoice_index]] == question[n[i]].choices[0])
				score++; // if the user's choice matches the first choice in the choices array, count as a correct answer
		}
		cout << "Quiz is over" << endl;
		cout << "Your score for this quiz is: " << score << " out of " << quiz_questions << endl; // output the score for each quiz
		quiz_id++; // increment the id of the quiz
	}
}

void show_stats(int* scores, int numofQuizzes, int quiz_questions, int& exit) {
	// scores : array storing scores for all quizzes, numofQuizzes : number of quizzes taken
	// quiz_questions : number of questions per quiz, exit : flag to go to main menu
	if (numofQuizzes == 0)
		cout << "No statistics to show yet" << endl; // if no quizzes were taken, no stats would be pretended
	else {
		string user_choice; // user's input to go back to main menu or exit
		int max_score = scores[0]; // set highest score to first score in the array
		int min_score = scores[0]; // set lowest score to first score in the array
		float average_score = 0; // sum of all scores to calculate the average
		for (int i = 0; i < numofQuizzes; i++) { // go over all scores to find lowest, highest and sum of all scores
			if (scores[i] > max_score) max_score = scores[i];
			if (scores[i] < min_score) min_score = scores[i];
			average_score += scores[i];
		}
		average_score /= numofQuizzes; // set average score to sum of all scores over number of quizzes
		cout << "Your score statistics:" << endl; // print the statistics
		cout << "Number of quizzes taken: " << numofQuizzes << endl;
		cout << "Your highest score: " << max_score << " out of " << quiz_questions << endl;
		cout << "Your lowest score: " << min_score << " out of " << quiz_questions << endl;
		cout << "Your average score: " << average_score << " out of " << quiz_questions << endl;
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		cout << "My choice: " << endl;
		getline(cin, user_choice); // get user's choice, either b or e
		while (user_choice.length() != 1 || (user_choice[0] != 'e' && user_choice[0] != 'b')) { // b goes back to main menu, e exits the program
			cout << "Invalid choice, please try again..." << endl;
			getline(cin, user_choice); // get user's choice again
		}
		if (user_choice[0] == 'e') exit = 1; // set exit flag in main function to 1 to exit program
	}
}

void show_scores(int* scores, int numofQuizzes, int quiz_questions, int& exit) {
	// scores : array storing scores for all quizzes, numofQuizzes : number of quizzes taken
	// quiz_questions : number of questions per quiz, exit : flag to go to main menu
	if (numofQuizzes == 0) cout << "No scores to show yet" << endl;
	else {
		string user_choice; // user's input to go back to main menu or exit
		cout << "Total quizzes taken: " << numofQuizzes << endl; // print scores text
		for (int i = 0; i < numofQuizzes; i++) {
			cout << "Quiz " << i + 1 << " : " << endl; // print number of each quiz
			cout << "Right answers: " << scores[i] << endl; // number of right answers for the quiz is the same as the score for that quiz
			cout << "Wrong answers: " << quiz_questions - scores[i] << endl; // number of wrong answers for this quiz is right answers subtractd from total number of questions per quiz
			cout << "Score: " << scores[i] << " out of " << quiz_questions << endl;
		}
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		cout << "My choice: " << endl;
		getline(cin, user_choice); // get user's choice, either b or e
		while (user_choice.length() != 1 || (user_choice[0] != 'e' && user_choice[0] != 'b')) { // b goes back to main menu, e exits the program
			cout << "Invalid choice, please try again..." << endl;
			getline(cin, user_choice); // get user's choice again
		}
		if (user_choice[0] == 'e') exit = 1; // set exit flag in main function to 1 to exit program
	}
}

int* randomnumbers(int last, int numofInt) {
	// return an array with "numofInt" random numbers in the range [0, last]
	int* rand_nums; // create a pointer
	int i = 0; // create a counter
	rand_nums = new int[numofInt]; // create a dynamic array whose size is numofInt
	srand((unsigned)(time(nullptr) + rand())); // change the seed everytime the function is called
	// (time to change seed from run to run, rand to change the seed from call to call)
	while (i < numofInt) { // iterate for a number of numofInt
		int exists = 0; // flag to make sure the random number doesn't duplicate
		rand_nums[i] = rand() % (last + 1); // generate the random number
		// rand() % last generates a number between 0 and 'last-1'
		// rand() % last + first : shifts them by 'first' to become from 1 till 'last'
		// rand() % (last + 1) + first : (last + 1) to make it inclusive of last
		for (int j = 0; j < i; j++) { // check if the generated number exists
			if (rand_nums[i] == rand_nums[j]) {
				exists = 1;
				break;
			}
		}
		if (exists == 0) i++; // if it hasn't been found, increment i, otherwise, generate another one
	}
	return rand_nums;
}