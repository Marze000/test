//创建一个接口。
class Strategy {
public:
	virtual int doOperation(int num1, int num2)=0;
	virtual ~Strategy(){}
};

//创建实现接口的实体类。
class OperationAdd :public Strategy{
public:
	int doOperation(int num1, int num2) {
    	return num1 + num2;
   	}
};

class OperationSubtract:public Strategy{
public:
	int doOperation(int num1, int num2) {
   		return num1 - num2;
   	}
};

class OperationMultiply:public	Strategy{
public:
	int doOperation(int num1, int num2) {
    	return num1 * num2;
   	}
};

//创建 Context 类。
class Context {
private:
	// 采用组合的方式，定义一个基类对象
	Strategy* strategy;
 
public:
	Context(Strategy* strategy){
    	this->strategy = strategy;
   	}
 
   	int executeStrategy(int num1, int num2){
   		// 运行时绑定，会执行对应的接口
    	return strategy->doOperation(num1, num2);
   	}
};

int main() {
	Context* context = new Context(new OperationAdd());    
	cout<<"10 + 5 = "<<context->executeStrategy(10,5)<<endl;

	context = new Context(new OperationSubtract());      
	cout<<"10 - 5 = "<<context->executeStrategy(10,5)<<endl;

	context = new Context(new OperationMultiply());    
	cout<<"10 * 5 = "<<context->executeStrategy(10,5)<<endl;
}

//执行程序，输出结果：
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50