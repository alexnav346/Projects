#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int hexToInteger(char number)
{
	int temp = 0;

	switch (number) {
	case '0':
		temp = 0;
		break;
	case '1':
		temp = 1;
		break;
	case '2':
		temp = 2;
		break;
	case '3':
		temp = 3;
		break;
	case '4':
		temp = 4;
		break;
	case '5':
		temp = 5;
		break;
	case '6':
		temp = 6;
		break;
	case '7':
		temp = 7;
		break;
	case '8':
		temp = 8;
		break;
	case '9':
		temp = 9;
		break;
	case 'A':
		temp = 10;
		break;
	case 'B':
		temp = 11;
		break;
	case 'C':
		temp = 12;
		break;
	case 'D':
		temp = 13;
		break;
	case 'E':
		temp = 14;
		break;
	case 'F':
		temp = 15;
		break;
	default:
		break;
	}

	return temp;
}

char intToHex(int number)
{
	char temp = '0';

	switch (number) {
	case 0:
		temp = '0';
		break;
	case 1:
		temp = '1';
		break;
	case 2:
		temp = '2';
		break;
	case 3:
		temp = '3';
		break;
	case 4:
		temp = '4';
		break;
	case 5:
		temp = '5';
		break;
	case 6:
		temp = '6';
		break;
	case 7:
		temp = '7';
		break;
	case 8:
		temp = '8';
		break;
	case 9:
		temp = '9';
		break;
	case 10:
		temp = 'A';
		break;
	case 11:
		temp = 'B';
		break;
	case 12:
		temp = 'C';
		break;
	case 13:
		temp = 'D';
		break;
	case 14:
		temp = 'E';
		break;
	case 15:
		temp = 'F';
		break;
	default:
		break;
	}

	return temp;
}

char addHex(char first, char second, bool& carry)
{
	int answer = 0;
	char charAnswer;

	//if carry flag is set, add one to answer
	if (carry == false)
	{
		answer = (hexToInteger(first) + hexToInteger(second));
	}
	else
	{
		answer = (hexToInteger(first) + hexToInteger(second) + 1);
	}

	//converting to hex and returning answer as charAnswer
	if (answer < 16)
	{
		carry = false;
		charAnswer = intToHex(answer);

	}
	else
	{
		answer = answer - 16;
		charAnswer = intToHex(answer);
		carry = true;
	}

	return charAnswer;

}

//used to calculate address for next instruction
//intakes: current address as string, size of string as int
//outputs: new address for next instruction
string calcNextAddress(string address, int size)
{
	string temp = "----";
	bool carry = false;
	char charAnswer[25] = "";

	//used to create format of size
	string strSize = "000";
	string charSize = "-";
	charSize.at(0) = intToHex(size);
	strSize.append(charSize);

	/*cout << "current addr: " << address << endl;
	cout << "old string val: " << size << endl;
	cout << "new size string: " << strSize << endl;*/

	int arrayCount = 0;
	for (int i = (address.length() - 1); i >= 0; i--)
	{
		charAnswer[arrayCount] = addHex(address.at(i), strSize.at(i), carry);
		arrayCount++;
	}

	for (int i = (arrayCount - 1); i >= 0; i--)
	{
		temp.at(i) = charAnswer[i];
	}

	reverse(temp.begin(), temp.end());

	//cout << "next address: " << temp << endl << endl;

	return temp;
}

