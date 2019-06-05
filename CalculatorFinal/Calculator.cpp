#include "Calculator.h"
#include <vector>

using namespace sf;

void Calculator::run()
{
	char option; 
	while (active)
	{
		printMenu();
		bool repeat;
		Sleep(200);
		option = _getch();
		if (tolower(option) == 'a')
		{
			do {
				repeat = false;
				char a = simpleExpressionEvaluation();
				a = tolower(a);
				if (a == 'm') {
					running = false;
				}
				else if (a == 'q') {
					exit(0);
				}
				else
				{
					repeat = true;
					system("CLS");
				}
			} while (repeat);
		}
		else if (tolower(option) == 'b') 
		{
			do {
				repeat = false;
				char a = 'a';//evaluateFunction();
				a = tolower(a);
				if (a == 'm') {
					running = false;
				}
				else if (a == 'q') {
					exit(0);
				}
				else
				{
					repeat = true;
					system("CLS");
				}
			} while (repeat);
			//evaluateFunction();
			//running = false;
		}
		else if (tolower(option) == 'c')
		{
			do {
				repeat = false;
				char a = 'a';// plotFunction();
				a = tolower(a);
				if (a == 'm') {
					running = false;
				}
				else if (a == 'q') {
					exit(0);
				}
				else
				{
					repeat = true;
					system("CLS");
				}
			} while (repeat);
		}
		else if (tolower(option) == 'm')
		{
			printManual();
		}
		else if (tolower(option) == 'q')
		{
			exit(0);
		}
	}

}

