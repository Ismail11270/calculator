#include "RPN.h"
#include "Calculator.h"


#pragma warning(disable:4996)

using namespace sf;

void testRpn();


int main()
{
	
	RenderWindow window(VideoMode(800,300), "Calculator");
	bool inMainMenu = true;
	Font font;
	font.loadFromFile("fonts/AGENCYB.TTF");
	
	Calculator calculator = Calculator();
	calculator.run(&window,font);

	system("PAUSE");
	/*CircleShape circle;
	circle.setRadius(100);
	//circle.setPosition(0, 0);
	circle.setFillColor(Color::Red);
	CircleShape circle1;
	circle1.setRadius(100);
	circle1.setPosition(1000, 300);
	circle1.setFillColor(Color::Red);
	CircleShape circle2;
	circle2.setRadius(100);
	circle2.setPosition(500, 600);
	circle2.setFillColor(Color::Red);
	CircleShape circle3;
	circle3.setRadius(100);
	circle3.setPosition(900,100);
	circle3.setFillColor(Color::Red);
	View view;
	view.setCenter(0, 0);
	view.setSize(10000, 10000);
	window.setView(view);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			event.
		}
		/*if (Keyboard::(Keyboard::Up)) {
			view.move({ 0,10});
			cout << " fff" << endl;
			sleep(microseconds(100));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			view.move({ 0,-10});
			cout << " down" << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			view.move({ -10,0});
			cout << " left" << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			view.move({ 10,0});
			cout << " right" << endl;
		}
		window.clear();
		window.draw(circle);

		window.display();

	}
	*/
	return 0;
}


void testRpn() {
	RPN rpn;
	char *s = "5^(3+2)/2";
	char *d = "5*x^2-5*x";
	cout << rpn.evaluate(s) << "bye" << endl;

	cout << rpn.evaluate(rpn.infixToPostfix(s)) << "hi" << endl;

	rpn.printRPN(rpn.infixToPostfix(d));

	cout << rpn.evaluate(rpn.infixToPostfix(d), 3) << endl;

	cout << rpn.evaluate(d, 3) << endl;

	vector<double> xx = rpn.evaluate(d, 0, 10, 1);
	cout << xx[3] << endl;
}