void decToHex(int x, char y[])
{
	char hexNumber[2] = { '0', '0' };
	int tempNumber;

	//converting decimal to hex
	int i = 0;
	while (x > 0)
	{
		tempNumber = x % 16;

		switch (tempNumber)
		{
		case 0:
			hexNumber[i] = '0';
			break;
		case 1:
			hexNumber[i] = '1';
			break;
		case 2:
			hexNumber[i] = '2';
			break;
		case 3:
			hexNumber[i] = '3';
			break;
		case 4:
			hexNumber[i] = '4';
			break;
		case 5:
			hexNumber[i] = '5';
			break;
		case 6:
			hexNumber[i] = '6';
			break;
		case 7:
			hexNumber[i] = '7';
			break;
		case 8:
			hexNumber[i] = '8';
			break;
		case 9:
			hexNumber[i] = '9';
			break;
		case 10:
			hexNumber[i] = 'A';
			break;
		case 11:
			hexNumber[i] = 'B';
			break;
		case 12:
			hexNumber[i] = 'C';
			break;
		case 13:
			hexNumber[i] = 'D';
			break;
		case 14:
			hexNumber[i] = 'E';
			break;
		case 15:
			hexNumber[i] = 'F';
			break;
		default:
			break;
		}

		x = x / 16;

		i++;
	}

	y[0] = hexNumber[1];
	y[1] = hexNumber[0];
}

