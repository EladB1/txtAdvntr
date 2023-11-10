#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "yaml-cpp/yaml.h"
#include "prompt.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::isdigit;
using std::stoi;

typedef enum gameState {
	WIN,
	LOSS,
	InProgress
} GameState;

string prompt(string text) {
	string answer;
	cout << text << ": ";
	cin >> answer;
	cout << endl;
	return answer;
}

bool is_number(string answer) {
	string::const_iterator it = answer.begin();
	while (it != answer.end() && isdigit(*it)) {
		++it;
	}
	return !answer.empty() && it == answer.end();
}

bool is_valid_answer(string answer, int num_choices) {
	if (!is_number(answer))
		return false;
	int numeric_answer = stoi(answer);
	if (numeric_answer < 1 || numeric_answer > num_choices)
		return false;
	return true; 
}

int multipleChoice_prompt(Prompt prompt) {
	cout << prompt.getText() << endl;
	string answer;
	int i;
	for (i = 0; i < prompt.getChoices().size(); i++) {
		cout << i + 1 << ". " << prompt.getChoices()[i].getText() << endl;
	}
	cout << "Your answer: ";
        cin >> answer;
	while (!is_valid_answer(answer, prompt.getChoices().size())) {
		cout << "'" << answer << "' is not a valid answer." << endl;
		cout << "Your answer: ";
		cin >> answer;
		cout << endl;
	}
	return stoi(answer);
}

void game_loop() {
	GameState state = InProgress;
	string promptsDirectory = "prompts";
	string file = "start.yml";
	Prompt prompt;
	YAML::Node content;
	int answer;
	vector<Choice> choices;
	while (state == InProgress) {
		content = YAML::LoadFile(promptsDirectory + "/" + file);
		prompt = Prompt(content);
		choices = prompt.getChoices();
		answer = multipleChoice_prompt(prompt);
		if (choices[answer-1].getResult() == "win")
			state = WIN;
		else if (choices[answer-1].getResult() == "loss")
			state = LOSS;
		else {
			file = choices[answer-1].getResult();
		}
	}
	if (choices[answer-1].getAdditionalText() != "")
		cout << choices[answer-1].getAdditionalText() << endl;
	if (state == WIN)
		cout << "Congratulations! You win!!!" << endl;
	else
		cout << "You lost!" << endl;
}

int main(int argc, char **argv) {
	cout << "Hello" << endl;
	game_loop();
	return 0;
}
