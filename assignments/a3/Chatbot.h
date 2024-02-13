// Chatbot.h

//
// Don't make any modifications to this file!
//

#pragma once // prevent multiple inclusion of this file

#include <iostream>
#include <string>

using namespace std;

class Chatbot
{
public:
	// returns the name of this chatbot
	virtual string name() const = 0;

	// gives a string to this chatbot
	virtual void give_to(const string &s) = 0;

	// gets a string from this chatbot
	virtual string get_from() = 0;

	// virtual destructor
	virtual ~Chatbot() {}

}; // class Chatbot

//
// Run a conversation between two chatbots. Chatbot a always speaks first.
//
void converse(Chatbot *a, Chatbot *b, int max_turns = 10)
{
	cout << "Conversation between "
		 << a->name() << " and " << b->name()
		 << ", " << max_turns << " turns\n\n";

	for (int turn = 1; turn <= max_turns; turn++)
	{
		string a_utterance = a->get_from();
		cout << a->name() << " " << turn << "> " << a_utterance << "\n";

		b->give_to(a_utterance);
		string b_utterance = b->get_from();
		cout << b->name() << " " << turn << "> " << b_utterance << "\n\n";

		a->give_to(b_utterance);
	} // for

	cout << "Conversation ended: max=" << max_turns << " turns reached\n";
}