int main()
{
	struct command {
		string address = "";
		string instruction = "";
		string value = "";
		string nextAddress = "";
	};

	command data[25];

	struct table {
		string address = "";
		string name = "";
	};

	table symbolTable[25];

	string temp = "";

	string tempAddress = "";

	string comments = "";

	ofstream output;
	ifstream input;
	input.open("input.txt");

	int commandCounter = 0;
	int stCounter = 0;
	int size = 0;

	while (!input.eof())
	{
		size = 0;

		if (commandCounter == 0)
		{
			data[0].address = "2000";
		}
		else
		{
			data[commandCounter].address = tempAddress;
		}

		input >> temp;

		//cout << "current instruction: " << temp << endl;

		if (temp == "ORG")
		{
			data[commandCounter].instruction = "ORG";

			input >> temp;

			data[commandCounter].nextAddress = temp;

		}
		else if (temp == "MOVE")
		{
			size = size + 2;

			data[commandCounter].instruction = "MOVE";

			input >> temp;

			if (temp.at(0) == '#')
			{
				data[commandCounter].value = temp;
				data[commandCounter].value.erase(3, 1);

				size = size + 2;

				input >> temp;

				data[commandCounter].nextAddress = temp;

				size = size + 4;
			}
			else if (temp.at(0) == '$')
			{
				data[commandCounter].nextAddress = temp;
				data[commandCounter].nextAddress.erase(9, 1);

				size = size + 4;

				//for "D0," command
				input >> temp;

				input >> temp;

				if (temp.at(0) == ';')
				{
					getline(input, comments);
				}

			}
			else if (temp.at(0) == 'D')
			{
				input >> temp;

				data[commandCounter].nextAddress = temp;
				data[commandCounter].nextAddress.erase(9, 1);

				size = size + 4;

				input >> temp;

				if (temp.at(0) == ';')
				{
					getline(input, comments);
				}
			}

		}
		else if (temp == "TRAP")
		{
			size = size + 2;

			data[commandCounter].instruction = "TRAP";

			input >> temp;

			data[commandCounter].value = temp;

			input >> temp;

			if (temp.at(0) == ';')
			{
				getline(input, comments);
			}

		}
		else if (temp == "LOOP1" || temp == "LOOP2")
		{
			input >> temp;

			if (temp == "MOVE")
			{
				size = size + 2;
				
				data[commandCounter].instruction = "MOVE";

				input >> temp;

				input >> temp;

				data[commandCounter].nextAddress = temp;

				size = size + 4;

				input >> temp;

				if (temp.at(0) == ';')
				{
					getline(input, comments);
				}

				symbolTable[stCounter].name = "LOOP1";
				symbolTable[stCounter].address = data[commandCounter].address;

			}
			else if (temp == "ADDI")
			{
				size = size + 2;

				data[commandCounter].instruction = "ADDI";

				input >> temp;

				data[commandCounter].value = temp;
				data[commandCounter].value.erase(3, 1);

				size = size + 2;

				input >> temp;

				data[commandCounter].nextAddress = temp;
				data[commandCounter].nextAddress.erase(9, 1);

				size = size + 4;

				input >> temp;

				if (temp.at(0) == ';')
				{
					getline(input, comments);
				}

				symbolTable[stCounter].name = "LOOP2";
				symbolTable[stCounter].address = data[commandCounter].address;

			}

			stCounter++;
		}
		else if (temp == "ADD")
		{
			size = size + 2;

			data[commandCounter].instruction = "ADD";

			input >> temp;

			data[commandCounter].nextAddress = temp;
			data[commandCounter].nextAddress.erase(9, 1);

			size = size + 4;

			input >> temp;

			input >> temp;

			if (temp.at(0) == ';')
			{
				getline(input, comments);
			}
		}

		tempAddress = calcNextAddress(data[commandCounter].address, size);
		commandCounter++;
	}

	//it was giving me trouble when I tried attaching to others...
	if (temp == "END")
	{
		size = size + 2;

		data[commandCounter].instruction = "END";
	}

	/*int z = 10;
	string dumb = "END";

	cout << endl << "Instruction " << (z+1) << ": '"  << dumb <<  "'" << endl;
	cout << "Location: " << data[z].address << endl;
	cout << "Command: " << data[z].instruction << endl;
	cout << "Value: " << data[z].value << endl;
	cout << "Assigned Address: " << data[z].nextAddress << endl;

	if (stCounter > 0)
	{
		cout << endl;

		cout << "## SYMBOL TABLE ##" << endl;
		for (int i = 0; i < (stCounter); i++)
		{
			cout << "Variable: " << symbolTable[i].name << endl;
			cout << "Address: " << symbolTable[i].address << endl << endl;
		}
	}*/

	output.open("output.txt");

	//do output shit
	output << "Address     Machine Code     Operands      Instructions" << endl;

	char operand[2] = { "" };
	string mc = "";

	for (int i = 0; i < (commandCounter - 1); i++)
	{
		if (data[i].instruction == "ORG" || data[i].instruction == "END")
		{
			;
		}
		else
		{
			//address output
			output << "00" << data[i].address << setw(6) << setfill(' ') << ' ';

			//machine code output
			if (data[i].address == "2000")
				mc = "33FC";
			else if (data[i].address == "2008")
				mc = "4E41";
			else if (data[i].address == "200A")
				mc = "33C0";
			else if (data[i].address == "2010")
				mc = "3039";
			else if (data[i].address == "2016")
				mc = "D079";
			else if (data[i].address == "201C")
				mc = "33C0";
			else if (data[i].address == "2022")
				mc = "0679";
			else if (data[i].address == "202A")
				mc = "4E42";
			else if (data[i].address == "202C")
				mc = "4E40";

				output << mc << setw(13) << ' ';

			//operands output
			data[i].value.erase(0, 1);
			int newNum = atoi(data[i].value.c_str());

			decToHex(newNum, operand);

			if (newNum != 0 && data[i].instruction != "TRAP")
				if (operand[1] == NULL)
					output << "0" << operand[0] << setw(12) << ' ';
				else
					output << operand[0] << operand[1] << setw(12) << ' ';
			else
				output << "--" << setw(12) << ' ';


			//instruction output
			if (data[i].instruction == "ORG" || data[i].instruction == "ADD")
				output << data[i].instruction << "  ";
			else
				output << data[i].instruction << ' ';

			if (data[i].value == "")
				output << "-- " << "  ";
			else
			{
				if (data[i].value.length() != 3)
					output << '#';

				if (data[i].nextAddress != "")
					output << data[i].value << ", ";
				else
					output << data[i].value << "   --";
			}

			output << data[i].nextAddress << endl;
		}
	}

	if (stCounter > 0)
	{
		output << endl;

		output << "## SYMBOL TABLE ##" << endl;
		for (int i = 0; i < (stCounter); i++)
		{
			output << symbolTable[i].name << setw(5) << ' ' << symbolTable[i].address << endl;
		}
	}
	

	if (input.is_open() && output.is_open())
	{
		input.close();
		output.close();
	}

	return 0;
}
