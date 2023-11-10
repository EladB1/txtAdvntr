#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

using std::string;
using std::vector;

class Choice {
	private:
		string text;
		string result;
		string additionalText;
	public:
		Choice(string text, string result) {
			this->text = text;
			this->result = result;
			this->additionalText = "";
		}

		Choice(string text, string result, string additionalText) {
			this->text = text;
			this->result = result;
			this->additionalText = additionalText;
		}

		string getText() {
			return text;
		}

		string getResult() {
			return result;
		}

		string getAdditionalText() {
			return additionalText;
		}
};

class Prompt {
	private:
		string text;
		vector<Choice> choices;
	public:
		Prompt() {
			this->text = "";
		}
		Prompt(string text, vector<Choice> choices) {
			this->text = text;
			this->choices = choices;
		}

		Prompt(YAML::Node fileContents) {
			if (fileContents["prompt"] && fileContents["choices"]) {
				this->text = fileContents["prompt"].as<string>();
				for (auto choice : fileContents["choices"]) {
					choice["additionalText"] ?
					this->choices.push_back(Choice(choice["text"].as<string>(), choice["result"].as<string>(), choice["additionalText"].as<string>())) :
					this->choices.push_back(Choice(choice["text"].as<string>(), choice["result"].as<string>()));
				}
			}
			else
				throw std::invalid_argument("Improperly formatted YAML file");
		}
		
		string getText() {
			return text;
		}

		vector<Choice> getChoices() {
			return choices;
		}
};