char Calculator::simpleExpressionEvaluation() {
	return 'a';
}
void Calculator::run(sf::RenderWindow *window, Font font)
{
	RectangleShape inputField;
	inputField.setSize({ (float)(window->getSize().x - 2 * (window->getSize().x / 30)), (float)(window->getSize().y / 5) });
	inputField.setPosition(window->getSize().x / 30, inputField.getSize().y);
	Text userInput;
	userInput.setFont(font);
	userInput.setFillColor(Color::Black);
	userInput.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 10);
	userInput.setCharacterSize(30);
	Text evaluate;
	evaluate.setString("  Evaluate\nExpression");
	evaluate.setPosition(50, 150);
	evaluate.setFont(font);
	evaluate.setFillColor(Color::White);
	Text evaluateForX;
	evaluateForX.setString("Evaluate\nFunction");
	evaluateForX.setFont(font);
	evaluateForX.setFillColor(Color::White);
	evaluateForX.setPosition(250, 150);
	Text plotFunctionButton;
	plotFunctionButton.setString("  Plot\nFunction");
	plotFunctionButton.setFont(font);
	plotFunctionButton.setFillColor(Color::White);
	plotFunctionButton.setPosition(450, 150);
	Text manual;
	manual.setString("  Manual");
	manual.setFont(font);
	manual.setFillColor(Color::White);
	manual.setPosition(650, 160);
	Text errorMessage;
	errorMessage.setFont(font);
	errorMessage.setFillColor(Color::Red);
	errorMessage.setPosition(0, window->getSize().y / 2);
	Text enterXMessage;
	enterXMessage.setFont(font);
	enterXMessage.setFillColor(Color::Red);
	enterXMessage.setPosition(0, window->getSize().y / 2);
	Text enterRangeMessage;
	enterRangeMessage.setFont(font);
	enterRangeMessage.setFillColor(Color::Red);
	enterRangeMessage.setPosition(0, window->getSize().y / 2);
	bool canEnterExpression = true;
	std::string userInputString;
	unsigned stage = 1;    //1 - main menu, 2 - result screen, 3 error screen
	while (window->isOpen())
	{
		if (stage == 1)
		{
			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window->close();
				}
				if (event.type == Event::Resized)
				{
					cout << "New window size - " << event.size.width << ":" << event.size.height << endl;
				}
				if (event.type == Event::TextEntered)
				{
					if (userInput.getLocalBounds().width <= window->getSize().x - window->getSize().x / 30 - 40 && canEnterExpression == true)
					{
						if (event.text.unicode > 33 && event.text.unicode < 126)
						{
							userInputString += (char)event.text.unicode;
						}
						else if (event.text.unicode == 8)
						{
							userInputString = userInputString.substr(0, userInputString.length() - 1);
						}
						userInput.setString(userInputString);
						cout << userInputString << endl;
						cout << userInput.getLocalBounds().width << endl;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace) && canEnterExpression == false)
				{
					canEnterExpression = true;
					userInputString = "";
				}
				if (event.type == event.MouseButtonPressed && canEnterExpression == true) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						//if evaluate pressed
						int x = event.mouseButton.x;
						int y = event.mouseButton.y;
						if (x >= evaluate.getGlobalBounds().left &&
							x <= (evaluate.getGlobalBounds().left + evaluate.getGlobalBounds().width) &&
							y >= evaluate.getGlobalBounds().top &&
							y <= evaluate.getGlobalBounds().top + evaluate.getGlobalBounds().height)
						{
							char tab2[1024];
							strncpy(tab2, userInputString.c_str(), sizeof(tab2));
							tab2[sizeof(tab2) - 1] = 0;
							try {
								double a = simpleExpressionEvaluation(tab2);

								userInputString += "=";
								userInputString += to_string(a);
								userInput.setString(userInputString);
								canEnterExpression = false;
							}
							catch (char *msg)
							{

								window->clear();
								string str = msg;
								str += "\nPress Space to Continue";
								errorMessage.setString(str);
								window->draw(errorMessage);
								window->display();
								while (!Keyboard::isKeyPressed(Keyboard::Space))
								{

								}
								userInputString = "";
							}
							catch (exception e)
							{
								window->clear();
								string str = e.what();
								str += "\nPress Space to Continue";
								errorMessage.setString(str);
								window->draw(errorMessage);
								window->display();
								while (!Keyboard::isKeyPressed(Keyboard::Space))
								{

								}
								userInputString = "";
							}
							cout << "Evaluate pressed\n";
						}
						//if evaluate function pressed
						else if (x >= evaluateForX.getGlobalBounds().left &&
							x <= (evaluateForX.getGlobalBounds().left + evaluateForX.getGlobalBounds().width) &&
							y >= evaluateForX.getGlobalBounds().top &&
							y <= evaluateForX.getGlobalBounds().top + evaluateForX.getGlobalBounds().height)
						{
							cout << "evaluateForX pressed\n";
							double x = 0;
							string x_ = "";
							char tab2[1024];
							strncpy(tab2, userInputString.c_str(), sizeof(tab2));
							tab2[sizeof(tab2) - 1] = 0;
							userInput.setString(x_);
							try {
								evaluateFunction(tab2, 0);
							}
							catch (char *msg)
							{
								while (!Keyboard::isKeyPressed(Keyboard::Space))
								{
									cout << "ERRRORORORORROR\n";
									window->clear();
									string str = msg;
									str += "\nPress SPACE to Continue";
									errorMessage.setString(str);
									window->draw(errorMessage);
									window->display();
								}
								userInputString = "";
								break;
							}
							while (!Keyboard::isKeyPressed(Keyboard::Return)) {
								enterXMessage.setString("Enter the value of X:");

								Event event1;
								while (window->pollEvent(event1)) {
									if (event1.type == Event::Closed)
									{
										window->close();
									}
									if (event1.type == Event::Resized)
									{
										cout << "New window size - " << event1.size.width << ":" << event1.size.height << endl;
									}
									if (event1.type == Event::TextEntered)
									{
										if ((event1.text.unicode >= 48 && event1.text.unicode <= 57) || event1.text.unicode == 46)
										{
											x_ += (char)event1.text.unicode;
											userInput.setString(x_);
										}
										else if (event1.text.unicode == 8)
										{
											userInputString = userInputString.substr(0, userInputString.length() - 1);
											userInput.setString(x_);
										}
									}
								}
								window->clear();
								window->draw(enterXMessage);
								window->draw(inputField);
								window->draw(userInput);
								window->display();
							}

							x = stod(x_);
							try {
								double a = evaluateFunction(tab2, x);
								string input__ = userInputString;
								userInputString = "y(x) = ";
								userInputString += input__;
								userInputString = userInputString + ", y(" + x_ + ") = " + to_string(a);
								userInput.setString(userInputString);
								canEnterExpression = false;
							}
							catch (char *msg)
							{
								while (!Keyboard::isKeyPressed(Keyboard::Space))
								{
									cout << "ERRRORORORORROR\n";
									window->clear();
									string str = msg;
									str += "\nPress SPACE to Continue";
									errorMessage.setString(str);
									window->draw(errorMessage);
									window->display();
								}
								userInputString = "";
							}


						}
						//plotting function pressed
						else if (x >= plotFunctionButton.getGlobalBounds().left &&
							x <= (plotFunctionButton.getGlobalBounds().left + plotFunctionButton.getGlobalBounds().width) &&
							y >= plotFunctionButton.getGlobalBounds().top &&
							y <= plotFunctionButton.getGlobalBounds().top + plotFunctionButton.getGlobalBounds().height)
						{
							double step_ = 0;
							string step = "";
							string range = "";
							char input[1024];
							strncpy(input, userInputString.c_str(), sizeof(input));
							input[sizeof(input) - 1] = 0;
							try {
								evaluateFunction(input, 0);
							}
							catch (char *msg)
							{
								while (!Keyboard::isKeyPressed(Keyboard::Space))
								{
									cout << "ERRRORORORORROR\n";
									window->clear();
									string str = msg;
									str += "\nPress SPACE to Continue";
									errorMessage.setString(str);
									window->draw(errorMessage);
									window->display();
								}
								userInputString = "";
								break;
							}
							userInput.setString("");
							while (!Keyboard::isKeyPressed(Keyboard::Return)) {
								
								enterXMessage.setString("Enter the range of X - (lower,upper):");

								Event event1;
								while (window->pollEvent(event1)) {
									if (event1.type == Event::Closed)
									{
										window->close();
									}
									if (event1.type == Event::Resized)
									{
										cout << "New window size - " << event1.size.width << ":" << event1.size.height << endl;
									}
									if (event1.type == Event::TextEntered)
									{
										if ((event1.text.unicode >= 48 && event1.text.unicode <= 57) || event1.text.unicode == 46 || event1.text.unicode == 44 || event1.text.unicode == 40 || event1.text.unicode == 41 || event1.text.unicode == 45)
										{
											range += (char)event1.text.unicode;
											userInput.setString(range);
										}
										else if (event1.text.unicode == 8)
										{
											range = range.substr(0, range.length() - 1);
											userInput.setString(range);
										}
									}
								}
								window->clear();
								window->draw(enterXMessage);
								window->draw(inputField);
								window->draw(userInput);
								window->display();
							}
							userInput.setString("");
							sleep(milliseconds(1000));
							while (!Keyboard::isKeyPressed(Keyboard::Return)) {
								enterXMessage.setString("Enter the step of X:");

								Event event1;
								while (window->pollEvent(event1)) {
									if (event1.type == Event::Closed)
									{
										window->close();
									}
									if (event1.type == Event::Resized)
									{
										cout << "New window size - " << event1.size.width << ":" << event1.size.height << endl;
									}
									if (event1.type == Event::TextEntered)
									{
										if ((event1.text.unicode >= 48 && event1.text.unicode <= 57) || event1.text.unicode == 46)
										{
											step += (char)event1.text.unicode;
											userInput.setString(step);
										}
										else if (event1.text.unicode == 8)
										{
											step = range.substr(0, step.length() - 1);
											userInput.setString(step);
										}
									}
								}
								window->clear();
								window->draw(enterXMessage);
								window->draw(inputField);
								window->draw(userInput);
								window->display();
							}
							cout << range << " " << step << endl;
							step_ = stod(step);
								try {
									plotFunction(input, range, step_);
									//string input__ = userInputString;
								//	userInputString = "y(x) = ";
								//	userInputString += input__;
								//	userInputString = userInputString + ", y(" + x_ + ") = " + to_string(a);
								//	userInput.setString(userInputString);
									canEnterExpression = false;
								}
								catch (char *msg)
								{
									while (!Keyboard::isKeyPressed(Keyboard::Space))
									{
										cout << "ERRRORORORORROR\n";
										window->clear();
										string str = msg;
										str += "\nPress SPACE to Continue";
										errorMessage.setString(str);
										window->draw(errorMessage);
										window->display();
									}
									userInputString = "";
								}
								catch (exception e)
								{
									while (!Keyboard::isKeyPressed(Keyboard::Space))
									{
										cout << "ERRRORORORORROR\n";
										window->clear();
										string str = e.what();
										str += "\nPress SPACE to Continue";
										errorMessage.setString(str);
										window->draw(errorMessage);
										window->display();
									}
									userInputString = "";
								}


						}
						else if (x >= manual.getGlobalBounds().left &&
							x <= (manual.getGlobalBounds().left + manual.getGlobalBounds().width) &&
							y >= manual.getGlobalBounds().top &&
							y <= manual.getGlobalBounds().top + manual.getGlobalBounds().height)
						{
							cout << "manual pressed\n";
							int a = system("start docs/Manual.txt");
						}
					}
				}

			}
			window->clear();

			window->draw(inputField);
			window->draw(userInput);
			window->draw(evaluate);
			window->draw(evaluateForX);
			window->draw(plotFunctionButton);
			window->draw(manual);
			//cout << inputField.getPosition().x << " " << inputField.getPosition().y << endl;
			window->display();
		}
	}
}


