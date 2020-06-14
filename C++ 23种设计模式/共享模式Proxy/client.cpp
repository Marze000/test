// 没有使用代理模式的做法
class Isubject{
public:
	Isubject();
	virtual void process();
	~Isubject();
	
};
class RealSubject:public Isubject{
public:
	virtual void process(){
		//...	
		//...
	}
};
class ClientApp{
	Isubject* subject;
public:
	ClientApp(){
		subject = new RealSubject();
	}
	void DoTask(){
		// ...
		subject->process();
		// ...
	}
};