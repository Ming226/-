#include "lk_stack.h"

class caculator
{
	private:
		//���������ݳ�Ա
		LinkStack<double> op_numbers;	//������ջ
		LinkStack<char> op_ch; //�����ջ

		//��������
		int optr_rank(char op);	//��������ȼ�
		void get_2numbers(double &op1, double &op2);	//��������������ջ
		double temp_op(double left, double right, char op);	//ִ�в���
		bool is_op(char op);	//�ж��Ƿ������

		//
	public:
		caculator() {};
		virtual ~caculator() {};
		void run();		
};

int caculator::optr_rank(char op)
{
	switch (op)
	{
		case '=':
			return 1; break;
		case '(':
			return 2; break;
		case ')':
			return 2; break;
		case '+':
			return 3; break;
		case '-':
			return 3; break;
		case '*':
			return 4; break;
		case '/':
			return 4; break;
		case '^':
			return 5; break;
	default:
		break;
	}
}

void caculator::get_2numbers(double &op1, double &op2)
{
	op_numbers.Pop(op2);
	op_numbers.Pop(op1);
}

double caculator::temp_op(double left, double right, char op)
{
	switch (op)
	{
	case '+':
		return left + right; break;
	case '-':
		return  left - right; break;
	case '*':
		return left * right; break;
	case '/' : 
		return left / right; break;
	case '^':
		return pow(left, right); break;
	default:
		break;
	}
}

bool caculator::is_op(char op)
{
	bool a = false;
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '=' || op == '(' ||op == ')')
		a = true;
	return a;
}

void caculator::run()
{
	op_numbers.Clear();
	op_ch.Clear();
	op_ch.Push('='); //��ʼѹ��һ����=��
	char temp;
	char pre_ch; //��ǰ�����ַ���ǰһ���ַ�
	char op_top_ch; //������ջ���ַ���
	double op_number = 0,answer = 0;
	char op;

	pre_ch = '=';
	temp = GetChar();

	op_ch.Top(op_top_ch);

	while (op_top_ch != '=' ||  temp != '=')
	{
		if (isdigit(temp) || temp == '.')
		{
			cin.putback(temp);
			cin >> op_number; //��cin����double������
			op_numbers.Push(op_number);	//ѹ����ջ
			pre_ch = '0';
			temp = GetChar();
		}
		else if (!is_op(temp))
		{
			cout << "���ʽ����" << endl;
			break;
		}
		else  // Ϊ������
		{
			if ((pre_ch == '=' || pre_ch == '(') && (temp == '+' || temp == '-')) // ��Ŀ�������Ϊ��ͨ��Ԫ����
			{
				op_numbers.Push(0);
				pre_ch = '0';
			}
			if ((op_top_ch == ')' && temp == '(') || (op_top_ch == '(' && temp == '=')
				|| (op_top_ch == '=' && temp == ')'))
				
			{
				cout << "���ʽ����" << endl;
				break;
			}
			else if (op_top_ch == '(' && temp == ')')
			{
				op_ch.Pop(op_top_ch);
				temp = GetChar();
				pre_ch = ')';
			}
			else if (temp == '(' || optr_rank(op_top_ch) < optr_rank(temp))
			{
				op_ch.Push(temp);
				pre_ch = temp;
				temp = GetChar();
			}
			else
			{
				op_ch.Pop(op);
				double a, b;
				get_2numbers(a, b);
				op_numbers.Push(temp_op(a, b, op));
			}
		}
		op_ch.Top(op_top_ch);
	}
	op_numbers.Pop(answer);
	cout << "����" << answer << endl;
}