double Calculator::simpleExpressionEvaluation(char *input_)
{
	system("CLS");
	char *input = input_;
	vector<Token> rpnResult;
	//cout << "Enter an expression to evaluate: \n";
	//cin >> input;
	double result;

	try {
		result = rpn.evaluate(input);
		cout << input << " = " << result << endl;
		return result;
	}
	catch (char *msg)
	{
		throw msg;
	}

	
}

double Calculator::evaluateFunction(char *input_, double x)
{
	system("CLS");
	char *input = input_;
	double result;
	try {
		result = rpn.evaluate(input, x);
		cout << "y(x)=" << input << endl;
		cout << "y(" << x << ")=" << result << endl;
		return result;
	}
	catch (char *msg) {
		throw msg;
	}
	
}

void Calculator::plotFunction(char *input_, string range, double step)
{
	double xLower;
	double xUpper;
	char *input = input_;
	
	char in[30];
	strncpy(in, range.c_str(), sizeof(range));
	in[sizeof(in) - 1] = 0;
	bool wrong = true;
	while (wrong)
	{
		char *p = in;
		char temp;
		int n;
		if (in[0] == '(') {
			p++;
		}
		else
		{
			throw "Wrong range format! Type in as (a,b) !";
		}
		if (int k = sscanf(p, "%lf%n", &xLower, &n) > 0) {
			p += n;
			if (k = sscanf(p, "%c", &temp) > 0 && temp == ',') {
				p++;
				if (k = sscanf(p, "%lf", &xUpper) > 0) {
					wrong = false;
				}
				else
				{
					throw "Wrong range format! Type in as (a,b) !";
				}
			}
			else
			{
				throw "Wrong range format! Type in as (a,b) !";
			}
		}
		else {
			throw "Wrong range format! Type in as (a,b) !";
		}
		if (xLower >= xUpper) {
			throw "Wrong upper and lower limits. (Equal or upper less than lower.";
		}
	}
	vector<double> result;
	vector<double> stepVec;
	vector<CircleShape> points;
	try {
		result = rpn.evaluate(input, xLower, xUpper, step);
		cout << "y(x)=" << input << endl;
		stepVec = rpn.getStepVec(xLower, xUpper, step);
		points.resize(result.size());
		for (int i = 0; i < result.size(); i++) {
			cout << "y(" << stepVec[i] << ")=" << result[i] << endl;
			points[i].setRadius(2);
			points[i].setFillColor(Color::White);
			points[i].setPosition({ (float)stepVec[i],(float)result[i] });
		}
	}
	catch (char *msg) {
		throw msg;
	}
	catch (exception e)
	{
		throw e;
	}
	
	string streng = "Plot of y(x) = ";
	streng += (string)input;
	
	RenderWindow plotWindow(VideoMode(500, 500), streng, Style::Resize | Style::Close | Style::Titlebar);

	RectangleShape xAxis;
	RectangleShape yAxis;

	xAxis.setFillColor(Color::White);
	yAxis.setFillColor(Color::White);
	xAxis.setSize({ 10000,2 });
	xAxis.setPosition(-xAxis.getSize().x / 2, 0);
	yAxis.setSize({ 2,10000 });
	yAxis.setPosition(0 - 2, -yAxis.getSize().y / 2);
	View view;
	view.setCenter(0, 0);
	view.setSize(1000, 1000);
	view.rotate(180);
	
	plotWindow.setView(view);
	
	while (plotWindow.isOpen())
	{
		Event event2;
		while (plotWindow.pollEvent(event2)) {
			if (event2.type == Event::Closed)
			{
				plotWindow.close();
			}
			//if(event2.type == Event::MouseMoveEvent(Mouse::)
		}
		plotWindow.clear();
		for (int i = 0; i < points.size(); i++) {
			plotWindow.draw(points[i]);
		}
		plotWindow.draw(xAxis);
		plotWindow.draw(yAxis);
		plotWindow.display();
		
	}
	
}
void Calculator::printMenu()
{
	if (!running)
	{
		system("CLS");
		cout << menuPrinter;
		running = true;
	}
}
void Calculator::printManual()
{
	system("cls");
	cout << manualPrinter << endl << endl;
	cout << "\nPress any key to continue...";
	_getch();
	running = false;
}
Calculator::Calculator()
{
	running = false;
	active = true;
}
Calculator::~Calculator()
{	
}