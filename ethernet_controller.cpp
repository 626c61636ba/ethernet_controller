#include <iostream>
#include <string>
#include <windows.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void menu();
void change_interface_status();
void commando_mode();
void change_status(std::string net_interface, std::string cmd);

int main()
{
	menu();
	return 0;
}

void menu() {
	std::string input = "0";

	while (input.at(0) != '3') {
		std::cout << "Select an option:\n";
		std::cout << "1 - Change interface status\n";
		std::cout << "2 - commando mode\n";
		std::cout << "3 - exit\n";

		do{
			std::getline(std::cin, input);
		} while (input.empty());

		system(CLEAR);

		switch (input.at(0))
		{
		case '1':
			change_interface_status();
			break;
		case '2':
			commando_mode();
			break;
		default:
			break;
		}
		system(CLEAR);
	}
}


void change_interface_status() {
	int int_cmd;
	std::string net_interface, cmd, input;

	std::cout << "These are the available interfaces:\n";

	system("netsh.exe interface show interface");

	std::cout << "Enter the interface name: ";

	std::getline(std::cin, net_interface);

	std::cout << "1 - enable, 2 - disable: ";

	std::getline(std::cin, input);
	int_cmd = input.at(0);

	switch (int_cmd)
	{
	case 1:
		cmd = "enable";
		break;
	case 2:
		cmd = "disable";
		break;
	default:
		return;
	}

	change_status(net_interface, cmd);
}


void commando_mode() {
	std::string net_interface;

	std::cout << "These are the available interfaces:\n";

	system("netsh.exe interface show interface");

	std::cout << "Enter the interface name(default=Ethernet): ";

	std::getline(std::cin, net_interface);

	if (net_interface.empty()) {
		net_interface = "Ethernet";
	}

	while (!(GetAsyncKeyState(VK_F3) & 0x01)) {
		if ((GetAsyncKeyState(VK_F1) & 0x01))
		{
			change_status(net_interface, "enable");
			std::cout << net_interface + " enabled!\n";
			std::cout << '\a';
		}

		if ((GetAsyncKeyState(VK_F2) & 0x01))
		{
			change_status(net_interface, "disable");
			std::cout << net_interface + " disabled!\n";
			std::cout << '\a';
		}
	}
}

void change_status(std::string net_interface, std::string cmd) {
	std::string netsh_cmd = "netsh.exe interface set interface \"";
	net_interface.append("\" ");

	system((netsh_cmd + net_interface + cmd).c_str());
}