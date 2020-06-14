// 适配器简单模型 : 通过目标接口可以调用遗留接口的功能

// 目标接口(新接口)
class ITarget{
public:
	virtual void process() = 0;
	
};

// 遗留接口(老接口)
class IAdaptee{
public:
	virtual void foo(int data) = 0;
	virtual int bar() = 0;
};

// 遗留类型
class OldClass:public IAdaptee{
	//...	
};

// 对象适配器
class Adapter:public ITarget{
protected:
	IAdaptee* pAdaptee;

public:
	Adapter(IAdaptee* pAdaptee){
		this->pAdaptee = pAdaptee;
	}
	virtual void process(){
		int data = pAdaptee->bar();
		pAdaptee->foo(data);
	}
	Adapter();
	~Adapter();
	
};

// 类适配器
class Adapter:public ITarget,protected OldClass{

};

int main(){
	IAdaptee* pAdaptee = new OldClass();
	ITarget* pTarget = new Adapter(pAdaptee);
	pTarget->process();

}