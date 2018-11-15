#include "lk_stack.h"

class caculator
{
	private:
		//计算器数据成员
		LinkStack<double> op_numbers;	//操作数栈
		LinkStack<char> op_ch; //运算符栈

		//辅助函数
		int optr_rank(char op);	//运算符优先级
		void get_2numbers(double &op1, double &op2);	//把俩个操作数退栈
		double temp_op(double left, double right, char op);	//执行操作
		bool is_op(char op);	//判断是否操作符

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
	op_ch.Push('='); //初始压入一个‘=’
	char temp;
	char pre_ch; //当前输入字符的前一个字符
	char op_top_ch; //操作符栈顶字符；
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
			cin >> op_number; //用cin输入double类型数
			op_numbers.Push(op_number);	//压入数栈
			pre_ch = '0';
			temp = GetChar();
		}
		else if (!is_op(temp))
		{
			cout << "表达式出错！" << endl;
			break;
		}
		else  // 为操作符
		{
			if ((pre_ch == '=' || pre_ch == '(') && (temp == '+' || temp == '-')) // 单目运算符变为普通二元操作
			{
				op_numbers.Push(0);
				pre_ch = '0';
			}
			if ((op_top_ch == ')' && temp == '(') || (op_top_ch == '(' && temp == '=')
				|| (op_top_ch == '=' && temp == ')'))
				
			{
				cout << "表达式错误！" << endl;
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
	cout << "答案是" << answer << endl;
}
